#pragma once
#include "../xattr/CustomXAttr.hpp"
#include "metaAdder.hpp"

class XAttrMetaAdder : public metaAdder {
public:
    int setMeta(const std::string &filePath, const std::string &name, const std::string &value) override {
        return CustomXAttr::setcxa(filePath, name, value, 0);
    }

    int getMeta(const std::string &filePath, const std::string &name, std::string &value) override {
        return CustomXAttr::getcxa(filePath, name, value);
    }

    int removeMeta(const std::string &filePath, const std::string &name) override {
        return CustomXAttr::removecxa(filePath, name);
    }
    
    int listMeta(const std::string &filePath, std::vector<std::string> &list) override {
        return CustomXAttr::listcxa(filePath, list);
    }
};