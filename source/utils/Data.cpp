#include "Data.h"

const char *DATA_FILE_NAME = "./resources/initial_data.json";

Data::Data() {

    std::ifstream iFile(DATA_FILE_NAME);
    if(!iFile.good())
    {
        char snOut[49 + strlen(DATA_FILE_NAME) -2 /* -2 is %s signature */];
        const int snOutSize = sizeof(snOut);
        int requiredSize =
            snprintf(
                snOut,
                sizeof(snOut),
                "Oppening data file failed!\n"
                "Cannot open file '%s'",
                DATA_FILE_NAME
            );
        Support::informAboutToSmallBuffer(requiredSize, snOutSize);

        /// testing
        // for(int i=0; i<snOutSize; i++)
        //     printf("'%c':%d\n", snOut[i], snOut[i]);
        // fflush(stdout);
        Support::displayEndingAppError(snOut);
        exit(1);
    }

    try
    {
        json_ = json::parse(iFile);
    }
    catch(const std::exception &e)
    {
        char snOut[512];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Parse data file to JSON failed!\n"
            "Cannot parse file '%s'\n"
            "JSON error: \n"
            "%s", DATA_FILE_NAME, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayEndingAppError(snOut);
        exit(1);
    }

    iFile.close();
}

json::value_type Data::rawReadValue(const char *name)
{
    json::value_type value;
    try {
        value = json_[name];
    }
    catch (const std::exception &e)
    {
        char snOut[512];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Reading key from JSON failed!\n"
            "Cannot read key '%s'\n"
            "JSON error: \n"
            "%s", name, e.what());
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayEndingAppError(snOut);
        exit(1);
    }
    if(value.is_null())
    {
        char snOut[124];
        int requiredSize = snprintf(
            snOut, sizeof(snOut),
            "Reading key from JSON failed!\n"
            "Cannot read key '%s'", name);
        Support::informAboutToSmallBuffer(requiredSize, sizeof(snOut));
        Support::displayEndingAppError(snOut);
        exit(1);
    }
    return value;
}

json::value_type Data::readValue(const char *name)
{
    return rawReadValue(name);
}

Data *Data::getObject()
{
    static Data data;
    return &data;
}
