open Ast ;;

module Env = Map.Make(String) ;;

let rec env_add names exprs venv benv =
  let values = eval_args exprs venv benv in
  List.fold_left2 (fun e n v -> Env.add n v e)
    venv names values

and eval_args args venv benv =
  List.(flatten (map (fun a -> eval_expr a venv benv) args))

and eval_expr expr venv benv =
  match expr with
  | Bit b -> [ b ]
  | Var v -> [ Env.find v venv ]
  | Call c ->
     match Env.find c.block benv with
     | B b -> eval_block b c.args venv benv
     | N f -> f (eval_args c.args venv benv)

and eval_instrs instrs venv benv =
  match instrs with
  | [] -> venv
  | (Assign a) :: instrs ->
     let venv = env_add a.outputs [ a.expr ] venv benv in
     eval_instrs instrs venv benv

and eval_block (Block b) args venv benv =
  let inputs = env_add b.inputs args venv benv in
  let venv = eval_instrs b.body inputs benv in
  List.map (fun o -> Env.find o venv) b.outputs

and eval_prog prog benv =
  match prog with
  | [] -> failwith "empty program" (* should not happen *)
  | [ Block main ] ->
     let inputs = List.map (fun i -> print_string (i ^ "? ") ;
                                     Bit (read_int () != 0))
                    main.inputs in
     let outputs = eval_block (Block main) inputs Env.empty benv in
     print_endline "…" ;
     List.iter2 (fun o v -> print_endline (o ^ ": " ^ (if v then "1" else "0")))
       main.outputs outputs
  | (Block b) :: prog ->
     eval_prog prog (Env.add b.name (B (Block b)) benv)
;;

let interp prog =
  eval_prog prog Baselib._natives_
;;
