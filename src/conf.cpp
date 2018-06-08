
#include "conf.h"
#include "logging.h"

namespace midware {
  namespace service {

bool Config::load(const std::string& cfg_file) {

    // TODO: DIY

    log_dir_ = "./log";
    log_debug_ = true;

    workers_ = 4;
    coroutines_ = 400;
    queue_size_ = 2000;

    return true;
}

}
}
