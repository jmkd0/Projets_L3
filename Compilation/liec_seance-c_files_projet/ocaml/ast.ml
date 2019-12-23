open Lexing ;;

module Parsed = struct
  type prog = expr
  and expr =
    Num of { value: int
           ; pos: position }
  | Call of { func: string
            ; args: expr list
            ; pos: position }
end ;;

type type_t =
  Num_t
| Fun_t of { ret: type_t
           ; args: type_t list }
;;

module Typed = struct
  type prog = expr
  and expr =
    Num of int
  | Call of { func: string
            ; args: expr list }
end ;;

module Mips = struct
  type reg =
    SP
  | RA
  | V0
  | A0
  | T0
  | T1

  type loc =
    Reg of reg
  | Lbl of string
  | Mem of reg * int

  type instr =
    Asciiz of string * string
  | Label of string
  | Li of reg * int
  | La of reg * loc
  | Addi of reg * reg * int
  | Add of reg * reg * reg
  | Sw of reg * loc
  | Lw of reg * loc
  | Move of reg * reg
  | Syscall
  | Jr of reg

  type asm = { data: instr list ; text: instr list }

  module Syscall = struct
    let print_int = 1
    let print_string = 4
  end
end ;;
