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
      std::cout << "await_suspend called on thread: " << std::this_thread::get_id() << std::endl;

      static thread_local std::vector<std::future<void>> futures;
      futures.emplace_back(std::async(std::launch::async, [h, this]() {
         std::cout << "Timer running on thread: " << std::this_thread::get_id() << std::endl;
         std::this_thread::sleep_for(duration);
         std::cout << "Timer completed, resuming coroutine from thread: " << std::this_thread::get_id() << std::endl;
         h.resume();
         }));

      std::cout << "await_suspend returning immediately" << std::endl;
   }

   void await_resume() const {
      std::cout << "await_resume called on thread: " << std::this_thread::get_id() << std::endl;
   }
};

struct Task {
   struct promise_type {
      Task get_return_object() { return {}; }
      std::suspend_never initial_suspend() { return {}; }
      std::suspend_always final_suspend() noexcept { return {}; }
      void return_void() {}
      void unhandled_exception() { std::terminate(); }
   };

   Task run() {
      std::cout << "Starting timer on thread: " << std::this_thread::get_id() << std::endl;
      co_await Timer{ std::chrono::seconds(2) };
      std::cout << "Timer finished on thread: " << std::this_thread::get_id() << std::endl;
      co_return;
   }
};

int main() {
   std::cout << "Main thread: " << std::this_thread::get_id() << std::endl;
   std::cout << "Custom Awaitable Types Demo\n";
   std::cout << "============================\n";

   Task task;
   task.run();

   std::cout << "Main thread continues immediately after task.run()" << std::endl;

   // Give some time for async operations to complete
   std::this_thread::sleep_for(std::chrono::seconds(3));

   std::cout << "Main function completed\n";
   return 0;
}

