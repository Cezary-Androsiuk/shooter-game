#ifndef SUPPORT_H
#define SUPPORT_H

#include <cstdio>
#include <string>
#include <chrono>
#include <math.h>
#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else // __linux__, __APPLE__ || __MACH__, __FreeBSD__, __unix || __unix__
#endif

// #define DISPALY_ENDING_APP_ERROR(message) \
//     Support::displayEndingAppError(snOut, __PRETTY_FUNCTION__);
// #define INFORM_ABOUT_TO_SMALL_BUFFER(requiredSize, gotSize) \
//     Support::informAboutToSmallBuffer(requiredSize, gotSize, __PRETTY_FUNCTION__);


#define LIKELY(expr)    __builtin_expect(!!(expr), true)
#define UNLIKELY(expr)  __builtin_expect(!!(expr), false)

class Support
{
public:
    static void displayApplicationError(std::string message);
    static void informAboutToSmallBuffer(int requiredSize, int availableSize);
    static void emulateLag(int msDelay);
};

#endif // SUPPORT_H
