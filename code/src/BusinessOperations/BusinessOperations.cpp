#include "BusinessOperations.h"

#include "AppUser.h"
#include "Document.h"
#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

BusinessOperations::BusinessOperations() : m_user(std::make_shared<AppUser>(0)) {}

void BusinessOperations::FetchUser(int userId)
{
    // m_user->Fetch(userId);
}

void BusinessOperations::AddNewDocument()
{
    // LOG_INFO("Adding new document...");
    // Document document{};
    // {
    //     document.InitNew();
    //     document.SetDocumentNumber("document_" + std::to_string(std::rand() % 100 + 1));

    //     for (int j = 0; j < std::rand() % 3 + 1; j++)
    //     {
    //         Product product{};
    //         product.InitNew();
    //         product.SetProductName("product_" + std::to_string(std::rand() % 100 + 1));
    //         document.AddProduct(product);
    //     }

    //     document.Update();
    // }

    // m_documents.push_back(std::make_shared<Document>(document));
}

void BusinessOperations::FetchMoreDocument()
{
    // // warunek symulujący, czy dokumenty są gotowe do pobrania (np. z webservice'u)
    // if (DocumentsReady())
    //     return;

    // for (long id : {1000, 2000, 3000})
    // {
    //     Document document{};
    //     document.Fetch(id);
    //     m_documents.push_back(std::make_shared<Document>(document));
    // }
}

void BusinessOperations::RemoveAllDocuments()
{
    // // warunek symulujący uprawnienie, czy użytkownik ma id = 1 (administrator)
    // if (m_user->Id() != 1)
    //     return;

    // for (auto& document : m_documents)
    //     document->Delete();

    // m_documents.clear();
}

bool BusinessOperations::DocumentsReady()
{
    return std::rand() % 4 > 0;
}
