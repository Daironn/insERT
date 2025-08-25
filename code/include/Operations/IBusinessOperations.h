#pragma once
#include <optional>

#include "common/common.h"

class IBusinessOperations
{
  public:
    virtual ~IBusinessOperations()                                   = default;
    virtual void AddNewDocument(const std::string& docNumber)        = 0;
    virtual void FetchMoreDocuments()                                = 0;
    virtual bool RemoveAllDocuments(std::optional<Id> currentUserId) = 0;
};
