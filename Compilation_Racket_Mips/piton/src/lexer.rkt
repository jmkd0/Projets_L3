#lang racket/base

(require parser-tools/lex
         (prefix-in : parser-tools/lex-sre)
         racket/string
         racket/list
         racket/match
         racket/function
         "errors.rkt")
(provide main-lexer
         keywords
         delimiters
         operators
         atoms)

;; Tokens
(define-empty-tokens delimiters
  (eof eol indent dedent col comma opar cpar obra cbra arrow))

(define-empty-tokens keywords
  (if else while def return))

(define-empty-tokens operators
  (assign-op land lor lnot add sub mul div eq neq gt lt gte lte))

(define-tokens atoms
  (num str const type name))

;; Regexp abbreviations
(define-lex-abbrev latin_
  (:or (char-range "a" "z")
       (char-range "A" "Z")
       "_"))

(define-lex-abbrev name
  (:: latin_ (:* (:or latin_ numeric))))

(define-lex-abbrev type
  (:or "int" "bool" "str"))

(define-lex-abbrev num
  (:: (:? "-") (:+ numeric)))

(define-lex-abbrev eol-and-indent
  (:: #\newline (:* (:or #\tab #\space))))

(define-lex-abbrev comment
  (:or (:: #\newline (:* (:or #\tab #\space)) "#" (:* (:~ #\newline))) ; full line
       (:: "#" (:* (:~ #\newline))))) ; line end

;; Main lexer
(define main-lexer
  (lexer-src-pos
   ; allow ending without trailing line, even when indented
   [(eof)          (append (handle-indent "\n")
                           (list (token-eof)))]
   [comment        (return-without-pos (main-lexer input-port))]

   ;; Delimiters
   [eol-and-indent (handle-indent lexeme)]
   [":"            (token-col)]
   [","            (token-comma)]
   ["("            (token-opar)]
   [")"            (token-cpar)]
   ["["            (token-obra)]
   ["]"            (token-cbra)]
   ["->"           (token-arrow)]
   ;; Keywords
   ["if"           (token-if)]
   ["else"         (token-else)]
   ["while"        (token-while)]
   ["def"          (token-def)]
   ["return"       (token-return)]
   ;; Operators
   ["and"          (token-land)]
   ["or"           (token-lor)]
   ["not"          (token-lnot)]
   ["="            (token-assign-op)]
   ["+"            (token-add)]
   ["-"            (token-sub)]
   ["*"            (token-mul)]
   ["/"            (token-div)]
   ["=="           (token-eq)]
   ["!="           (token-neq)]
   [">"            (token-gt)]
   ["<"            (token-lt)]
   [">="           (token-gte)]
   ["<="           (token-lte)]
   ;; Atoms
   [num            (token-num (string->number lexeme))]
   ["True"         (token-const 'true)]
   ["False"        (token-const 'false)]
   ; TODO None
   ["\""           (token-str (apply string-append (string-lexer input-port)))]
   [type           (token-type (string->symbol lexeme))]
   [name           (token-name lexeme)]

   [whitespace     (return-without-pos (main-lexer input-port))]
   [any-char       (raise-lexer-error start-pos lexeme)]))

;; String lexer
;; TODO multiline strings, single-quoted strings
(define string-lexer
  (lexer
   ; double quote
   ["\\\"" (cons "\"" (string-lexer input-port))]
   ; slash TODO not working properly
   ["\\\\" (cons "\\" (string-lexer input-port))]
   ; newline
   ["\\n"  (cons "\n" (string-lexer input-port))]
   ; tab
   ["\\t"  (cons "\t" (string-lexer input-port))]
   ; string end
   ["\""   (list)]
   [(eof)  (raise-unterminated-str-error start-pos)]
   [any-char (cons lexeme (string-lexer input-port))]))

;; Indentation
(define indent-stack (list))
;; <returns> tokens to emit (eol, indent,dedent)
;; and updates <indent-stack>
(define (handle-indent eol-and-indent)
  (define indent-string (string-trim eol-and-indent "\n"
                                     #:left? #t #:right? #f #:repeat? #t))
  (let loop ([string indent-string]
             [stack indent-stack])
    (match (cons (empty? stack) (equal? string ""))
      ;; stack and string are not empty
      [(cons #f #f)
       ; indentation string must start with
       ; next indentation piece found in stack
       (define piece (first stack))
       (when (not (string-prefix? string piece))
         (if (string-prefix? piece string)
             (raise-unindent-error)
             (raise-tab-error)))
       ; remove indentation piece from string and continue
       (let ([string (string-trim string piece
                                  #:left? #t #:right? #f #:repeat? #f)])
         (loop string (rest stack)))]

      ;; stack and string are both empty
      [(cons #t #t)
       ; indentation did not change
       (list (token-eol))]

      ;; stack is empty but string isn't yet
      [(cons #t #f)
       ; push one indentation level
       (set! indent-stack (append indent-stack (list string)))
       (list (token-eol)
             (token-indent))]

      ;; string is empty but stack isn't yet
      [(cons #f #t)
       ; pop one or several indentation levels
       (define dedent-count (length stack))
       (set! indent-stack (drop-right indent-stack dedent-count))
       (append (list (token-eol))
               ; emit as many dedent tokens as poped indentation levels
               (build-list dedent-count (const (token-dedent))))])))
