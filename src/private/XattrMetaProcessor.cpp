//
//  XattrMetaProcessor.cpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#include "XattrMetaProcessor.hpp"

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


std::string XattrMetaProcessor::readClassification()
{
    // TODO: implement reading with xattr
    // it is possible to use this->path() if needed
    char value[1];
    getxattr(this->path().c_str(), CLASSIFICATION_KEY, value, 1);
    return std::string(1,value[0]);
}

void XattrMetaProcessor::setClassification(const std::string &aPath, const char aType)
{
    // TODO: Implement set attributes with xattr
    setxattr(this->path().c_str(), CLASSIFICATION_KEY, &aType, 1, 0);
}
