open Ast ;;
open Ast.Mips ;;

module Env = Map.Make(String) ;;

let _types_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%add", Fun_t { ret = Num_t ; args = [ Num_t ; Num_t ] } ]
;;

let _lib_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%add", [ Lw (T0, Mem (SP, 4))
                        ; Lw (T1, Mem (SP, 0))
                        ; Add (V0, T0, T1) ] ]
;;

(*
 * Ici %add est une fonction simple qui est systématiquement inlinée.
 *
 * En pratique pour la plupart des petites fonctions de la stdlib qui
 * correspondent à une instruction MIPS on pourra faire comme ça.
 *
 * Mais pour les fonctions plus complexes, par exemple celles définies
 * par l'utilisateurice, leur code sera à un label à l'endroit de leur
 * définition, et l'appelle de la fonction consistera en un
 * jump-and-link vers ce label.
 *)
