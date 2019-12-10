module T = Ast.Typed ;;
open Ast.Simplified ;;

let collect_constant_strings ast =
  let uniq = ref 0 in
  let rec ccs ast =
    match ast with
    | T.Nil   -> Nil, []
    | T.Num n -> Num n, []
    | T.Str s ->
       incr uniq;
       let lbl = Printf.sprintf "str_%04d" !uniq in
       Data (lbl), [ (lbl, s) ]
    | T.Call c ->
       let args = List.map ccs c.args in
       Call { func = c.func ; args = List.map fst args },
       List.flatten (List.map snd args)
  in
  ccs ast
;;

let simplify ast =
  collect_constant_strings ast
;;
