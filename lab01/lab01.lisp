;;;; lab01.lisp

(setq *print-base* 16)

(defmacro << (x i) `(ash ,x ,i))
(defmacro >> (x i) `(ash ,x (- ,i)))
(defmacro *and (x y) `(logand ,x ,y))
(defmacro *or (x y) `(logior ,x ,y))
(defmacro *xor (x y) `(logxor ,x ,y))


(<< 5 3)
(>> 8 2)
(>> 1024 2)
(<< -8 2)
(>> -8 2)

(trace ash)
(trace logand)
(trace logior)
(trace logxor)

(setq x #x89ABCDEF
      y #x76543210
      m 3
      n 2)
(*and (>> 
       (<< x (<< n 3))
       (<< m 3))
      (*xor (>> 
             (<< #xff 24) 
             (<< m 3))
            (<< 
             (>> (<< #xff 24) 
                 (<< m 3))
             8)
            )
      )
