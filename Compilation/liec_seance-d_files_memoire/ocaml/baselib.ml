open Ast ;;
open Ast.Mips ;;

module Env = Map.Make(String) ;;

let _types_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%add", Fun_t { ret = Num_t
                              ; args = [ Num_t ; Num_t ] }
              ; "print_num", Fun_t { ret = Void_t
                                    ; args = [ Num_t ]}
              ; "print_str", Fun_t { ret = Void_t
                                    ; args = [ Str_t ]}
              ; "pair", Fun_t { ret = Pair_t Num_t
                              ; args = [ Num_t ; Pair_t (Num_t) ] }
              ; "head", Fun_t { ret = Num_t
                              ; args = [ Pair_t (Num_t) ] }
              ; "tail", Fun_t { ret = Pair_t (Num_t)
                              ; args = [ Pair_t (Num_t) ] }
    ]
;;

let _lib_ =
  List.fold_left
    (fun e builtin -> Env.add (fst builtin) (snd builtin) e)
    Env.empty [ "%add", [ Lw (T0, Mem (SP, 4))
                        ; Lw (T1, Mem (SP, 0))
                        ; Add (V0, T0, T1) ]
              ; "print_num", [ Lw (A0, Mem (SP, 0))
                             ; Li (V0, Syscall.print_int)
                             ; Syscall ]
              ; "print_str", [ Lw (A0, Mem (SP, 0))
                             ; Li (V0, Syscall.print_string)
                             ; Syscall ]
              ; "pair", [ Jal (Lbl "_pair") ]
              ; "head", [ Lw (T0, Mem (SP, 0))
                        ; Lw (V0, Mem (T0, -4)) ]
              ; "tail", [ Lw (T0, Mem (SP, 0))
                        ; Lw (V0, Mem (T0, 0)) ]
    ]
;;

let _implem_ =
  [ Label "_pair"
  ; Li (A0, 8)
  ; Li (V0, Syscall.sbrk)
  ; Syscall
  ; Lw (T0, Mem (SP, 4))
  ; Sw (T0, Mem (V0, -4))
  ; Lw (T0, Mem (SP, 0))
  ; Sw (T0, Mem (V0, 0))
  ; Jr RA
  ]
;;
