#pragma once

#ifdef WIN32
    #define KRAYO_INLINE __forceinline

    #ifdef KRAYO_EXPORTS
        #define KRAYO_API __declspec(dllexport)
    #else
        #define KRAYO_API __declspec(dllimport)
    #endif
#else
    #define KRAYO_INLINE __attribute__((always_inline))

    #ifdef KRAYO_EXPORTS
        #define KRAYO_API __attribute__((visibility("default")))
    #else // KRAYO_EXPORTS
        #define KRAYO_API
    #endif
#endif
