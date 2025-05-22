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

    std::string readClassification();
    void setClassification(const std::string &aPath, const char aType);

    static constexpr const char *CLASSIFICATION_KEY = "user.classification";

};
