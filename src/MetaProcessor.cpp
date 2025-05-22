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

std::string MetaProcessor::getClassification()
{
    return "";
}

void MetaProcessor::setClassification(const std::string &aPath, const char aType)
{

}

std::string MetaProcessor::path()
{
    return _path;
}
