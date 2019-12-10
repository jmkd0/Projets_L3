type p_prog = p_instr list
and p_instr =
  | Passign of { var: string
               ; expr: p_expr
               ; pos: Lexing.position }
and p_expr =
  | Pbool of { value: bool
             ; pos: Lexing.position }
  | Pnum of { value: int
            ; pos: Lexing.position }
  | Pvar of { name: string
            ; pos: Lexing.position }
  | Pcall of { func: string
             ; args: p_expr list
             ; pos: Lexing.position }
  | Pcond of { test: p_expr
             ; yes: p_expr
             ; no: p_expr
             ; pos: Lexing.position }
;;

type prog = instr list
and instr =
  | Assign of { var: string
              ; expr: expr }
and expr =
  | Bool of bool
  | Num of int
  | Var of string
  | Call of { func: string
            ; args: expr list }
  | Cond of { test: expr
            ; yes: expr
            ; no: expr }
;;
