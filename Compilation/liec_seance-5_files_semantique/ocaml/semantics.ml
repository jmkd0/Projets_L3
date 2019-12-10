open Ast ;;

exception Error of string * Lexing.position ;;

let warn msg pos =
  Printf.eprintf "Warning on line %d col %d: %s.\n"
    pos.Lexing.pos_lnum Lexing.(pos.pos_cnum - pos.pos_bol) msg ;
  exit 1
;;

module Set = Set.Make(String) ;;
module Env = Map.Make(String) ;;

let _be n = if n = 1 then "is" else "are" ;;
let _s n = if n = 1 then "" else "s" ;;

let rec collect_read_var expr =
  match expr with
  | Bit _  -> Set.empty
  | Var v  -> Set.singleton v
  | Call c -> List.fold_left (fun s1 s2 -> Set.union s1 s2) Set.empty
                (List.map collect_read_var c.args)
;;

let idents ps =
  List.map (fun (Pident p) -> p.name) ps
;;

let duplicates ps =
  let rec find_dup ps seen dup =
    match ps with
    | [] -> dup
    | p :: ps -> if Set.mem p seen then find_dup ps seen (p::dup)
                 else find_dup ps (Set.add p seen) dup
  in find_dup ps Set.empty []
;;

let rec analyze_expr expr env lenv =
  match expr with
  | Pbit b -> Bit b.value, 1
  | Pvar v ->
     if Set.mem v.name (fst lenv) then
       Var v.name, 1
     else
       raise (Error (Printf.sprintf "unknown variable %s" v.name, v.pos))
  | Pcall c ->
     try
       let block_arity = Env.find c.block env in
       let aas = List.map (fun a -> analyze_expr a env lenv) c.args in
       let nb_inputs = List.fold_left (+) 0 (List.map snd aas) in
       if nb_inputs = fst block_arity then
         Call { block = c.block ; args = List.map fst aas },
         snd block_arity
       else
         raise (Error (Printf.sprintf "block %s expects %d input%s but %d %s given"
                         c.block
                         (fst block_arity) (_s (fst block_arity))
                         nb_inputs (_be nb_inputs),
                       c.pos))
     with Not_found ->
       raise (Error (Printf.sprintf "unkwown block %s" c.block, c.pos))
;;

let rec analyze_instr (Passign a) env lenv =
  let ae = analyze_expr a.expr env lenv in
  let outputs = idents a.outputs in
  if List.length outputs != snd ae then
    raise (Error (Printf.sprintf "assignment expects %d output%s but %d %s given"
                    (List.length outputs) (_s (List.length outputs))
                    (snd ae) (_be (snd ae)),
                  a.pos)) ;
  let d = Set.(inter (of_list outputs) (fst lenv)) in
  if not (Set.is_empty d) then
    begin
      let n = Set.choose d in
      let Pident p = List.find (fun (Pident p) -> p.name = n) a.outputs in
      raise (Error (Printf.sprintf "%s already assigned" p.name, p.pos))
    end ;
  Assign { outputs = outputs ; expr = fst ae },
  (Set.union (fst lenv) (Set.of_list outputs),
   Set.union (snd lenv) (collect_read_var (fst ae)))
;;

let rec analyze_block (Pblock b) env =
  if Env.mem b.name env then
    raise (Error (Printf.sprintf "block %s already defined" b.name, b.pos)) ;
  let d = duplicates (idents b.inputs) in
  if not (d = []) then
    begin
      let n = List.hd d in
      let Pident p = List.find (fun (Pident p) -> p.name = n) b.inputs in
      raise (Error (Printf.sprintf "duplicate input %s" p.name,
                    p.pos))
    end ;
  let d = duplicates (idents b.outputs) in
  if not (d = []) then
    begin
      let n = List.hd d in
      let Pident p = List.find (fun (Pident p) -> p.name = n) b.outputs in
      raise (Error (Printf.sprintf "duplicate output %s" p.name,
                    p.pos))
    end ;
  let rec analyze_body body lenv =
    match body with
    | [] ->
       let written, read = lenv in
       if not Set.(subset (of_list (idents b.outputs)) written) then
         begin
           let n = Set.(choose (diff (of_list (idents b.outputs)) written)) in
           let Pident p = List.find (fun (Pident p) -> p.name = n) b.outputs in
           raise (Error (Printf.sprintf "output %s is not written to in block %s"
                           p.name b.name,
                         p.pos))
         end ;
       if not Set.(subset (of_list (idents b.inputs)) read) then
         begin
           let n = Set.(choose (diff (of_list (idents b.inputs)) read)) in
           let Pident p = List.find (fun (Pident p) -> p.name = n) b.inputs in
           warn (Printf.sprintf "output %s is not written to in block %s"
                   p.name b.name)
             p.pos
         end ;
       []
    | instr :: body ->
       let ai = analyze_instr instr env lenv
       in (fst ai) :: (analyze_body body (snd ai))
  in
  let ab = analyze_body b.body (Set.of_list (idents b.inputs), Set.empty)
  in Block { name = b.name
           ; inputs = idents b.inputs
           ; outputs = idents b.outputs
           ; body = ab },
     Env.add b.name (List.length b.inputs, List.length b.outputs) env
;;

let rec analyze_prog prog env =
  match prog with
  | [] -> failwith "empty program" (* should really not happen *)
  | [ Pblock last ] ->
     if last.name = "main" then
       [ fst (analyze_block (Pblock last) env) ]
     else
       raise (Error (Printf.sprintf "missing 'main' block", last.pos))
  | block :: prog ->
     let ab = analyze_block block env in
     (fst ab) :: (analyze_prog prog (snd ab))
;;

let analyze prog =
  analyze_prog prog Stdlib._typing_
;;
