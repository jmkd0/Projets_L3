open Ast ;;
module P = Ast.Parsed ;;
open Ast.Typed ;;
open Baselib ;;

exception Error of string * Lexing.position ;;

let rec string_of_type t =
  match t with
  | Num_t    -> "number"
  | Fun_t ft ->
     (if (List.length ft.args) > 1 then "(" else "")
     ^ (String.concat ", " (List.map string_of_type ft.args))
     ^ (if (List.length ft.args) > 1 then ")" else "")
     ^ " -> " ^ (string_of_type ft.ret)
;;

let errt expected given pos =
  raise (Error (Printf.sprintf "expected %s but given %s"
                  (string_of_type expected)
                  (string_of_type given),
                pos))
;;

module Env = Baselib.Env ;;

let rec analyze_expr expr env =
  match expr with
  | P.Num n  -> Num n.value, Num_t
  | P.Call c ->
     try
       match Env.find c.func env with
       | Fun_t ft -> begin
           if not ((List.length c.args) = (List.length ft.args)) then
             raise (Error (Printf.sprintf "function '%s' expects %d arguments but was given %d"
                             c.func (List.length ft.args) (List.length c.args),
                           c.pos))
           else
             let args = List.map2
                          (fun a at ->
                            let aa = analyze_expr a env in
                            if not (at = (snd aa)) then errt at (snd aa) c.pos
                            else fst aa)
                          c.args ft.args in
             Call { func = c.func ; args = args }, ft.ret
         end
       | _ -> raise (Error (Printf.sprintf "value '%s' is not a function" c.func, c.pos))
     with Not_found -> raise (Error (Printf.sprintf "undefined function '%s'" c.func, c.pos))
;;

let rec analyze_prog prog env =
  analyze_expr prog env
;;

let analyze parsed =
  fst (analyze_prog parsed Baselib._types_)
;;
