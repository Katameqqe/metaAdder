#pragma once
#include "../OfficeMeta/OfficeMeta.hpp"
#include "metaAdder.hpp"
#include "MetaLogger.hpp"

class OfficeMetaAdder : public metaAdder {
public:
    OfficeMetaAdder(MetaLogger &logger) : log(logger) {}
    int setMeta(const std::string &filePath, const std::string &name, const std::string &value) override {
        return OfficeMeta::setProp(filePath, name, value, log);
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
private:
    MetaLogger &log;
};