#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

void Product::OnFetch()
{
    m_productName = "product_" + std::to_string(Id());
    LOG_INFO("Product fetched: {}", m_productName);
}

void Product::OnUpdate()
{
    LOG_INFO("Product updated: {}", m_productName);
}

void Product::OnDelete()
{
    LOG_INFO("Product deleted: {}", m_productName);
}

void Product::SetProductName(std::string productName)
{
    m_productName = productName;
}
