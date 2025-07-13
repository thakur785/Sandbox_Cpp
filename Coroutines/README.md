# Coroutines    
-	Coroutines are special functions that can have their execution suspended and resumed. To define a coroutine, the co_return, co_await, or co_yield keywords must be present in the function's body. 
    C++20's coroutines are stackless; unless optimized out by the compiler, their state is allocated on the heap.Basically, a coroutine is a function that can yield control back to the caller without losing its state. 
    This means that a coroutine can pause its execution at a certain point, return a value (or wait for some asynchronous event), and then continue executing from where it left off.

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

## Understanding Coroutines in details:

Very good link to understand basics of coroutines.->
[Understanding C++ Coroutine Implementation](https://medium.com/@AlexanderObregon/understanding-c-coroutine-implementation-8e6e5a2c3edd#id_token=eyJhbGciOiJSUzI1NiIsImtpZCI6ImYxMDMzODYwNzE2ZTNhMmFhYjM4MGYwMGRiZTM5YTcxMTQ4NDZiYTEiLCJ0eXAiOiJKV1QifQ.eyJpc3MiOiJodHRwczovL2FjY291bnRzLmdvb2dsZS5jb20iLCJhenAiOiIyMTYyOTYwMzU4MzQtazFrNnFlMDYwczJ0cDJhMmphbTRsamRjbXMwMHN0dGcuYXBwcy5nb29nbGV1c2VyY29udGVudC5jb20iLCJhdWQiOiIyMTYyOTYwMzU4MzQtazFrNnFlMDYwczJ0cDJhMmphbTRsamRjbXMwMHN0dGcuYXBwcy5nb29nbGV1c2VyY29udGVudC5jb20iLCJzdWIiOiIxMTgyNTQ2OTIzNjIwMzY0MjkxNzMiLCJlbWFpbCI6InRoYWt1cjc4NUBnbWFpbC5jb20iLCJlbWFpbF92ZXJpZmllZCI6dHJ1ZSwibmJmIjoxNzUyMzg1ODI1LCJuYW1lIjoiQW51cmFnIFRoYWt1ciIsInBpY3R1cmUiOiJodHRwczovL2xoMy5nb29nbGV1c2VyY29udGVudC5jb20vYS9BQ2c4b2NJdTRVZ2xaOXVJRzRfdC1weDRsM2lDbUg1Xy1iR1RIMmpScnBnWDZVMlptU2thWWhFPXM5Ni1jIiwiZ2l2ZW5fbmFtZSI6IkFudXJhZyIsImZhbWlseV9uYW1lIjoiVGhha3VyIiwiaWF0IjoxNzUyMzg2MTI1LCJleHAiOjE3NTIzODk3MjUsImp0aSI6IjliOWZkM2MwY2YzNTNhNDA0OTBiYWE5ZGQxMTY2MTk5MTEyOTQ4NTgifQ.ODBg834qWss7fnUzTNQfe_i_cLBk2WYJ4i1Tn3io3ZRA4uDDPazzVoc6TNiPXSx2mDhv6krsdEALIXvITcxn46O60yhTsM2z4M_27Nmizl8T23z-u3c1QOpgTEDAJ7i2r8dHPMFLR9HblCeL629Ev5HiDaQZn9kSgU8L_BVptybWRo-eymb_30UbFiovvKhUnX3e_sHl2IRLmQCPCXn6RQDuhZtm4jH_75cblalWK--9Ktkp5IK2Jib6LBL3roUkrTv-ckbNL6EnJGD7Qg3wAdLXF5veN1I6YKMuDt0SRVgZzF3AuxNJdF0BBamMpDD2EH34xEgVoLG3wxvSOUNmHQ)
