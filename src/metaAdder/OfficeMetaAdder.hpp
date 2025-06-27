#pragma once
#include "../OfficeMeta/OfficeMeta.hpp"
#include "metaAdder.hpp"

class OfficeMetaAdder : public metaAdder {
public:
    int setMeta(const std::string &filePath, const std::string &name, const std::string &value) override {
        return OfficeMeta::setProp(filePath, name, value);
    }

    int getMeta(const std::string &filePath, const std::string &name, std::string &value) override {
        return OfficeMeta::getProp(filePath, name, value);
    }

    int removeMeta(const std::string &filePath, const std::string &name) override {
        return OfficeMeta::rmProp(filePath, name);
    }

    int listMeta(const std::string &filePath, std::vector<std::string> &list) override {
        return 0;
    }
};