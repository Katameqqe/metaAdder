#pragma once
#include "../pdfEdit/keyEdit.hpp"
#include "metaAdder.hpp"

class PDFMetaAdder : public metaAdder {
public:
    int setMeta(const std::string &filePath, const std::string &name, const std::string &value) override {
        return keyEdit::appendAfterEOF(filePath, name, value);
    }

    int getMeta(const std::string &filePath, const std::string &name, std::string &value) override {
        return keyEdit::readAfterEOF(filePath, name, value);
    }

    int removeMeta(const std::string &filePath, const std::string &name) override {
        return keyEdit::removeAfterEOF(filePath, name);
    }

    int listMeta(const std::string &filePath, std::vector<std::string> &list) override {
        return keyEdit::listAfterEOF(filePath, list);
    }
};