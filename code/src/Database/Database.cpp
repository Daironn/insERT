#include "Database.h"

// TODO: Change CMake to include only needed files
#include "AppUser/AppUser.h"
Database::Database()
{
    auto admin   = std::make_shared<AppUser>(0, "admin");
    m_storage[0] = admin;

    m_nextId = 1;

    LOG_INFO("Initialized database with default admin (id={})", 0);
}

std::shared_ptr<IBusinessObject> Database::Fetch(long id)
{
    auto it = m_storage.find(id);
    if (it == m_storage.end())
    {
        LOG_WARNING("Object not found (id={})", id);
        return nullptr;
    }

    LOG_INFO("Fetched object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    return it->second;
}

void Database::Update(const std::shared_ptr<IBusinessObject>& obj)
{
    if (!obj)
    {
        LOG_ERROR("Update called with null object");
        return;
    }

    if (m_storage.find(obj->GetId()) == m_storage.end())
    {
        LOG_ERROR("Object not found (id={})", obj->GetId());
        return;
    }
    LOG_INFO("Updated object ({}, {})", ObjectTypeToString(obj->GetType()), obj->GetId());
}

void Database::Delete(long id)
{
    auto it = m_storage.find(id);
    if (it == m_storage.end())
    {
        LOG_ERROR("Object not found (id={})", id);
        return;
    }

    LOG_INFO("Deleted object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
    m_storage.erase(it);
}

const std::vector<long> Database::GetAllIds() const
{
    std::vector<long> ids;
    for (const auto& [id, obj] : m_storage)
    {
        ids.push_back(id);
    }
    return ids;
}
