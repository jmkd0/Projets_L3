{
  open Parser ;;

  exception Error of char;;
}

let digit = ['0'-'9']

rule lex = parse
| eof          { Leof }
| [ ' ' '\t' ] { lex lexbuf }
| '\n'         { Lexing.new_line lexbuf; lex lexbuf }
| "+"          { Lplus }
| digit+ as n  { Lnum (int_of_string n) }
| _ as c       { raise (Error c) }
