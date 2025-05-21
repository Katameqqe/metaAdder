//
//  MetaAdder.cpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#include "MetaAdder.hpp"

#include "private/XattrMetaProcessor.hpp"

MetaAdder::PtrT MetaAdder::create(const std::string &aPath)
{
    MetaAdder::PtrT result = std::shared_ptr<MetaAdder>(new MetaAdder());

/*
    TODO:
        if exif can read
            ....
        else if office files can read
            ...
        else is pdf can read
            ...
        .........
        else
*/
    if (XattrMetaProcessor::canRead(aPath))
    {
        result->_processor = std::shared_ptr<XattrMetaProcessor>(new XattrMetaProcessor(aPath));
    }

    if (nullptr == result->_processor)
    {
        return nullptr;
    }

    return result;
}

MetaAdder::MetaAdder()
    : _processor(nullptr)
{

}

std::string MetaAdder::getClassification()
{
    if (nullptr != _processor)
    {
        return _processor->getClassification();
    }
    return "";
}

void MetaAdder::setClassification(const std::string &aClassification)
{
    if (nullptr != _processor)
    {
        _processor->setClassification(aClassification);
    }
}
