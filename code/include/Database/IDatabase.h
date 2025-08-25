#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "common/common.h"
class IBusinessObject;

class IDatabase
{
  public:
    virtual ~IDatabase() = default;
    virtual std::shared_ptr<IBusinessObject> Create(ObjectType type, const std::string& payload)
        = 0;

    virtual std::shared_ptr<IBusinessObject> Fetch(Id id)                                 = 0;
    virtual bool            Delete(Id id, std::optional<Id> currentUserId = std::nullopt) = 0;
    virtual bool            Update(const std::shared_ptr<IBusinessObject>& obj)           = 0;
    virtual std::vector<Id> GetAllIds() const                                             = 0;
};
