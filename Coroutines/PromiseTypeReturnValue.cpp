#include<iostream>
#include<coroutine>

struct ReturnValue {
   struct promise_type {
      int value;
      ReturnValue get_return_object() { return ReturnValue(this); }
      std::suspend_never initial_suspend() { return {}; }
      std::suspend_always final_suspend() noexcept{ return{}; }
      void return_value(int v) { value = v; }
      void unhandled_exception() { std::terminate(); }
   };
   promise_type* promise;
   ReturnValue(promise_type* p) : promise(p) {}
   int get() { return promise->value; }
};

static ReturnValue computeValue() {
   co_return 50; // Return value from the coroutine
}
int main()
{
   std::cout << "Coroutine Return Value Demo\n";
   std::cout << "============================\n";
   auto rv = computeValue(); // Create the coroutine
   std::cout << "Computed value: " << rv.get() << "\n"; // Get the return value

}