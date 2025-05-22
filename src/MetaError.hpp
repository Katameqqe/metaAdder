//
//  MetaError.hpp
//  metaAdder
//
//  Created by Danil Korotenko on 5/22/25.
//

#pragma once

#include <memory>
#include <string>

class MetaError
{
public:
    using PtrT = std::shared_ptr<MetaError>;

    MetaError(int aCode, const std::string &aDescription)
        : errorCode(aCode)
        , errorDescription(aDescription)
    {

    }


    int errorCode;
    std::string errorDescription;
};
