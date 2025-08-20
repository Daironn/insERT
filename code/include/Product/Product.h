#pragma once

#include "BusinessObject/BusinessObject.h"

class Product : public BusinessObject
{
  private:
    std::string m_productName;

  public:
    Product() = default;

    void OnFetch() override;
    void OnUpdate() override;
    void OnDelete() override;
    void SetProductName(std::string productName);
};
