#include <iostream>
#include <coroutine>
#include <fstream>
#include <string>
#include <thread>
#include <future>


struct AsyncFileRead {
   struct promise_type {
      AsyncFileRead get_return_object() { return {}; }
      std::suspend_never initial_suspend() { return {}; }
      std::suspend_always final_suspend() noexcept { return {}; }
      void return_void() {}
      void unhandled_exception() { std::terminate(); }
   };

   struct Awaiter {
      std::string filename;
      Awaiter(const std::string& filename) : filename(filename) {}
      bool await_ready() const { return false; }
      void await_suspend(std::coroutine_handle<>h)
      {
         std::thread([h, this]() {
            std::ifstream file(filename);
            std::string line;
            while(std::getline(file,line)){
               std::cout << "Read from " << filename << ": " << line << std::endl;
            }
            h.resume();
            }).detach();
      }
      void await_resume() const {}
      
   };
};

AsyncFileRead processFiles() {
   co_await AsyncFileRead::Awaiter("file1.txt");
   co_await AsyncFileRead::Awaiter("file2.txt");
}

int main() {
   processFiles();
   std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for async tasks
}