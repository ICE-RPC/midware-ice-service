
#pragma once 

// DIY: logging

#include <iostream>

#include <stdlib.h>
#include <time.h>

enum log_rank_t {  
   DEBUG,
   INFO,  
   WARNING,  
   ERROR,  
   FATAL  
};
static const char* LOGNAME[] = {
    "DEBUG", 
    "INFO",
    "WARN",
    "ERROR",
    "FATAL"
};

class Logger {
public:  
    Logger(log_rank_t log_rank) : m_log_rank(log_rank) {};  
    ~Logger() {}
    std::ostream& start(log_rank_t log_rank,
                                const std::string& file,
                                const int32_t line,
                                const std::string& function) {
        time_t tm = time(NULL);
        char time_str[128] = {0};
        //char* pts = ctime_r(&tm, time_str);
        struct tm t40;
        struct tm* t4 = localtime_r(&tm, &t40);
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t4);
        return stream(log_rank) <<std::endl
                                << "["<<time_str<<"] "
                                << LOGNAME[log_rank]
                                << " " <<file 
                                << " +" << line
                                << " (" <<function << ") "
                                << std::flush;
    }
private:  
    static std::ostream& stream(log_rank_t log_rank) {
        return std::cerr;
    }     
    log_rank_t m_log_rank;
};  

#define LOG(log_rank)   \
    Logger(log_rank).start(log_rank, __FILE__, __LINE__, __FUNCTION__)  

#define LOG_DEBUG   LOG(DEBUG)
#define LOG_INFO    LOG(INFO)
#define LOG_WARN    LOG(WARN)
#define LOG_WARNING LOG(WARNING)
#define LOG_ERROR   LOG(ERROR)
#define LOG_FATAL   LOG(FATAL)

static void logging_init(const std::string& logdir, bool debug) {
}

static void logging_destroy() {
}

