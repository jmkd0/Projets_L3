(* ocamlbuild -use-menhir liec.byte *)

open Lexing ;;

let err msg pos =
  Printf.eprintf "Error on line %d col %d: %s.\n"
    pos.pos_lnum (pos.pos_cnum - pos.pos_bol) msg ;
  exit 1
;;

let () =
  if (Array.length Sys.argv) != 2 then begin
      Printf.eprintf "Usage: %s <file>\n" Sys.argv.(0) ;
      exit 1
    end;
  let src = open_in Sys.argv.(1) in
  let buf = Lexing.from_channel src in
  try
    let prs = Parser.prog Lexer.lex buf in
    let ast = Analyzer.analyze prs in
    let asm = Compiler.compile ast in
    let tgt = open_out (Sys.argv.(1) ^ ".s") in
    MipsPrinter.print tgt asm ;
    close_in src ; close_out tgt
  with
  | Lexer.Error c ->
     err (Printf.sprintf "unrecognized char '%c'" c) (Lexing.lexeme_start_p buf)
  | Parser.Error ->
     err "syntax error" (Lexing.lexeme_start_p buf)
  | Analyzer.Error (msg, pos) -> err msg pos
