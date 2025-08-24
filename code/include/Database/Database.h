#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "common/Logger.h"

class IBusinessObject;

class Database
{
  private:
    std::unordered_map<long, std::shared_ptr<IBusinessObject>> storage;
    long                                                       nextId{1};

  public:
    Database();

    template <typename T, typename... Args> T* Create(Args&&... args)
    {
        auto obj              = std::make_unique<T>(nextId++, std::forward<Args>(args)...);
        auto ptr              = obj.get();
        storage[ptr->GetId()] = std::move(obj);

        LOG_INFO("Created object ({}, {})", ObjectTypeToString(ptr->GetType()), ptr->GetId());
        return ptr;
    }
    std::optional<std::shared_ptr<IBusinessObject>> Fetch(long id);
    void                                            Update(const IBusinessObject* obj);
    void                                            Delete(long id);
    const std::vector<long>                         GetAllIds() const;
};
