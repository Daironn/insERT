#pragma once

#include "BusinessObject/BusinessObject.h"

class Product : public BusinessObject
{
  public:
    std::string m_productName;
    Product() = default;

    void OnFetch() override;
    void OnUpdate() override;
    void OnDelete() override;
    void SetProductName(std::string productName);
};
