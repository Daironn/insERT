#pragma once

#include <vector>

#include "BusinessObject/IBusinessObject.h"
namespace insERT::object
{
    class Document : public IBusinessObject
    {
        long              m_documentId{};
        std::string       m_name;
        std::vector<long> m_productIds;

      public:
        Document(long documentId, const std::string& productNumber);

        long               GetId() const override;
        common::ObjectType GetType() const override;
        const std::string& GetName() const override;

        void                     AddProduct(long productId);
        void                     RemoveProduct(long productId);
        const std::vector<long>& GetProducts() const;
    };
} // namespace insERT::object
