# C++20/17/14/11
### Coroutines
-	Coroutines are special functions that can have their execution suspended and resumed. To define a coroutine, the co_return, co_await, or co_yield keywords must be present in the function's body. C++20's coroutines are stackless; unless optimized out by the compiler, their state is allocated on the heap