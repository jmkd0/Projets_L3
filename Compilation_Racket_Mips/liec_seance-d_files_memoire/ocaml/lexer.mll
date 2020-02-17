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
| "("          { Lopar }
| ")"          { Lcpar }
| ","          { Lcomma }
| "print_num"  { Lident "print_num" }
| "print_str"  { Lident "print_str" }
| "pair"       { Lident "pair" }
| "head"       { Lident "head" }
| "tail"       { Lident "tail" }
| digit+ as n  { Lnum (int_of_string n) }
| "\""         { Lstr (string lexbuf) }
| _ as c       { raise (Error c) }

and string = parse
| "\\\"" { "\"" ^ (string lexbuf) }
| "\"" { "" }
| _ as c { (String.make 1 c) ^ (string lexbuf) }
