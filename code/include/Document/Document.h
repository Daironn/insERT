#pragma once

#include "BusinessObject/IBusinessObject.h"

class Document : public IBusinessObject
{
    long              id{};
    std::string       number;
    std::vector<long> productIds;

  public:
    Document(long documentId) : id(documentId) {}
    long       GetId() const override;
    ObjectType GetType() const override;

    const std::string& GetNumber() const;
    void               SetNumber(const std::string& n);

    void                     AddProduct(long productId);
    const std::vector<long>& GetProducts() const;
};
