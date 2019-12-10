#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide tokenize
         keywords-and-operators
         names-and-values)

(define-empty-tokens keywords-and-operators
  (Ladd Lsub Lmul Ldiv Lopar Lcpar
   Leq Lneq Llt Lgt Llte Lgte
   Lif Lthen Lelse
   Lassign Lsc Lend))

(define-tokens names-and-values
  (Lvar Lnum Lbool))

(define tokenize
  (lexer-src-pos
   ((eof)           (token-Lend))
   (whitespace      (return-without-pos (tokenize input-port)))
   ("#"             (return-without-pos (comment input-port)))
   ("+"             (token-Ladd))
   ("-"             (token-Lsub))
   ("*"             (token-Lmul))
   ("/"             (token-Ldiv))
   ("("             (token-Lopar))
   (")"             (token-Lcpar))
   ("=="            (token-Leq))
   ("!="            (token-Lneq))
   ("<"             (token-Llt))
   (">"             (token-Lgt))
   ("<="            (token-Llte))
   (">="            (token-Lgte))
   ("="             (token-Lassign))
   (";"             (token-Lsc))
   ("if"            (token-Lif))
   ("then"          (token-Lthen))
   ("else"          (token-Lelse))
   ("true"          (token-Lbool #t))
   ("false"         (token-Lbool #f))
   ((:+ numeric)    (token-Lnum (string->number lexeme)))
   ((:+ alphabetic) (token-Lvar (string->symbol lexeme)))
   (any-char (begin
               (eprintf "Lexer: invalid char '~a' on line ~a col ~a.\n"
                        lexeme
                        (position-line start-pos)
                        (position-col start-pos))
               (exit 1)))))

(define comment
  (lexer
   ("\n"     (tokenize input-port))
   ((eof)    (tokenize input-port))
   (any-char (comment input-port))))
