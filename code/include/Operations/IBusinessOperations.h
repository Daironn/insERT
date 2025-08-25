#pragma once
#include <optional>

#include "common/common.h"
namespace insERT::ops
{
    class IBusinessOperations
    {
      public:
        virtual ~IBusinessOperations()                                           = default;
        virtual void AddNewDocument(const std::string& docNumber)                = 0;
        virtual void FetchMoreDocuments()                                        = 0;
        virtual bool RemoveAllDocuments(std::optional<common::Id> currentUserId) = 0;
    };

} // namespace insERT::ops
