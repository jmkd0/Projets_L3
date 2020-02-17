{
  open Lexing;;
  open Parser;;

  exception Lexer of string;;
}

rule tokenize = parse
| eof { Lend }
| [ ' ' '\t' '\n' ] { tokenize lexbuf }
| "&" { Land }
| "|" { Lor }
| "!" { Lnot }
| "(" { Lopar }
| ")" { Lcpar }
| "0" { Lbool (false) }
| "1" { Lbool (true) }
| _ as c { raise (Lexer (Printf.sprintf "Unrecognized char '%c' at offset %d."
                                           c lexbuf.lex_curr_p.pos_cnum)) }
