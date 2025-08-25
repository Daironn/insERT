#include "BusinessOperations.h"

#include <cstdlib>

#include "Database/IDatabase.h"
#include "Document/Document.h"
#include "Product/Product.h"
#include "common/Logger.h"

namespace insERT::ops
{

    BusinessOperations::BusinessOperations(std::shared_ptr<database::IDatabase> db)
        : m_database(std::move(db))
    {
    }

    void BusinessOperations::AddNewDocument(const std::string& docName)
    {
        auto base = m_database->Create(common::ObjectType::ObjectDocument, docName);
        auto doc  = std::dynamic_pointer_cast<object::Document>(base);
        if (!doc)
        {
            logger::LOG_ERROR("Failed to create document {}", docName);
            return;
        }

        int count = std::rand() % 3 + 1;
        for (int i = 0; i < count; ++i)
        {
            auto pbase   = m_database->Create(common::ObjectType::ObjectProduct,
                                            "product_" + std::to_string(std::rand() % 100 + 1));
            auto product = std::dynamic_pointer_cast<object::Product>(pbase);
            if (product)
            {
                doc->AddProduct(product->GetId());
                logger::LOG_INFO(
                    "Added product id={} to document id={}", product->GetId(), doc->GetId());
            }
        }

        m_database->Update(doc);
        logger::LOG_INFO("Document created: id={}, number={}", doc->GetId(), doc->GetName());
    }

    void BusinessOperations::FetchMoreDocuments()
    {
        for (long id : {1000, 2000, 3000})
            m_database->Create(common::ObjectType::ObjectDocument, "fetched_" + std::to_string(id));
        logger::LOG_INFO("FetchMoreDocuments completed");
    }

    bool BusinessOperations::RemoveAllDocuments(std::optional<common::Id> currentUserId)
    {
        auto                    ids = m_database->GetAllIds();
        std::vector<common::Id> toDelete;
        for (auto id : ids)
        {
            auto obj = m_database->Fetch(id);
            if (obj && obj->GetType() == common::ObjectType::ObjectDocument)
                toDelete.push_back(id);
        }
        bool allOk = true;
        for (auto id : toDelete)
            if (!m_database->Delete(id, currentUserId))
            {
                logger::LOG_WARNING("Failed to delete document id={}", id);
                allOk = false;
            }
        logger::LOG_INFO("RemoveAllDocuments completed (requested {} items)", toDelete.size());
        return allOk;
    }
} // namespace insERT::ops
