%{
  open Ast;;
%}

%token <bool> Lbool
%token Land Lor Lnot
%token Lopar Lcpar
%token Lend

%left Lor
%left Land
%right Lnot

%start prog

%type <Ast.expr> prog

%%

prog:
| e = expr; Lend { e }

expr:
| a = expr; Land; b = expr { And (a, b) }
| a = expr; Lor; b = expr { Or (a, b) }
| Lnot; e = expr { Not (e) }
| Lopar; e = expr; Lcpar { e }
| b = Lbool { Bit (b) }

