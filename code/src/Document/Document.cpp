#include "Document.h"

#include <algorithm>

#include "Product/Product.h"
#include "common/Logger.h"

namespace insERT::object
{
    Document::Document(long documentId, const std::string& productNumber)
        : m_documentId(documentId), m_name(productNumber)
    {
    }

    long Document::GetId() const
    {
        return m_documentId;
    }

    common::ObjectType Document::GetType() const
    {
        return common::ObjectType::ObjectDocument;
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
            logger::LOG_INFO("Removed product {} from document {}", productId, m_documentId);
        }
        else
        {
            logger::LOG_WARNING(
                "Attempted to remove product {} from document {}, but it was not found",
                productId,
                m_documentId);
        }
    }

    const std::vector<long>& Document::GetProducts() const
    {
        return m_productIds;
    }
} // namespace insERT::object
