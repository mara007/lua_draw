//
// Created by Marek on 05.07.2019.
//

#pragma once

#include <cstdarg>
#include <cstdio>
#include <iostream>

class logger {
public:
    static void log(const char * msg, ...) {
        char buff[2048];
        va_list args;
        va_start(args, msg);
        vsnprintf(buff, sizeof(buff), msg, args);
        va_end(args);
        std::cout << "[LOG] : " << buff << std::endl;
    }
};

#define LOG(...) logger::log(__VA_ARGS__);
