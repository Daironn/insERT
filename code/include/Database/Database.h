#pragma once
#include <mutex>
#include <unordered_map>

#include "IDatabase.h"
#include "common/common.h"

class IBusinessObject;

class Database : public IDatabase
{
    mutable std::mutex                                       mtx;
    std::unordered_map<Id, std::shared_ptr<IBusinessObject>> m_storage;
    Id                                                       m_nextId;

    template <typename T, typename... Args> std::shared_ptr<T> CreateImpl(Args&&... args)
    {
        std::scoped_lock lock(mtx);

        auto obj                = std::make_shared<T>(m_nextId++, std::forward<Args>(args)...);
        m_storage[obj->GetId()] = obj;
        return obj;
    }

  public:
    Database();

    std::shared_ptr<IBusinessObject> Create(ObjectType type, const std::string& payload) override;
    std::shared_ptr<IBusinessObject> Fetch(Id id) override;
    bool                             Update(const std::shared_ptr<IBusinessObject>& obj) override;
    bool            Delete(Id id, std::optional<Id> currentUserId = std::nullopt) override;
    std::vector<Id> GetAllIds() const override;
};
