#pragma once
#include <memory>

#include "ISystemOperations.h"

class IDatabase;

class SystemOperations : public ISystemOperations
{
    std::shared_ptr<IDatabase> m_database;

  public:
    explicit SystemOperations(std::shared_ptr<IDatabase> database);
    void BackupDocuments() override;
};
