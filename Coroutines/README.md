# Coroutines
-	Coroutines are special functions that can have their execution suspended and resumed. To define a coroutine, the co_return, co_await, or co_yield keywords must be present in the function's body. C++20's coroutines are stackless; unless optimized out by the compiler, their state is allocated on the heap.

## Where Can Coroutines Be Used?
-   Asynchronous I/O	Replace callbacks/promises with cleaner co_await code (like in networking or file I/O)
-   Generators / Iterators	Lazily yield values (e.g., infinite sequences, paging data)
-   Game Loops & Scripting	Pause/resume logic at runtime (e.g., wait for an event or animation)
-   Web servers (e.g., REST APIs)	Use coroutines for non-blocking request handling
-   State Machines	Resume logic between states cleanly
    Simulations	Pause/resume entities (agents, actors, robots) in discrete steps

## When Not to Use Coroutines
-   For small or performance-critical inner loops (overhead may not be worth it).
-   When exception handling is deeply entangled — handling co_await and errors together can be subtle

## limitations of coroutines
-   STL does not yet include full coroutine-based generators (expected in C++26+).
-   You need to write or use a custom coroutine type like the Generator<T> shown above.
-   Coroutines use lower-level concepts like promise_type, suspension points, and handles — not trivial.