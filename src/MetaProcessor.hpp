//
//  MetaProcessor.hpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#pragma once

#include <memory>
#include <string>

#include "MetaError.hpp"

class MetaProcessor
{
public:
    using PtrT = std::shared_ptr<MetaProcessor>;

    static bool canRead(const std::string &aPath);

    MetaProcessor(const std::string &aPath);

    bool getClassification(std::string *aClassificationValue, MetaError::PtrT *anError);
    bool setClassification(const std::string &aClassification, MetaError::PtrT *anError);

    enum class Type : const unsigned char
    {
        USER      =  0b00000001,
        SYSTEM    =  0b00000010,
        SECURITY  =  0b00000100,
        TRUSTED   =  0b00001000,
        OTHER     =  0b00000000,
    };

protected:
    std::string path();

private:
    std::string _path;
};
