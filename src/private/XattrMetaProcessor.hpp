//
//  XattrMetaProcessor.hpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#pragma once

#include "../MetaProcessor.hpp"
#include <sys/xattr.h>

class XattrMetaProcessor : public MetaProcessor
{
public:
    static bool canRead(const std::string &aPath);

    XattrMetaProcessor(const std::string &aPath);
    ~XattrMetaProcessor();

    bool getClassification(std::string *aClassificationValue, MetaError::PtrT *anError);
    bool setClassification(const std::string &aClassification, MetaError::PtrT *anError);
};
