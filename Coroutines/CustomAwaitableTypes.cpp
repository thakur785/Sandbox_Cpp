#include<iostream>
#include<coroutine>
#include <chrono>
#include<thread>

struct Timer {
   std::chrono::milliseconds duration;
   Timer(std::chrono::milliseconds d) : duration(d) {}
   bool await_ready() const { return false; }
   bool await_suspend(std::coroutine_handle<> h) const {
      std::this_thread::sleep_for(duration);
      h.resume();
      //return false; // No need to destroy the coroutine handle
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

   void run() {
      std::cout << "Starting timer...\n";
      co_await Timer{ std::chrono::seconds(2) };
      std::cout << "Timer finished.\n";
   }
};


int main() {
   std::cout << "Custom Awaitable Types Demo\n";
   std::cout << "============================\n";
   Task task;
   task.run();
   std::cout << "Main function completed\n";
   return 0;
}