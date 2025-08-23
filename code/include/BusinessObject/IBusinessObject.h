#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

enum class ObjectType
{
    ObjectAppUser = 0,
    ObjectDocument,
    ObjectProduct
};

inline std::string ObjectTypeToString(ObjectType type)
{
    switch (type)
    {
    case ObjectType::ObjectAppUser:
        return "AppUser";
    case ObjectType::ObjectDocument:
        return "Document";
    case ObjectType::ObjectProduct:
        return "Product";
    default:
        return "Unknown";
    }
}

class IBusinessObject
{
  public:
    virtual long               GetId() const   = 0;
    virtual ObjectType         GetType() const = 0;
    virtual const std::string& GetName() const = 0;
};
