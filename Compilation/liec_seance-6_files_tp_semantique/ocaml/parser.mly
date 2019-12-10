%{
  open Ast ;;
%}

%token <bool> Lbool
%token <int> Lnum
%token <string> Lvar
%token Ladd Lsub Lmul Ldiv Lopar Lcpar
%token Leq Lneq Llt Lgt Llte Lgte
%token Lif Lthen Lelse
%token Lassign Lsc Lend

%right Lelse
%left Leq Lneq Llt Lgt Llte Lgte
%left Ladd Lsub
%left Lmul Ldiv

%start prog

%type <Ast.p_prog> prog

%%

prog:
| p = nonempty_list(instr); Lend { p }
;

instr:
| v = Lvar; Lassign; e = expr; Lsc {
  Passign { var = v ; expr = e ; pos = $startpos($2) }
}
;

expr:
| n = Lnum {
  Pnum { value = n ; pos = $startpos }
}
| Lsub; n = Lnum {
  Pnum { value = -n ; pos = $startpos }
}
| b = Lbool {
  Pbool { value = b ; pos = $startpos }
}
| n = Lvar {
  Pvar { name = n ; pos = $startpos }
}
| a = expr; Ladd; b = expr {
  Pcall { func = "%add" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lsub; b = expr {
  Pcall { func = "%sub" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lmul; b = expr {
  Pcall { func = "%mul" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Ldiv; b = expr {
  Pcall { func = "%div" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| Lif; c = expr; Lthen; t = expr; Lelse; e = expr {
  Pcond { test = c ; yes = t ; no = e ; pos = $startpos }
}
| a = expr; Leq; b = expr {
  Pcall { func = "%eq" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lneq; b = expr {
  Pcall { func = "%neq" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Llt; b = expr {
  Pcall { func = "%lt" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lgt; b = expr {
  Pcall { func = "%gt" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Llte; b = expr {
  Pcall { func = "%lte" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| a = expr; Lgte; b = expr {
  Pcall { func = "%gte" ; args = [ a ; b ] ; pos = $startpos($2) }
}
| Lopar; e = expr; Lcpar { e }
;
