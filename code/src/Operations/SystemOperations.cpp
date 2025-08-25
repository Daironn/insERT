#include "SystemOperations.h"

#include "Database/IDatabase.h"
#include "Document/Document.h"
#include "common/Logger.h"
namespace insERT::ops
{
    SystemOperations::SystemOperations(std::shared_ptr<database::IDatabase> db)
        : m_database(std::move(db))
    {
    }

    void SystemOperations::BackupDocuments()
    {
        auto ids = m_database->GetAllIds();
        for (auto id : ids)
        {
            auto obj = m_database->Fetch(id);
            if (obj && obj->GetType() == common::ObjectType::ObjectDocument)
            {
                logger::LOG_INFO("Backup document: id={} name={}", id, obj->GetName());
            }
        }
        logger::LOG_INFO("BackupDocuments finished");
    }
} // namespace insERT::ops
