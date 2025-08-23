#include "Document.h"

#include "Product/Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

Document::Document(long documentId, const std::string& productNumber)
    : m_documentId(documentId), m_name(productNumber)
{
}

long Document::GetId() const
{
    return m_documentId;
}

ObjectType Document::GetType() const
{
    return ObjectType::ObjectDocument;
}

const std::string& Document::GetName() const
{
    return m_name;
}

void Document::AddProduct(long productId)
{
    m_productIds.push_back(productId);
}

const std::vector<long>& Document::GetProducts() const
{
    return m_productIds;
}
