//
//  MetaProcessor.cpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#include "MetaProcessor.hpp"

bool MetaProcessor::canRead(const std::string &aPath)
{
    return false;
}

MetaProcessor::MetaProcessor(const std::string &aPath)
    : _path(aPath)
{

}

bool MetaProcessor::getClassification(std::string *aClassificationValue, MetaError::PtrT *anError)
{
    return false;
}

bool MetaProcessor::setClassification(const std::string &aClassification, MetaError::PtrT *anError)
{
    return false;
}

std::string MetaProcessor::path()
{
    return _path;
}
