#pragma once
#include <string>
#include <vector>

class metaAdder {
public:
    virtual ~metaAdder() = default;
    virtual int setMeta(const std::string &filePath, const std::string &name, const std::string &value) = 0;
    virtual int getMeta(const std::string &filePath, const std::string &name, std::string &value) = 0;
    virtual int removeMeta(const std::string &filePath, const std::string &name) = 0;
    virtual int listMeta(const std::string &filePath, std::vector<std::string> &list) = 0;
};