open Lexer;;
open Parser;;
open Ast;;

let rec string_of_expr e =
  match e with
  | And (a, b) -> "And(" ^ (string_of_expr a) ^ ", " ^ (string_of_expr b) ^ ")"
  | Or (a, b)  -> "Or(" ^ (string_of_expr a) ^ ", " ^ (string_of_expr b) ^ ")"
  | Not (e)    -> "Not(" ^ (string_of_expr e) ^ ")"
  | Bit (b)    -> "Bit(" ^ (string_of_bool b) ^ ")"
;;

let buf = Lexing.from_string Sys.argv.(1) in
let e = Parser.prog Lexer.tokenize buf
in Printf.printf "%s\n" (string_of_expr e)
