#include <memory>
#include <stdexcept>
#include <unordered_map>

#include "common/Logger.h"

class IBusinessObject;

class Database
{
  private:
    std::unordered_map<long, std::unique_ptr<IBusinessObject>> storage;
    long                                                       nextId{1};

  public:
    template <typename T> T* Create()
    {
        auto obj              = std::make_unique<T>(nextId++);
        auto ptr              = obj.get();
        storage[ptr->GetId()] = std::move(obj);

        LOG_INFO("Created object ({}, {})", ObjectTypeToString(ptr->GetType()), ptr->GetId());
        return ptr;
    }
    std::optional<IBusinessObject*> Fetch(long id);
    void                            Update(const IBusinessObject* obj);
    void                            Delete(long id);
};
