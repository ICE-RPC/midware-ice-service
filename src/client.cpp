
#include <iostream>

#include <Ice/Ice.h>
#include <ice_interface.h>

#include "utils.h"

class Client : public Ice::Application {
public:

    Client() : Ice::Application(Ice::NoSignalHandling) {
    }

    virtual int run(int argc, char* argv[]) {

        const std::string& service = "midware-ice-service";
        Ice::ObjectPrx obj = communicator()->stringToProxy(service);
        obj = obj->ice_connectionCached(false);
        obj = obj->ice_locatorCacheTimeout(3);

        ::midware::service::idl::SrvPrx server = ::midware::service::idl::SrvPrx::checkedCast(obj);
        if(!server) {
            std::cerr << argv[0] << ": couldn't find server." << std::endl;
            return EXIT_FAILURE;
        }


        std::string method1{"worldcup.matches"};
        std::string rqst1 = "{\"rqstid\":\"adksfjajfk\",\"country\":\"US\",\"lang\":\"en\"}";
        std::string resp1;
        bool succ1 = server->Call(RQSTID(), method1, rqst1, resp1);
        std::cerr<<succ1<<" "<<rqst1<<" "<<resp1<<std::endl;

        std::string method2{"worldcup.match"};
        std::string rqst2 = "{\"rqstid\":\"adksfjajfk\",\"match_id\":12939838}";
        std::string resp2;
        bool succ2 = server->Call(RQSTID(), method2, rqst2, resp2);
        std::cerr<<succ2<<" "<<rqst2<<" "<<resp2<<std::endl;


        return EXIT_SUCCESS;
    }
};

int main(int argc, char* argv[]) {
    Client app;
    return app.main(argc, argv, "ice.admin.conf");
}

