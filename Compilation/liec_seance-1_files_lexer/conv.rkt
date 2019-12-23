#lang racket/base

(require racket/port
         racket/string
         parser-tools/lex
         (prefix-in : parser-tools/lex-sre))

(define-lex-abbrev num
  (:: (:+ numeric)
      (:? (:: "." (:+ numeric)))
      (:? whitespace)))

(define (val lexeme unit)
  (string->number (string-trim (string-replace lexeme unit ""))))

(define conv
  (lexer
   (whitespace (conv input-port))

   ((:: num "€")
    (printf "~a F\n" (* (val lexeme "€") 6.55957)))

   ((:: num "F")
    (printf "~a €\n" (/ (val lexeme "F") 6.55957)))


   ((:: num "°C")
    (printf "~a °F\n" (+ (* (val lexeme "°C") 1.8) 32)))

   ((:: num "°F")
    (printf "~a °C\n" (/ (- (val lexeme "°F") 32) 1.8)))


   ((:: num "\"")
    (printf "~acm\n" (* (val lexeme "\"") 2.54)))

   ((:: num "cm")
    (printf "~a\"\n" (/ (val lexeme "cm") 2.54)))


   (any-char (error (format "Unrecognizedd char '~a' at offset ~a."
                            lexeme (position-offset start-pos))))))

(define argv (current-command-line-arguments))
(cond
  ((= (vector-length argv) 1)
   (call-with-input-string (vector-ref argv 0) conv))
  (else
   (eprintf "Usage: racket conv.rkt \"expr\"\n")
   (exit 1)))
