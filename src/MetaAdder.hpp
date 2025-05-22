//
//  MetaAdder.hpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/20/25.
//

#pragma once

#include <memory>

#include "MetaProcessor.hpp"

/*
    public interface
*/
class MetaAdder
{
public:
    using PtrT = std::shared_ptr<MetaAdder>;

    static PtrT create(const std::string &aPath);

    std::string getClassification();
    void setClassification(const std::string &aClassification, const char aType);

private:
    MetaAdder();

    std::shared_ptr<MetaProcessor> _processor;
};
