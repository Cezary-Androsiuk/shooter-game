#ifndef DATA_H
#define DATA_H

#include <cstdio>
#include <fstream>

#include "utils/json.hpp"
#include "utils//Support.h"

extern const char *DATA_FILE_NAME;

using json = nlohmann::json;

class Data
{
    Data();
    json::value_type rawReadValue(const char *name);
public:
    json::value_type readValue(const char *name);
    static Data * getObject();



private:
    json json_;
};

#endif // DATA_H
