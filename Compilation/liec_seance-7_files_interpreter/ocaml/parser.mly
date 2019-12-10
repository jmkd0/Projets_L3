%{
  open Ast ;;
%}

%token <bool> Lbool
%token <string> Lident
%token Llet Lwhere Lrarr Llarr Lsc Ldot Lend
%token Land Lor Lxor Lnot Lopar Lcpar

%left Lor
%left Lxor
%left Land
%right Lnot

%start prog

%type <Ast.p_prog> prog

%%

prog:
| p = nonempty_list(block); Lend { p }
;

block:
| Llet; n = Lident; i = list(ident); Lrarr; o = nonempty_list(ident); Lwhere;
  b = separated_nonempty_list(Lsc, instr); Ldot {
  Pblock { name = n ; inputs = i ; outputs = o ; body = b ; pos = $endpos }
}
;

ident:
| p = Lident {
  Pident { name = p ; pos = $startpos }
}
;

instr:
| o = nonempty_list(ident); Llarr; e = expr {
  Passign { outputs = o ; expr = e ; pos = $startpos($2) }
}
;

expr:
| b = Lident; a = nonempty_list(arg) {
  Pcall { block = b ; args = a ; pos = $startpos }
}
| a = expr; Land; b = expr {
  Pcall { block = "%and" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lor; b = expr {
  Pcall { block = "%or" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lxor; b = expr {
  Pcall { block = "%xor" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| Lnot; e = expr {
  Pcall { block = "%not" ; args = [ e ] ; pos = $startpos }
}
| a = arg { a }
;

arg:
| i = Lident {
  Pvar { name = i ; pos = $startpos }
}
| v = Lbool  {
  Pbit { value = v ; pos = $startpos }
}
| Lopar; e = expr; Lcpar { e }
;
