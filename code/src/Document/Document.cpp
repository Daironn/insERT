#include "Document.h"

void OnFetch()
{
    // m_documentNumber = "document_" + std::to_string(Id());

    // // wczytanie powiązanych towarów
    // Product product{};
    // product.Fetch(std::rand() % 100 + 1);
    // AddProduct(product);

    // std::cout << "Document fetched: " << m_documentNumber << std::endl;
}

void OnUpdate()
{
    // // zapisanie powiazanych towarów
    // for (auto& product : m_products)
    //     product.Update();

    // std::cout << "Document updated: " << m_documentNumber << std::endl;
}

void OnDelete()
{
    // // usunięcie powiązanych towarów
    // for (auto& product : m_products)
    //     product.Delete();

    // std::cout << "Document deleted: " << m_documentNumber << std::endl;
}

void SetDocumentNumber(std::string documentNumber)
{
    // m_documentNumber = documentNumber;
}

void AddProduct(const Product& product)
{
    // m_products.push_back(product);
}

void SendDocumentProductsEmail()
{
    // std::string content;
    // for (auto& product : m_products)
    //     content += product.m_productName + "\n";

    // std::cout << "Sending document content email: " << content << std::endl;
}
