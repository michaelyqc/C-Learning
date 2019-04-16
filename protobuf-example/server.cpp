#include <iostream>

#include <service.ph.h>

using namespace std;


class EchoServiceImpl : public EchoService {
  public:
    EchoServiceImpl() {}

    virtual void Foo(::google::protobuf::RpcController* controller,
                      const ::FooRequest* request,
                      ::FooResponse* response,
                      ::google::protobuf::Closure* done) {

        std::string str = request->text();
        std::string tmp = str;
        
        for (int i = 1; i < request->times(); i++)
          str += (" " + tmp);
        
        response->set_text(str);
        response->set_result(true);
        
        if (done)
          done->Run();
    }   
};



int main(int argc, char *argv[]) {
    RpcServer rpc_server;
   
    EchoServiceImpl *impl = new EchoServiceImpl();
    rpc_server.RegisterService(impl);
    
    rpc_server.Start();
  
    return 0;
}
