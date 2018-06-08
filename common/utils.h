
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#define NOUSE(v) (void)(v);

#define _MIN_(a, b) (a)>=(b)?(b):(a)
#define _MAX_(a, b) (a)>=(b)?(a):(b)

static std::string RQSTID(int n=20) {
    static char CHARS[] = "abcdefghijklmnopqrstuvwxwz1234567890";
    std::string uuid(n, '0');
    for(size_t i=0; i<uuid.size(); i++)
        uuid[i] = CHARS[rand()%(sizeof(CHARS)-1)];
    return uuid;
}

