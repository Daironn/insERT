#pragma once

#include <string>

#include "common/common.h"


class IBusinessObject
{
  public:
    virtual long               GetId() const   = 0;
    virtual ObjectType         GetType() const = 0;
    virtual const std::string& GetName() const = 0;
};
