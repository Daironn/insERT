#pragma once

#include <string>

#include "common/common.h"
namespace insERT::object
{
    class IBusinessObject
    {
      public:
        virtual long               GetId() const   = 0;
        virtual common::ObjectType GetType() const = 0;
        virtual const std::string& GetName() const = 0;
    };
} // namespace insERT::object
