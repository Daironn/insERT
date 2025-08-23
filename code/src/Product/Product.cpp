#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

Product::Product(long productId, const std::string& productName) : id(productId), name(productName)
{
}

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
