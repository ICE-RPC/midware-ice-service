
#pragma once

#include <string>

#include "logging.h"

class Request {
public:

    Request(const std::string& rqstid, const std::string& method, const std::string& rqst)
      : rqstid_(rqstid), method_(method), rqst_(rqst) {
    }
    virtual ~Request() {
        response(success_, resp_);
    }

    const std::string& Rqstid() const { return rqstid_; }
    const std::string& Method() const { return method_; }
    const std::string& Rqst() const { return rqst_; }

    void Rqstid(const std::string& rqstid) { rqstid_ = rqstid; }
    void Method(const std::string& method) { method_ = method; }
    void Rqst(const std::string& rqst) { rqst_ = rqst; }


    const bool Success() const { return success_; }
    const std::string& Resp() const { return resp_; }
    const std::string& Error() const { return err_; }

    bool& Success() { return success_; }
    std::string& Resp() { return resp_; }
    std::string& Error() { return err_; }

    virtual bool response() { 
        if(responsed_) return false;
        responsed_ = true;
        return response(success_, resp_); 
    }

protected:
    // override
    virtual bool response(bool succ, const std::string& resp) { 
        return false; 
    }

protected:
    std::string rqstid_;
    std::string method_;
    std::string rqst_;

    bool responsed_{false};
    bool success_{false};
    std::string resp_{"{\"code\":1,\"message\":\"there maybe something wrong\"}"};
    std::string err_{"success"};
};

