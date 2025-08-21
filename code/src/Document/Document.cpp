#include "Document.h"

#include "Product/Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

void Document::OnFetch()
{
    m_documentNumber = "document_" + std::to_string(Id());

    // wczytanie powiązanych towarów
    Product product{};
    product.Fetch(std::rand() % 100 + 1);
    AddProduct(product);

    LOG_INFO("Document fetched: {}", m_documentNumber);
}

void Document::OnUpdate()
{
    // zapisanie powiazanych towarów
    for (auto& product : m_products)
        product.Update();

    LOG_INFO("Document updated: {}", m_documentNumber);
}

void Document::OnDelete()
{
    // usunięcie powiązanych towarów
    for (auto& product : m_products)
        product.Delete();

    LOG_INFO("Document deleted: {}", m_documentNumber);
}

void Document::SetDocumentNumber(std::string documentNumber)
{
    m_documentNumber = documentNumber;
}

void Document::AddProduct(const Product& product)
{
    m_products.push_back(product);
}

void Document::SendDocumentProductsEmail()
{
    std::string content;
    for (auto& product : m_products)
        content += product.m_productName + "\n";

    LOG_INFO("Sending document content email: {}", content);
}
