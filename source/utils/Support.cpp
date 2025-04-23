#include "Support.h"

#include <chrono>
#include <filesystem>
#include <thread>

namespace fs = std::filesystem;

void Support::displayApplicationError(std::string message)
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

void Support::emulateLag(int msDelay)
{
    printf("Emulating lag (%dms)... ", msDelay);
    fflush(stdout);

    auto start_time = std::chrono::steady_clock::now();
    const auto duration = std::chrono::milliseconds(msDelay);
    volatile double result = 0.0; // volatile prevent compiler optimization

    int timeCheckCounter = 0;
    while (std::chrono::steady_clock::now() - start_time < duration)
    {
        for (int i=0; i<10'000; i++)
        {
            result += std::sqrt(std::sin(i) * std::cos(i)) + std::log(i + 1);
        }
        timeCheckCounter++;
    }

    printf("\r""emulated lag (%dms)!\n", msDelay);
    fflush(stdout);
}

void Support::makeScreenshot(const sf::RenderTexture *const renderTexture)
{
    /// while geting the texture, renderTexture might change XD
    std::thread thread(Support::makeScreenshotSingleThread, renderTexture);
    thread.detach();
}

void Support::makeScreenshotSingleThread(const sf::RenderTexture * const renderTexture)
{
    std::string screenshotsDirectory = "screenshots/";
    try{
        if (!fs::exists(screenshotsDirectory))
        {
            fs::create_directory(screenshotsDirectory);
        }
    } catch(const std::exception &e){
        Support::displayApplicationError(
            "Failed to create screenshots output folder: '" + screenshotsDirectory + "'");
    }

    const auto now = std::chrono::system_clock::now();
    const auto epoch_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                                now.time_since_epoch()
                                ).count();
    const std::string filename = screenshotsDirectory + std::to_string(epoch_time) + ".png";

    sf::Image image = renderTexture->getTexture().copyToImage();
    image.flipVertically();

    if (!image.saveToFile(filename))
    {
        Support::displayApplicationError("Failed to save screenshot to '" + filename+ "'");
    }
    else
    {
        printf("screenshot saved in '%s'\n", filename.c_str());
        fflush(stdout);
    }
}
