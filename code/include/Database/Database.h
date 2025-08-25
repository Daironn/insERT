#pragma once
#include <mutex>
#include <unordered_map>

#include "IDatabase.h"
#include "common/common.h"

namespace insERT::object
{
    class IBusinessObject;
}

namespace insERT::database
{
    class Database : public IDatabase
    {
        std::unordered_map<common::Id, std::shared_ptr<object::IBusinessObject>> m_storage;

        mutable std::mutex mtx;
        common::Id         m_nextId;

        template <typename T, typename... Args> std::shared_ptr<T> CreateImpl(Args&&... args)
        {
            std::scoped_lock lock(mtx);

            auto obj                = std::make_shared<T>(m_nextId++, std::forward<Args>(args)...);
            m_storage[obj->GetId()] = obj;
            return obj;
        }

      public:
        Database();

        std::shared_ptr<object::IBusinessObject> Create(common::ObjectType type,
                                                        const std::string& payload) override;
        std::shared_ptr<object::IBusinessObject> Fetch(common::Id id) override;
        bool Update(const std::shared_ptr<object::IBusinessObject>& obj) override;
        bool Delete(common::Id id, std::optional<common::Id> currentUserId = std::nullopt) override;
        std::vector<common::Id> GetAllIds() const override;
    };
} // namespace insERT::database
