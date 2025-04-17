#include "Support.h"

void Support::displayEndingAppError(const char *message)
{
    printf("%s\n", message);
    fflush(stdout);

#if defined _WIN32 || defined _WIN64
    MessageBox(
        NULL,                                   // Handle do okna nadrzędnego (brak)
        message,  // Tekst komunikatu
        "Shooter Game load failed",                      // Tytuł okna
        MB_ICONERROR | MB_OK                   // Ikona błędu i przycisk OK
        );

#else // __linux__, __APPLE__ || __MACH__, __FreeBSD__, __unix || __unix__
    system("read -p 'Press Enter, to continue...'");
#endif

}
