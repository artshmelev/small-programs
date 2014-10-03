#! /usr/bin/guile \
--no-auto-compile -s
!#

(use-modules (srfi srfi-1))

(define (extract p a l)
  (filter (p a) l)
)

(define (qsort l)
  (if (null? l)
    '()
    (append (qsort (extract (lambda (a) (lambda (x) (< x a))) (car l) (cdr l)))
            (list (car l))
            (qsort (extract (lambda (a) (lambda (x) (>= x a))) (car l) (cdr l)))
    )
  )
)


(display (qsort '(2 2 1 10 4)))
(newline)

