#include "Document.h"

#include "Product/Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

long Document::GetId() const
{
    return id;
}

ObjectType Document::GetType() const
{
    return ObjectDocument;
}

const std::string& Document::GetNumber() const
{
    return number;
}

void Document::SetNumber(const std::string& n)
{
    number = n;
}

void Document::AddProduct(long productId)
{
    productIds.push_back(productId);
}

const std::vector<long>& Document::GetProducts() const
{
    return productIds;
}
