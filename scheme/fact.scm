#! /usr/bin/guile \
--no-auto-compile -s
!#

(use-modules (srfi srfi-1))

(define (generate n)
  (define (helper n i)
    (if (= i n)
      (cons i '())
      (cons i (helper n (+ i 1)))
    )
  )
  
  (helper n 1)
)

(define (fact n)
  (fold * 1 (generate n))
)

(display (generate 6))
(newline)
(display (fact 6))
(newline)

