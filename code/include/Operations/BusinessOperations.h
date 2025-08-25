#pragma once
#include <memory>

#include "IBusinessOperations.h"

class IDatabase;

class BusinessOperations : public IBusinessOperations
{
    std::shared_ptr<IDatabase> m_database;

  public:
    explicit BusinessOperations(std::shared_ptr<IDatabase> database);
    void AddNewDocument(const std::string& docNumber) override;
    void FetchMoreDocuments() override;
    bool RemoveAllDocuments(std::optional<Id> currentUserId) override;
};
