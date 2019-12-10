%{
  open Ast.Parsed ;;
%}

%token <int> Lnum
%token Lplus Leof

%left Lplus

%start prog

%type <Ast.Parsed.prog> prog

%%

prog:
| e = expr; Leof { e }
;

expr:
| n = Lnum {
  Num { value = n ; pos = $startpos }
}
| a = expr; Lplus; b = expr {
  Call { func = "%add" ; args = [ a ; b ] ; pos = $startpos($2) }
}
;
