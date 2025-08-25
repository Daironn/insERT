#pragma once
#include <memory>

#include "IBusinessOperations.h"
namespace insERT::database
{
    class IDatabase;
}

namespace insERT::ops
{
    class BusinessOperations : public IBusinessOperations
    {
        std::shared_ptr<database::IDatabase> m_database;

      public:
        explicit BusinessOperations(std::shared_ptr<database::IDatabase> database);
        void AddNewDocument(const std::string& docNumber) override;
        void FetchMoreDocuments() override;
        bool RemoveAllDocuments(std::optional<common::Id> currentUserId) override;
    };
} // namespace insERT::ops
