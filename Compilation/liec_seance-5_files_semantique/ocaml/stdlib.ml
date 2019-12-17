module Env = Map.Make(String) ;;

let _typing_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%and", (2, 1)
              ; "%or",  (2, 1)
              ; "%xor", (2, 1)
              ; "%not", (1, 1) ]
;;
