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
    return false;
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

    return "";
}

void XattrMetaProcessor::setClassification()
{
    // TODO: Implement set attributes with xattr
}
