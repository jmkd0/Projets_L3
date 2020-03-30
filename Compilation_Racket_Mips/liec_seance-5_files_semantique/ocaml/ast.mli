type p_prog = p_block list
and p_block =
  | Pblock of { name: string
              ; inputs: p_ident list
              ; outputs: p_ident list
              ; body: p_instr list
              ; pos: Lexing.position }
and p_ident =
  | Pident of { name: string
              ; pos: Lexing.position }
and p_instr =
  | Passign of { outputs: p_ident list
               ; expr: p_expr
               ; pos: Lexing.position }
and p_expr =
  | Pbit of { value: bool
            ; pos: Lexing.position }
  | Pvar of { name: string
            ; pos: Lexing.position }
  | Pcall of { block: string
             ; args: p_expr list
             ; pos: Lexing.position }
;;

type prog = block list
and block =
  | Block of { name: string
             ; inputs: string list
             ; outputs: string list
             ; body: instr list }
and instr =
  | Assign of { outputs: string list
              ; expr: expr }
and expr =
  | Bit of bool
  | Var of string
  | Call of { block: string
            ; args: expr list }
;;
