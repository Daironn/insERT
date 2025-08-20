#include "Product.h"

void Product::OnFetch()
{
    // m_productName = "product_" + std::to_string(Id());
    // std::cout << "Product fetched: " << m_productName << std::endl;
}

void Product::OnUpdate()
{
    // std::cout << "Product updated: " << m_productName << std::endl;
}

void Product::OnDelete()
{
    // std::cout << "Product deleted: " << m_productName << std::endl;
}

void Product::SetProductName(std::string productName)
{
    // m_productName = productName;
}
