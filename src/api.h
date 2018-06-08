
#pragma once

#include "request.h"

namespace midware {
  namespace service {

class API {
public:
    static int Init();
    static int Destroy();

    static void Process(Request* request);

private:
};

}
}

