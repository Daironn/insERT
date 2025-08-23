#include "Database.h"

// TODO: Change CMake to include only needed files
#include "AppUser/AppUser.h"
Database::Database()
{
    auto admin = std::make_unique<AppUser>(0, "admin");
    storage[0] = std::move(admin);

    nextId = 1;

    LOG_INFO("Initialized database with default admin (id=0)");
}

std::optional<std::shared_ptr<IBusinessObject>> Database::Fetch(long id)
{
    auto it = storage.find(id);
    if (it == storage.end())
    {
        LOG_WARNING("Object not found (id={})", id);
        return std::nullopt;
    }

    LOG_INFO("Fetched object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    return it->second; // it->second jest shared_ptr<IBusinessObject>
}

void Database::Update(const IBusinessObject* obj)
{
    if (storage.find(obj->GetId()) == storage.end())
    {
        LOG_ERROR("Object not found (id={})", obj->GetId());
        return;
        // throw std::runtime_error("Object not found");
    }
    LOG_INFO("Updated object ({}, {})", ObjectTypeToString(obj->GetType()), obj->GetId());
}

void Database::Delete(long id)
{
    auto it = storage.find(id);
    if (storage.find(id) == storage.end())
    {
        LOG_ERROR("Object not found (id={})", id);
        return;
        // throw std::runtime_error("Object not found");
    }
    LOG_INFO("Deleted object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    storage.erase(it);
}

const std::vector<long> Database::GetAllIds() const
{
    std::vector<long> ids;
    for (const auto& [id, obj] : storage)
    {
        ids.push_back(id);
    }
    return ids;
}
