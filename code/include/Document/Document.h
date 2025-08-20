#pragma once

#include "BusinessObject/BusinessObject.h"

class Product;

class Document : public BusinessObject
{
  private:
    std::string          m_documentNumber;
    std::vector<Product> m_products;

  public:
    Document() = default;

    void OnFetch() override;
    void OnUpdate() override;
    void OnDelete() override;
    void SendDocumentProductsEmail() override;

    void SetDocumentNumber(std::string documentNumber);

    void AddProduct(const Product& product);
};
