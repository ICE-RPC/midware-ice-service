
#include <string>
#include <thread>
#include <iostream>

#include "logging.h"

#include "conf.h"
#include "ice_srv_imp.h"

using namespace midware::service;

class IceServer : public Ice::Application {
public:

    virtual int run(int argc, char* argv[]) {

        std::string cfg_file = "config.json";
        if(argc > 1) {
            cfg_file = argv[1];
        }
        Config& config = Config::instance();
        bool res = config.load(cfg_file);
        if(!res) {
            std::cerr<<"load config failed "<<cfg_file<<std::endl;
            return EXIT_FAILURE;
        }

        const std::string& logdir = config.getLogDir();
        bool debug = config.getLogLevel();
        logging_init(logdir, debug);

        midware::service::API::Init();

        int workers = config.getWorkers();
        int coroutines = config.getWorkerCoroutines();
        int queue_size = config.getWorkerQueueSize();
        SrvImpl* srv = new SrvImpl(workers, coroutines, queue_size);

        LOG_INFO<<"system start";
        Ice::PropertiesPtr properties = communicator()->getProperties();
        Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter(
                                            properties->getProperty("AdapterIdentity"));
        adapter->add(srv, communicator()->stringToIdentity(
                                            properties->getProperty("ServiceIdentity")));
        adapter->activate();
        communicator()->waitForShutdown();

        srv->stop();
        usleep(100*1000);

        midware::service::API::Destroy();

        LOG_INFO<<"system exit";
        logging_destroy();

        return EXIT_SUCCESS;
    }
};

int main(int argc, char ** argv) {
    IceServer application;
    int status = application.main(argc, argv);
    _exit(status);
}

