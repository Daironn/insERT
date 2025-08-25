#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"
namespace insERT::object
{
    Product::Product(long productId, const std::string& productName)
        : m_productId(productId), m_name(productName)
    {
    }

    long Product::GetId() const
    {
        return m_productId;
    }

    common::ObjectType Product::GetType() const
    {
        return common::ObjectType::ObjectProduct;
    }

    const std::string& Product::GetName() const
    {
        return m_name;
    }
} // namespace insERT::object
