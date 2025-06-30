#pragma once

#include <zip.h>
#include <string>
#include <vector>

class OfficeMeta
{
public:
    static int setProp(const std::string &filePath, const std::string &name, const std::string &value);
    static int getProp(const std::string &filePath, const std::string &name, std::string &value);
    static int rmProp(const std::string &filePath, const std::string &name);
private:
    static void writeToStr(zip_t *za, const std::string &fileName, std::string &buffer);
};