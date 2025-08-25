#include "SystemOperations.h"

#include "Database/IDatabase.h"
#include "Document/Document.h"
#include "common/Logger.h"

SystemOperations::SystemOperations(std::shared_ptr<IDatabase> db) : m_database(std::move(db)) {}

void SystemOperations::BackupDocuments()
{
    auto ids = m_database->GetAllIds();
    for (auto id : ids)
    {
        auto obj = m_database->Fetch(id);
        if (obj && obj->GetType() == ObjectType::ObjectDocument)
        {
            LOG_INFO("Backup document: id={} name={}", id, obj->GetName());
        }
    }
    LOG_INFO("BackupDocuments finished");
}
