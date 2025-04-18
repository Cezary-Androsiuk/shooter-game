#include "Support.h"

void Support::displayEndingAppError(std::string message)
{
    fprintf(stderr, "%s\n", message.c_str());
    fflush(stderr);

#if defined _WIN32 || defined _WIN64
    MessageBox(
        NULL,                                   // parent window handle (none)
        message.c_str(),                        // message info
        "Shooter Game load failed",             // window title
        MB_ICONERROR | MB_OK                    // error icon and OK button
        );
#else // __linux__, __APPLE__ || __MACH__, __FreeBSD__, __unix || __unix__
    system("read -p 'Press Enter, to continue...'");
#endif

}

void Support::informAboutToSmallBuffer(int requiredSize, int availableSize)
{
    if(requiredSize >= availableSize)
    {
        fprintf(
            stderr,
            "required buffer size to emplace error text is to small, "
            "required %d bytes, but got %d\n",
            requiredSize +1, availableSize);
        fflush(stderr);
    }
}
