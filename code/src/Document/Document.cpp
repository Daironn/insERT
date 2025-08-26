#include "Document.h"

#include <algorithm>

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

void Document::RemoveProduct(long productId)
{
    auto it = std::remove(m_productIds.begin(), m_productIds.end(), productId);
    if (it != m_productIds.end())
    {
        m_productIds.erase(it, m_productIds.end());
        LOG_INFO("Removed product {} from document {}", productId, m_documentId);
    }
    else
    {
        LOG_WARNING("Attempted to remove product {} from document {}, but it was not found",
                    productId,
                    m_documentId);
    }
}

const std::vector<long>& Document::GetProducts() const
{
    return m_productIds;
}
