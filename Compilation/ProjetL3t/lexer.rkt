#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(provide gawi-lexer
         keywords-and-operators values-and-names
         (struct-out position))

(define-empty-tokens keywords-and-operators
  (Lend Ladd Lsub Lmul Ldiv Lopar Lcpar Loacc Lcacc 
    Lsc Lco Lassign Lneq Lgt Llt Lgte Llte Land Lxor Lnot Lor Leq Ldef Lreturn Lif))

(define-tokens values-and-names
  (Lbool Lnum Lvar))

(define-lex-abbrev identifier
  (:: alphabetic (:* (:or alphabetic numeric "-" "_"))))

(define gawi-lexer
  (lexer-src-pos
    [(eof)      (token-Lend)]
    [whitespace  (return-without-pos (gawi-lexer input-port))]
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
    ["&&"       (token-Land)]
    ["^"        (token-Lxor)]
    ["!"        (token-Lnot)]
    ["||"       (token-Lor)]
    ["=="       (token-Leq)]
    ("if"       (token-Lif))
    ["def"      (token-Ldef)]
    ["return"   (token-Lreturn)]
    [identifier (token-Lvar (string->symbol lexeme))]
    [(:+ numeric)(token-Lnum (string->number lexeme))]
    [any-char   (error (format "unrecognized character '~a'" lexeme) start-pos)]
    )
                 )

(define comment-lexer
  (lexer
   ("\n"     (gawi-lexer input-port))
   (any-char (comment-lexer input-port))))
