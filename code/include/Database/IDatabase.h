#pragma once
#include <memory>
#include <optional>
#include <vector>

#include "common/common.h"
namespace insERT::object
{
    class IBusinessObject;
}

namespace insERT::database
{
    class IDatabase
    {
      public:
        virtual ~IDatabase() = default;
        virtual std::shared_ptr<object::IBusinessObject> Create(common::ObjectType type,
                                                                const std::string& payload)
            = 0;

        virtual std::shared_ptr<object::IBusinessObject> Fetch(common::Id id) = 0;
        virtual bool Delete(common::Id id, std::optional<common::Id> currentUserId = std::nullopt)
            = 0;
        virtual bool Update(const std::shared_ptr<object::IBusinessObject>& obj) = 0;
        virtual std::vector<common::Id> GetAllIds() const                        = 0;
    };
} // namespace insERT::database
