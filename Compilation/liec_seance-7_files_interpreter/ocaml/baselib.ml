open Ast ;;

module Env = Map.Make(String) ;;

let _typing_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%and", (2, 1)
              ; "%or",  (2, 1)
              ; "%xor", (2, 1)
              ; "%not", (1, 1) ]
;;

let _natives_ =
    List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty
    [ "%and", N (fun l -> [ (List.hd l) && (List.nth l 1) ])
    ; "%or",  N (fun l -> [ (List.hd l) || (List.nth l 1) ])
    ; "%xor", N (fun l -> [ ((List.hd l) && (not (List.nth l 1))) ||
                            ((not (List.hd l)) && (List.nth l 1)) ])
    ; "%not", N (fun l -> [ not (List.hd l) ]) ]
;;
