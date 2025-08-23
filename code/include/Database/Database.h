#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "common/Logger.h"

class IBusinessObject;

class Database
{
  private:
    std::unordered_map<long, std::shared_ptr<IBusinessObject>> m_storage;
    long                                                       m_nextId;

  public:
    Database();

    template <typename T, typename... Args> std::shared_ptr<T> Create(Args&&... args)
    {
        auto obj                = std::make_shared<T>(m_nextId++, std::forward<Args>(args)...);
        m_storage[obj->GetId()] = obj;
        LOG_INFO("Created object ({}, {})", ObjectTypeToString(obj->GetType()), obj->GetId());
        return obj;
    }

    std::shared_ptr<IBusinessObject> Fetch(long id);
    void                             Update(const std::shared_ptr<IBusinessObject>& obj);
    void                             Delete(long id);
    const std::vector<long>          GetAllIds() const;
};
