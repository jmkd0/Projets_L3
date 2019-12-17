open Ast ;;
open Stdlib ;;

exception Error of string * Lexing.position ;;

module Env = Map.Make(String) ;;

(* fonctions d'aide à la gestion des erreurs *)

let rec string_of_type t =
  match t with
  | Num_t  -> "number"
  | Bool_t -> "boolean"
  | Fun_t (r, a) ->
     (if (List.length a) > 1 then "(" else "")
     ^ (String.concat ", " (List.map string_of_type a))
     ^ (if (List.length a) > 1 then ")" else "")
     ^ " -> " ^ (string_of_type r)
;;

let expr_pos expr =
  match expr with
  | Pbool e -> e.pos
  | Pnum e  -> e.pos
  | Pvar e  -> e.pos
  | Pcall e -> e.pos
  | Pcond e -> e.pos
;;

let errt expected given pos =
  raise (Error (Printf.sprintf "expected %s but given %s"
                  (string_of_type expected)
                  (string_of_type given),
                pos))
;;

(* analyse sémantique *)

let rec analyze_expr expr =
  match expr with
  | Pbool b -> Bool b.value
  | Pnum n  -> Num n.value
  | Pvar v  -> Var v.name
  | Pcall c ->
     let args = List.map analyze_expr c.args in
     Call { func = c.func ; args = args }
  | Pcond c ->
     let at = analyze_expr c.test in
     let ay = analyze_expr c.yes in
     let an = analyze_expr c.no in
     Cond { test = at ; yes = ay ; no = an }
;;

let rec analyze_instr instr =
  match instr with
  | Passign a ->
     let ae = analyze_expr a.expr in
     Assign { var = a.var ; expr = ae }
;;

let rec analyze_prog prog =
  match prog with
  | [] -> []
  | instr :: prog ->
     let ai = analyze_instr instr in
     ai :: (analyze_prog prog)
;;

let analyze parsed =
  analyze_prog parsed
;;
