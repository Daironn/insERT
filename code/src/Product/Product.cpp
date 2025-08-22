#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

long Product::GetId() const
{
    return id;
}

ObjectType Product::GetType() const
{
    return ObjectType::ObjectProduct;
}

const std::string& Product::GetName() const
{
    return name;
}

void Product::SetName(const std::string& n)
{
    name = n;
}
