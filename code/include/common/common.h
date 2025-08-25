#pragma once
#include <string>

using Id                          = long;
inline constexpr Id ADMIN_USER_ID = 0;

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
