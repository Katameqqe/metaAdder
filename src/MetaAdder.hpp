//
//  MetaAdder.hpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#pragma once

#include <memory>

#include "MetaProcessor.hpp"
#include "MetaError.hpp"

/*
    public interface
*/
class MetaAdder
{
public:
    using PtrT = std::shared_ptr<MetaAdder>;

    static PtrT create(const std::string &aPath, MetaError::PtrT *anError);

    bool getClassification(std::string *aClassificationValue, MetaError::PtrT *anError);
    bool setClassification(const std::string &aClassification, MetaError::PtrT *anError);

private:
    MetaAdder();

    std::shared_ptr<MetaProcessor> _processor;
};
