#include "BusinessOperations.h"

#include "Database/IDatabase.h"
#include "Document/Document.h"
#include "Product/Product.h"
#include "common/Logger.h"

BusinessOperations::BusinessOperations(std::shared_ptr<IDatabase> db) : m_database(std::move(db)) {}

void BusinessOperations::AddNewDocument(const std::string& docName)
{
    auto base = m_database->Create(ObjectType::ObjectDocument, docName);
    auto doc  = std::dynamic_pointer_cast<Document>(base);
    if (!doc)
    {
        LOG_ERROR("Failed to create document {}", docName);
        return;
    }

    int count = std::rand() % 3 + 1;
    for (int i = 0; i < count; ++i)
    {
        auto pbase   = m_database->Create(ObjectType::ObjectProduct,
                                        "product_" + std::to_string(std::rand() % 100 + 1));
        auto product = std::dynamic_pointer_cast<Product>(pbase);
        if (product)
        {
            doc->AddProduct(product->GetId());
            LOG_INFO("Added product id={} to document id={}", product->GetId(), doc->GetId());
        }
    }

    m_database->Update(doc);
    LOG_INFO("Document created: id={}, number={}", doc->GetId(), doc->GetName());
}

void BusinessOperations::FetchMoreDocuments()
{
    for (long id : {1000, 2000, 3000})
        m_database->Create(ObjectType::ObjectDocument, "fetched_" + std::to_string(id));
    LOG_INFO("FetchMoreDocuments completed");
}

bool BusinessOperations::RemoveAllDocuments(std::optional<Id> currentUserId)
{
    auto            ids = m_database->GetAllIds();
    std::vector<Id> toDelete;
    for (auto id : ids)
    {
        auto obj = m_database->Fetch(id);
        if (obj && obj->GetType() == ObjectType::ObjectDocument)
            toDelete.push_back(id);
    }
    bool allOk = true;
    for (auto id : toDelete)
        if (!m_database->Delete(id, currentUserId))
        {
            LOG_WARNING("Failed to delete document id={}", id);
            allOk = false;
        }
    LOG_INFO("RemoveAllDocuments completed (requested {} items)", toDelete.size());
    return allOk;
}
