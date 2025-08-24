#pragma once

#include <string>

#include "BusinessObject/IBusinessObject.h"

class Product : public IBusinessObject
{
    long        id{};
    std::string name;

  public:
    Product(long productId, const std::string& productName);
    long       GetId() const override;
    ObjectType GetType() const override;

    const std::string& GetName() const;
};
