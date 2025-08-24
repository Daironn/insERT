#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

enum ObjectType
{
    ObjectAppUser = 0,
    ObjectDocument,
    ObjectProduct
};

inline std::string ObjectTypeToString(ObjectType type)
{
    switch (type)
    {
    case ObjectAppUser:
        return "AppUser";
    case ObjectDocument:
        return "Document";
    case ObjectProduct:
        return "Product";
    default:
        return "Unknown";
    }
}

class IBusinessObject
{
  public:
    virtual long       GetId() const   = 0;
    virtual ObjectType GetType() const = 0;
};
