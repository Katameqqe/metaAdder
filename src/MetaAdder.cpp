//
//  MetaAdder.cpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#include "MetaAdder.hpp"

#include "private/XattrMetaProcessor.hpp"

MetaAdder::PtrT MetaAdder::create(const std::string &aPath, MetaError::PtrT *anError)
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
        if (anError!=NULL)
        {
            *anError = std::shared_ptr<MetaError>(new MetaError(0, "canno create meta processor")); // write more detailed description. why we cannot create meta processor. May be something worng with path. may be file is corrupted.
        }
        return nullptr;
    }

    return result;
}

MetaAdder::MetaAdder()
    : _processor(nullptr)
{

}

bool MetaAdder::getClassification(std::string *aClassificationValue, MetaError::PtrT *anError)
{
    if (nullptr != _processor)
    {
        return _processor->getClassification(aClassificationValue, anError);
    }

    if (NULL != anError)
    {
        *anError = std::shared_ptr<MetaError>(new MetaError(0 , "Metaprocessor is null"));
    }

    return false;
}

bool MetaAdder::setClassification(const std::string &aClassification, MetaError::PtrT *anError)
{
    if (nullptr != _processor)
    {
        return _processor->setClassification(aClassification, anError);
    }

    if (NULL != anError)
    {
        *anError = std::shared_ptr<MetaError>(new MetaError(0 , "Metaprocessor is null"));
    }
    return false;
}
