#include <coroutine>
#include <iostream>
#include <optional>

template<typename T>
struct Generator {
   struct promise_type;
   using handle_type = std::coroutine_handle<promise_type>;

   struct promise_type {
      T current_value;
      auto get_return_object() { return Generator{ handle_type::from_promise(*this) }; }
      std::suspend_always initial_suspend() { return {}; }
      std::suspend_always final_suspend() noexcept { return {}; }
      std::suspend_always yield_value(T value) {
         current_value = value;
         return {};
      }
      void return_void() {}
      void unhandled_exception() { std::exit(1); }
   };

   handle_type h;

   Generator(handle_type h) : h(h) {}
   ~Generator() { if (h) h.destroy(); }

   bool next() {
      h.resume();
      return !h.done();
   }

   T value() const { return h.promise().current_value; }
};

// A coroutine that generates numbers from 0 to n
Generator<int> countTo(int n) {
   for (int i = 0; i <= n; ++i)
      co_yield i;
}

int main() {
   std::cout << "Coroutine Generator Demo\n";
   std::cout << "========================\n";

   // Create a generator that counts from 0 to 5
   auto gen = countTo(5);

   std::cout << "Generating numbers from 0 to 5: ";
   while (gen.next()) {
      std::cout << gen.value() << " ";
   }
   std::cout << "\n\n";

   // Create another generator with a different range
   auto gen2 = countTo(3);
   std::cout << "Generating numbers from 0 to 3: ";
   while (gen2.next()) {
      std::cout << gen2.value() << " ";
   }
   std::cout << "\n";

   return 0;
}
