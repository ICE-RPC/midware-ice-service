
#pragma once

#include <string>

namespace midware {
  namespace service {

class Config {
public:

    static Config& instance() { 
        static Config config;
        return config;
    }
    virtual ~Config() {}

    bool load(const std::string& cfg_file);

    const std::string getLogDir() const { return log_dir_; }
    bool getLogLevel() const { return log_debug_; }

    int getWorkers() const { return workers_; }
    int getWorkerCoroutines() const { return coroutines_; }
    int getWorkerQueueSize() const { return queue_size_; }

private:
    Config(){}
    Config(const Config& conf);
    void operator=(const Config& conf);

private:

    std::string log_dir_{"./log"};
    bool log_debug_{true};

    int workers_{4};
    int coroutines_{400};
    int queue_size_{2000};

};

}
}
