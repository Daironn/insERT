#pragma once
#include <memory>

#include "ISystemOperations.h"

namespace insERT::database
{
    class IDatabase;
}

namespace insERT::ops
{
    class SystemOperations : public ISystemOperations
    {
        std::shared_ptr<database::IDatabase> m_database;

      public:
        explicit SystemOperations(std::shared_ptr<database::IDatabase> database);
        void BackupDocuments() override;
    };
} // namespace insERT::ops
