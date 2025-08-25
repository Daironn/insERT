#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

Product::Product(long productId, const std::string& productName)
    : m_productId(productId), m_name(productName)
{
}

long Product::GetId() const
{
    return m_productId;
}

ObjectType Product::GetType() const
{
    return ObjectType::ObjectProduct;
}

const std::string& Product::GetName() const
{
    return m_name;
}
