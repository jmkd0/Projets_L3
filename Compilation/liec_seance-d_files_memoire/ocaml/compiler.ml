open Ast.Simplified ;;
open Ast.Mips ;;

module Env = Baselib.Env ;;

(* helper functions *)

let stack_push regs =
  let rec loop regs =
    if regs = [] then []
    else Sw (List.hd regs, Mem (SP, 4 * ((List.length regs) - 1))) :: (loop (List.tl regs))
  in [ Addi (SP, SP, -4 * List.length regs) ] @ loop regs
;;

let stack_pop regs =
  let rec loop regs =
    if regs = [] then []
    else Lw (List.hd regs, Mem (SP, 4 * ((List.length regs) - 1))) :: (loop (List.tl regs))
  in loop regs @ [ Addi (SP, SP, 4 * List.length regs) ]
;;

(* compiler *)

let rec compile_and_push expr env =
  compile_expr expr env @ stack_push [ V0 ]

and compile_expr expr env =
  match expr with
  | Nil    -> [ Li (V0, 0) ]
  | Num n  -> [ Li (V0, n) ]
  | Data l -> [ La (V0, Lbl l) ]
  | Call c -> List.flatten (List.map (fun a -> compile_and_push a env) c.args)
              @ Env.find c.func env
              @ [ Addi (SP, SP, 4 * (List.length c.args)) ]
;;

let compile_prog prog env =
  compile_expr prog env
;;

let compile ast =
  { data = [ Asciiz ("newline", "\\n") ]
           @ List.map (fun (l,s) -> Asciiz (l, s)) (snd ast)
  ; text = Baselib._implem_
           @ [ Label "main" ]
           @ stack_push [ RA ]
           @ compile_prog (fst ast) Baselib._lib_
           @ [ La (A0, Lbl "newline")
             ; Li (V0, Syscall.print_string)
             ; Syscall ]
           @ stack_pop [ RA ]
           @ [ Jr RA ]
  }
;;
