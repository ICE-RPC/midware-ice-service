
#include "api.h"

#include <string>
#include <vector>
#include <assert.h>

#include "utils.h"
#include "jsons.h"
#include "logging.h"

#include "conf.h"

namespace midware {
  namespace service {

int API::Init() {

    Config& config = Config::instance();

    return 0;
}

int API::Destroy() {

    return 0;
}

bool DIY1(Request* request);
bool DIY2(Request* request);

void API::Process(Request* request) {
    if(!request) return;

    const std::string& rqstid{request->Rqstid()};
    const std::string& method{request->Method()};
    const std::string& rqst{request->Rqst()};
    std::string& err{request->Error()};

    LOG_DEBUG<<rqstid<<" REQUEST "<<method<<" "<<rqst;

    bool succ = false;
    try {
        if(method == "worldcup.matches") {
            succ = DIY1(request);
        } else if (method == "worldcup.match") {
            succ = DIY2(request);
        } else {
            err = "invalid method: " + method;
        }
    } catch(...) {
        err = "unkown exception";
    }

    if(!succ) {
        std::string& resp = request->Resp();
        resp = "{\"rqstid\":\"" + rqstid + "\",\"code\":1,\"message\":\"" + err + "\"}";
    }
}


bool DIY1(Request* request) {
    assert(request != nullptr);

    int res = 0;

    const Config& config = Config::instance();
   
    const std::string& rqstid{request->Rqstid()};
    const std::string& method{request->Method()};
    const std::string& rqst{request->Rqst()};

    bool& succ = request->Success();
    std::string& resp = request->Resp();
    std::string& err = request->Error();

    do {
        rapidjson::Document doc;
        if(!JSON::Parse(doc, rqst) || !doc.IsObject()) {
            err = "invalid request " + rqst;
            break;
        }
        if(rqstid.empty()) {
            std::string _rqstid = JSON::GetString(doc, "rqstid", "");
            if(_rqstid.empty()) _rqstid = RQSTID();
            request->Rqstid(_rqstid);
        }
        // TODO: DIY protocol
        std::string country = JSON::GetString(doc, "country", "");
        std::string lang = JSON::GetString(doc, "lang", "");

        // TODO: DIY process
        resp = "{\"code\":1,\"message\":\"DIY1: hello, world\"}";

        succ = true;
    } while(false);

    return succ;
}

bool DIY2(Request* request) {
    assert(request != nullptr);

    int res = 0;

    const Config& config = Config::instance();
   
    const std::string& rqstid{request->Rqstid()};
    const std::string& method{request->Method()};
    const std::string& rqst{request->Rqst()};

    bool& succ = request->Success();
    std::string& resp = request->Resp();
    std::string& err = request->Error();

    do {
        rapidjson::Document doc;
        if(!JSON::Parse(doc, rqst) || !doc.IsObject()) {
            err = "invalid request " + rqst;
            break;
        }
        if(rqstid.empty()) {
            std::string _rqstid = JSON::GetString(doc, "rqstid", "");
            if(_rqstid.empty()) _rqstid = RQSTID();
            request->Rqstid(_rqstid);
        }
        // TODO: DIY protocol
        long match_id = JSON::GetInt64(doc, "match_id", 0);

        // TODO: DIY process
        resp = "{\"code\":1,\"message\":\"DIY2: hello, world!\"}";

        succ = true;
    } while(false);

    return succ;
}


}
}

