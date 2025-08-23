#pragma once

#include "BusinessObject/IBusinessObject.h"

class Document : public IBusinessObject
{
    long              m_documentId{};
    std::string       m_name;
    std::vector<long> m_productIds;

  public:
    Document(long documentId, const std::string& productNumber);

    long               GetId() const override;
    ObjectType         GetType() const override;
    const std::string& GetName() const override;

    void                     AddProduct(long productId);
    const std::vector<long>& GetProducts() const;
};
