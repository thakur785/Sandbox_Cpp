#include<iostream>
#include <grpcpp/grpcpp.h>
#include <agrpc/asio_grpc.hpp>
#include <asio/co_spawn.hpp>
#include <asio/use_awaitable.hpp>
#include "helloworld.grpc.pb.h"
using grpc::Server;

int main()
{
   grpc::ChannelArguments channel_args;
   auto channel = grpc::CreateCustomChannel("localhost:50051", grpc::InsecureChannelCredentials(), channel_args);
   
   helloworld::Greeter::Stub stub(channel);
   agrpc::GrpcContext grpc_context;

   asio::co_spawn(
      grpc_context.get_executor(),
      [&stub]() -> asio::awaitable<void> {
         helloworld::HelloRequest request;
         request.set_name("World");
         helloworld::HelloReply reply;
         grpc::ClientContext context;
         auto status = co_await agrpc::request(stub, &helloworld::Greeter::Stub::AsyncSayHello, &context, request, reply);

         if (status.ok()) {
            std::cout << "Greeting: " << reply.message() << std::endl;
         }
         else {
            std::cerr << "RPC failed: " << status.error_message() << std::endl;
         }
      },
      asio::detached
   );
}
grpc_context.run();
return 0;
}