```
$make test

"comparing swapcontext with direct procedure call and pthreads"
./compare
func call avg cycles:   100.556400
longjmp avg cycles:     154.278600      (1.534249 times slower than direct procedure calls)
swapcontext avg cycles: 2218.746600     (14.381428 times slower than direct longjmp)
pthread avg cycles:     58976.268800    (26.580894 times slower than swapcontext)

```
