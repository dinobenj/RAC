#ifndef MEMCHECK_SHARED_LIB_H
#define MEMCHECK_SHARED_LIB_H

#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>


#ifdef __cplusplus
    extern "C" {
#endif

#ifdef BUILD_MY_DLL
    #define MEMCHECK_SHARED_LIB __declspec(dllexport)
#else 
    #define MEMCHECK_SHARED_LIB __declspec(dllimport)
#endif


void MEMCHECK_SHARED_LIB pipecommand(std::string strCmd);

#ifdef __cplusplus
    }
#endif

void MEMCHECK_SHARED_LIB SaySomething(std::string str);

#endif //end of DLL