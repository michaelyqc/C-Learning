#include <iostream>

#include <service.ph.h>

using namespace std;


int main(int argc, char *argv[]) {
    RpcClient client; 
    RpcChannel channel(&client , "127.0.0.1:18669"); 

    EchoService::Stub echo_clt(& channel); 
   
    FooRequest request ; 
    request.set_text ("test1"); 
    request.set_times (1); 
   
    FooResponse response ; 
    RpcController controller ; 
   
    echo_clt.Foo(&controller, &request, &respose，
                  google::protobuf::NewCallback(&FooDone, response2, controller2)); 

    return 0;
}
