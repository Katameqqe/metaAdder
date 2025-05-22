//
//  XattrMetaProcessor.cpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#include "XattrMetaProcessor.hpp"

namespace
{
    const char *CLASSIFICATION_KEY = "user.classification";
}

bool XattrMetaProcessor::canRead(const std::string &aPath)
{
    // TODO: implement check if we can read/set attributes with xattr
    return true;
}

XattrMetaProcessor::XattrMetaProcessor(const std::string &aPath)
    : MetaProcessor(aPath)
{
//    TODO: Any initializations here
}

XattrMetaProcessor::~XattrMetaProcessor()
{
    // TODO: correctly close file, release memory here
}

bool XattrMetaProcessor::getClassification(std::string *aClassificationValue, MetaError::PtrT *anError)
{
    char value[1];
    ssize_t result = getxattr(this->path().c_str(), CLASSIFICATION_KEY, value, 1, 0, 0);
    if (!result)
    {
        if (NULL != anError)
        {
            *anError = std::make_shared<MetaError>(errno, strerror(errno));
        }
        return false;
    }

    return true;
}

bool XattrMetaProcessor::setClassification(const std::string &aClassification, MetaError::PtrT *anError)
{
    char aType = 0;
    int result = setxattr(this->path().c_str(), CLASSIFICATION_KEY, &aType, 1, 0, 0);
    if (!result)
    {
        if (NULL != anError)
        {
            *anError = std::make_shared<MetaError>(errno, strerror(errno));
        }
        return false;
    }
    return true;
}
