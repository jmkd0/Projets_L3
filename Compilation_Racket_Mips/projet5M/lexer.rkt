#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide gawi-lexer
         keywords-and-operators values-and-names
         (struct-out position))

(define-empty-tokens keywords-and-operators
  (Lend Ladd Lsub Lmul Ldiv Lopar Lcpar Loacc Lcacc 
    Lsc Lco Lassign Lneq Lgt Llt Lgte Llte Land Lxor Lnot Lor Leq Ldef Lreturn Lif 
     Llarr ))

(define-tokens values-and-names
  (Lbool Lnum Lident))

(define-lex-abbrev identifier
  (:: alphabetic (:* (:or alphabetic numeric "-" "_"))))

(define gawi-lexer
  (lexer-src-pos
   [(eof)      (token-Lend)]
   [whitespace (return-without-pos (gawi-lexer input-port))]
   ["#"        (return-without-pos (comment-lexer input-port))]
   ["+"        (token-Ladd)]
    ["-"        (token-Lsub)]
    ["*"        (token-Lmul)]
    ["/"        (token-Ldiv)]
    ["("        (token-Lopar)]
    [")"        (token-Lcpar)]
    ["{"        (token-Loacc)]
    ["}"        (token-Lcacc)]
    [";"        (token-Lsc)]
    [","        (token-Lco)]
    ["="        (token-Lassign)]
    ["!="       (token-Lneq)]
    [">"        (token-Lgt)]
    ["<"        (token-Llt)]
    ["<="       (token-Llte)]
    [">="       (token-Lgte)]
    ["true"     (token-Lbool #t)]
    ["false"    (token-Lbool #f)]
    ["^"        (token-Lxor)]
    ["!"        (token-Lnot)]
    ["=="       (token-Leq)]
    ("if"       (token-Lif))
    ["def"      (token-Ldef)]
    ["return"   (token-Lreturn)]

   ["&&"        (token-Land)]
   ["||"        (token-Lor)]
   ("<-"       (token-Llarr))
   [identifier (token-Lident (string->symbol lexeme))]
   [(:+ numeric)(token-Lnum (string->number lexeme))]
   (any-char   (begin
                 (eprintf "Lexer: unrecognized char '~a' at line ~a col ~a.\n"
                          lexeme (position-line start-pos) (position-col start-pos))
                 (exit 1)))))

(define comment-lexer
  (lexer
   ("\n"     (gawi-lexer input-port))
   (any-char (comment-lexer input-port))))
