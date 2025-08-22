#include "Database.h"

// TODO: Change CMake to include only needed files
#include "BusinessObject/IBusinessObject.h"

std::optional<IBusinessObject*> Database::Fetch(long id)
{
    auto it = storage.find(id);
    if (it == storage.end())
    {
        LOG_WARNING("Object not found (id={})", id);
        return std::nullopt;
    }

    LOG_INFO("Fetched object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    return it->second.get();
}
void Database::Update(const IBusinessObject* obj)
{
    auto it = storage.find(obj->GetId());
    if (it == storage.end())
        throw std::runtime_error("Object not found");
    LOG_INFO("Updated object ({}, {})", ObjectTypeToString(obj->GetType()), obj->GetId());
}

void Database::Delete(long id)
{
    auto it = storage.find(id);
    if (it == storage.end())
        throw std::runtime_error("Object not found");
    LOG_INFO("Deleted object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    storage.erase(it);
}
