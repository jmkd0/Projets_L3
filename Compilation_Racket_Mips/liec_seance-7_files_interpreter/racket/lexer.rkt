#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide gawi-lexer
         keywords-and-operators values-and-names
         (struct-out position))

(define-empty-tokens keywords-and-operators
  (Llet Lwhere Lrarr Llarr Lsc Ldot Lend
   Land Lor Lxor Lnot Lopar Lcpar))

(define-tokens values-and-names
  (Lbool Lident))

(define-lex-abbrev identifier
  (:: alphabetic (:* (:or alphabetic numeric "-" "_"))))

(define gawi-lexer
  (lexer-src-pos
   ((eof)      (token-Lend))
   (whitespace (return-without-pos (gawi-lexer input-port)))
   ("#"        (return-without-pos (comment-lexer input-port)))
   ("&"        (token-Land))
   ("|"        (token-Lor))
   ("^"        (token-Lxor))
   ("!"        (token-Lnot))
   ("("        (token-Lopar))
   (")"        (token-Lcpar))
   ("let"      (token-Llet))
   ("->"       (token-Lrarr))
   ("<-"       (token-Llarr))
   ("where"    (token-Lwhere))
   (";"        (token-Lsc))
   ("."        (token-Ldot))
   ("0"        (token-Lbool #f))
   ("1"        (token-Lbool #t))
   (identifier (token-Lident (string->symbol lexeme)))
   (any-char   (begin
                 (eprintf "Lexer: unrecognized char '~a' at line ~a col ~a.\n"
                          lexeme (position-line start-pos) (position-col start-pos))
                 (exit 1)))))

(define comment-lexer
  (lexer
   ("\n"     (gawi-lexer input-port))
   (any-char (comment-lexer input-port))))
