#pragma once

#include <string>

#include "BusinessObject/IBusinessObject.h"

class Product : public IBusinessObject
{
    long        m_productId{};
    std::string m_name;

  public:
    Product(long productId, const std::string& productName);
    long               GetId() const override;
    ObjectType         GetType() const override;
    const std::string& GetName() const override;
};
