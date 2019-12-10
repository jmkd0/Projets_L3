%{
  open Ast.Parsed ;;
%}

%token <int> Lnum
%token <string> Lstr Lident
%token Lplus Lopar Lcpar Lcomma Leof

%left Lplus

%start prog

%type <Ast.Parsed.prog> prog

%%

prog:
| e = expr; Leof { e }
;

expr:
| Lopar; Lcpar {
  Nil
}
| n = Lnum {
  Num { value = n
      ; pos = $startpos }
}
| s = Lstr {
  Str { value = s
      ; pos = $startpos }
}
| f = Lident; Lopar; a = separated_list(Lcomma, expr); Lcpar {
  Call { func = f
       ; args = a
       ; pos = $startpos }
}
| a = expr; Lplus; b = expr {
  Call { func = "%add"
       ; args = [ a ; b ]
       ; pos = $startpos($2) }
}
;
