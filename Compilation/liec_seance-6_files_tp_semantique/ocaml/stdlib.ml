module Env = Map.Make(String) ;;

type type_t =
  | Bool_t
  | Num_t
  | Fun_t of type_t * type_t list
;;

let _types_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%add", Fun_t (Num_t, [ Num_t ; Num_t ])
              ; "%sub", Fun_t (Num_t, [ Num_t ; Num_t ])
              ; "%mul", Fun_t (Num_t, [ Num_t ; Num_t ])
              ; "%div", Fun_t (Num_t, [ Num_t ; Num_t ])
              ; "%eq",  Fun_t (Bool_t, [ Num_t ; Num_t ])
              ; "%neq", Fun_t (Bool_t, [ Num_t ; Num_t ])
              ; "%lt",  Fun_t (Bool_t, [ Num_t ; Num_t ])
              ; "%gt",  Fun_t (Bool_t, [ Num_t ; Num_t ])
              ; "%lte", Fun_t (Bool_t, [ Num_t ; Num_t ])
              ; "%gte", Fun_t (Bool_t, [ Num_t ; Num_t ]) ]
;;
