#ifndef SUPPORT_H
#define SUPPORT_H

#include <cstdio>
#include <iostream>
#if defined _WIN32 || defined _WIN64
#include <windows.h>
#else // __linux__, __APPLE__ || __MACH__, __FreeBSD__, __unix || __unix__
#endif


class Support
{
public:
    static void displayEndingAppError(const char *message);
};

#endif // SUPPORT_H
