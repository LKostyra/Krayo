#pragma once

#ifdef WIN32
    #ifdef KRAYO_EXPORTS
        #define KRAYO_API __declspec(dllexport)
    #else
        #define KRAYO_API __declspec(dllimport)
    #endif
#else
    #ifdef KRAYO_EXPORTS
        #define KRAYO_API __attribute__((visibility("default")))
    #else // KRAYO_EXPORTS
        #define KRAYO_API
    #endif
#endif
