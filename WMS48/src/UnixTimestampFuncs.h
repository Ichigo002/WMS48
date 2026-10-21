
#include <sys/time.h>
#include <time.h>

#ifndef UNIX_TIMESTAMP_FUNCS_CPP
#define UNIX_TIMESTAMP_FUNCS_CPP

inline void setESP32UnixTimeStamp(uint32_t seconds)
{
    struct timeval tv;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;

    settimeofday(&tv, NULL);
}

inline uint32_t getESP32Timestamp() {
    time_t now;
    time(&now);                
    return (uint32_t)now;
}

inline time_t getESP32Time_t() {
    time_t now;
    time(&now);                
    return now;
}

#endif