
#pragma once

#include <string>
#include <memory>

#include <Ice/Ice.h>
#include <ice_interface.h>

#include <boost/thread.hpp>
#include <libgo/coroutine.h>
#include <libgo/channel.h>

#include "utils.h"
#include "timer.h"
#include "api.h"

class IceRequest : public Request {
public:
    IceRequest(const std::string& rqstid, const std::string& method, const std::string& rqst, const ::midware::service::idl::AMD_Srv_CallPtr& cb)
      : Request(rqstid, method, rqst), cb_(cb) {
        TIME_SINCE_EPOCH(now);
        time_begin_ = now;
    }
    virtual ~IceRequest() {
    }

protected:
    virtual bool response(bool succ, const std::string& resp) override {
        if(!cb_) return false;
        cb_->ice_response(succ, resp);

        TIME_SINCE_EPOCH(now);
        int64_t elapse = now - time_begin_;

        if(succ) {
            LOG_INFO<<Rqstid()<<" RESULT success method="<<Method()<<" elapse="<<elapse<<" resp.size="<<resp.size();
            LOG_DEBUG<<Rqstid()<<" RESULT success method="<<Method()<<" elapse="<<elapse<<" "<<resp;
        } else {
            LOG_ERROR<<Rqstid()<<" RESULT error method="<<Method()<<" elapse="<<elapse<<" "<<resp;
        }

        return true;
    }

private:
    ::midware::service::idl::AMD_Srv_CallPtr cb_;

    int64_t time_begin_{0};
};

class SrvImpl : public ::midware::service::idl::Srv {
public:

    SrvImpl(int workers=4, int coroutines=400, int queue_size=10000) 
      : workers_(workers), worker_coroutines_(coroutines), running_(true), task_channel_(queue_size) {
        startWorkers();
    }
    virtual ~SrvImpl() {
        running_ = false;
    }

    virtual void Call_async(const ::midware::service::idl::AMD_Srv_CallPtr& cb,
                            const std::string& rqstid,
                            const std::string& method,
                            const std::string& rqst,
                            const ::Ice::Current& = ::Ice::Current()) override {

        std::shared_ptr<Request> request(new IceRequest(rqstid, method, rqst, cb));
        go [this, request] { this->task_channel_ << request; };
    }

    inline void stop() { 
        running_ = false; 
        for(int i=0; i<worker_coroutines_; i++) {
            std::shared_ptr<Request> request;
            this->task_channel_ << request;
        }
    }
    inline bool isRunning() { return running_; }

    void startWorkers() {

        workers_ = _MAX_(1, _MIN_(workers_, 100));
        worker_coroutines_ = _MAX_(workers_*64, _MIN_(worker_coroutines_, workers_*1024));

        for(int i=0; i<worker_coroutines_; i++) {
            go [this, i]() {
                LOG_INFO<<i<<" corouting start";
                std::chrono::duration<int,std::milli> ms(2000);
                std::shared_ptr<Request> request;
                while(this->isRunning()) {
                    bool r = this->task_channel_.TimedPop(request, ms);
                    if(!r) {
                        continue;
                    }
                    if(!request) { // exit
                        break;
                    }
                    midware::service::API::Process(request.get());
                    request->response();
                    request.reset();

                    co_yield;
                }

                request.reset();
                while(!this->task_channel_.TryPop(request)) {
                    if(!request) { // exit
                        break;
                    }
                    midware::service::API::Process(request.get());
                    request->response();
                    request.reset();

                    co_yield;
                }
                LOG_INFO<<i<<" corouting exit";
            };
        }

        for (int i=0; i<workers_; i++) {
            thread_manager_.create_thread([]{ co_sched.RunUntilNoTask(); }); 
        }
    }
    void joinAll() {
        thread_manager_.join_all();
    }

private:
    int workers_{4};
    int worker_coroutines_{400};
    bool running_{true};
    co_chan<std::shared_ptr<Request>> task_channel_;
    boost::thread_group thread_manager_; 
};

