open Ast.Mips ;;

let fmt_reg r =
  match r with
  | SP -> "$sp"
  | RA -> "$ra"
  | V0 -> "$v0"
  | A0 -> "$a0"
  | T0 -> "$t0"
  | T1 -> "$t1"
;;

let fmt_loc l =
  match l with
  | Reg r -> fmt_reg r
  | Lbl l -> l
  | Mem (r, o) -> Printf.sprintf "%d(%s)" o (fmt_reg r)
;;

let print_instr out instr =
  let pr = Printf.fprintf in
  match instr with
  | Asciiz (n, s)  -> pr out "%s: .asciiz \"%s\"\n" n s
  | Label n        -> pr out "%s:\n" n
  | Move (d, r)    -> pr out "  move %s, %s\n" (fmt_reg d) (fmt_reg r)
  | Li (d, i)      -> pr out "  li %s, %d\n" (fmt_reg d) i
  | La (d, l)      -> pr out "  la %s, %s\n" (fmt_reg d) (fmt_loc l)
  | Sw (r, l)      -> pr out "  sw %s, %s\n" (fmt_reg r) (fmt_loc l)
  | Lw (r, l)      -> pr out "  lw %s, %s\n" (fmt_reg r) (fmt_loc l)
  | Addi (d, r, i) -> pr out "  addi %s, %s, %d\n" (fmt_reg d) (fmt_reg r) i
  | Add (d, r, s)  -> pr out "  add %s, %s, %s\n" (fmt_reg d) (fmt_reg r) (fmt_reg s)
  | Syscall        -> pr out "  syscall\n"
  | Jal l          -> pr out "  jal %s\n" (fmt_loc l)
  | Jr r           -> pr out "  jr %s\n" (fmt_reg r)
;;

let print_instructions out instrs =
  List.iter (fun i -> print_instr out i) instrs
;;

let print out asm =
  Printf.fprintf out "  .data\n" ;
  print_instructions out asm.data ;
  Printf.fprintf out "\n  .text\n  .globl main\n" ;
  print_instructions out asm.text
;;
