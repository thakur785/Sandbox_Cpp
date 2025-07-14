#include<iostream>
#include<coroutine>
#include <chrono>
#include<thread>
#include<future>

struct Timer {
   std::chrono::milliseconds duration;
   Timer(std::chrono::milliseconds d) : duration(d) {}

   bool await_ready() const { return false; }

   void await_suspend(std::coroutine_handle<> h) const {
      // Use std::async with deferred launch for better resource management
      std::async(std::launch::async, [h, this]() {
         std::this_thread::sleep_for(duration);
         h.resume();
         });
   }

   void await_resume() const {}
};

struct Task {
   struct promise_type {
      Task get_return_object() { return {}; }
      std::suspend_never initial_suspend() { return {}; }
      std::suspend_never final_suspend() noexcept { return {}; }
      void return_void() {}
      void unhandled_exception() { std::terminate(); }
   };

   Task run() {
      std::cout << "Starting timer...\n";
      co_await Timer{ std::chrono::seconds(2) };
      std::cout << "Timer finished.\n";
      co_return;
   }
};

int main() {
   std::cout << "Custom Awaitable Types Demo\n";
   std::cout << "============================\n";
   Task task;
   task.run();

   // Give some time for async operations to complete
   std::this_thread::sleep_for(std::chrono::seconds(3));

   std::cout << "Main function completed\n";
   return 0;
}
