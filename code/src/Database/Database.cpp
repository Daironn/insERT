#include "Database.h"

#include "AppUser/AppUser.h"
#include "Document/Document.h"
#include "Product/Product.h"
#include "common/Logger.h"

Database::Database()
{
    m_nextId                 = 1;
    auto admin               = std::make_shared<AppUser>(ADMIN_USER_ID, "admin");
    m_storage[ADMIN_USER_ID] = admin;
    LOG_INFO("Initialized database with default admin (id={})", ADMIN_USER_ID);
}

std::shared_ptr<IBusinessObject> Database::Create(ObjectType type, const std::string& payload)
{
    try
    {
        std::shared_ptr<IBusinessObject> created;
        switch (type)
        {
        case ObjectType::ObjectAppUser:
            created = CreateImpl<AppUser>(payload);
            break;
        case ObjectType::ObjectProduct:
            created = CreateImpl<Product>(payload);
            break;
        case ObjectType::ObjectDocument:
            created = CreateImpl<Document>(payload);
            break;
        default:
            LOG_ERROR("Database cannot create unsupported ObjectType");
            return nullptr;
        }

        LOG_INFO("Database created object: ({}, {})", ObjectTypeToString(type), created->GetId());
        return created;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Database create exception for type={} and name={} : {}",
                  ObjectTypeToString(type),
                  payload,
                  e.what());
        return nullptr;
    }
}

std::shared_ptr<IBusinessObject> Database::Fetch(Id id)
{
    std::scoped_lock lock(mtx);
    try
    {
        auto it = m_storage.find(id);

        if (it == m_storage.end())
        {
            LOG_WARNING("Database fetch failed: Object not found (id={})", id);
            return nullptr;
        }
        LOG_INFO("Database fetched object: ({}, {})",
                 ObjectTypeToString(it->second->GetType()),
                 it->second->GetId());
        return it->second;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Database fetch exception for id={} : {}", id, e.what());
        return nullptr;
    }
}

bool Database::Update(const std::shared_ptr<IBusinessObject>& obj)
{
    if (!obj)
    {
        LOG_ERROR("Database update failed: null object provided");
        return false;
    }

    std::scoped_lock lock(mtx);
    try
    {
        auto it = m_storage.find(obj->GetId());
        if (it == m_storage.end())
        {
            LOG_ERROR("Database cannot update missing object id={}", obj->GetId());
            return false;
        }

        if (it->second->GetType() != obj->GetType())
        {
            LOG_ERROR(
                "Database cannot update object: type mismatch for id={}. Stored={} Provided={}",
                obj->GetId(),
                ObjectTypeToString(it->second->GetType()),
                ObjectTypeToString(obj->GetType()));
            return false;
        }

        it->second = obj;
        LOG_INFO(
            "Database updated object: ({}, {})", ObjectTypeToString(obj->GetType()), obj->GetId());
        return true;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Database update exception for id={} : {}", obj->GetId(), e.what());
        return false;
    }
}

bool Database::Delete(Id id, std::optional<Id> currentUserId)
{
    std::scoped_lock lock(mtx);
    try
    {
        if (id == ADMIN_USER_ID)
        {
            LOG_ERROR("Database attempt to delete admin user id={}", ADMIN_USER_ID);
            return false;
        }
        if (currentUserId && *currentUserId == id)
        {
            LOG_ERROR("Database attempt to delete currently logged user id={}", id);
            return false;
        }

        auto it = m_storage.find(id);
        if (it == m_storage.end())
        {
            LOG_WARNING("Database delete failed: Object not found (id={})", id);
            return false;
        }

        if (it->second->GetType() == ObjectType::ObjectProduct)
        {
            Id pid = it->second->GetId();
            for (auto& [did, obj] : m_storage)
            {
                if (obj->GetType() != ObjectType::ObjectDocument)
                {
                    continue;
                }

                if (auto doc = std::dynamic_pointer_cast<Document>(obj); doc)
                {
                    doc->RemoveProduct(pid);
                }
            }
        }

        LOG_INFO("Database deleted object ({}, {})", ObjectTypeToString(it->second->GetType()), id);
        m_storage.erase(it);
        return true;
    }
    catch (const std::exception& e)
    {
        LOG_ERROR("Database delete exception for id={} : {}", id, e.what());
        return false;
    }
}

std::vector<Id> Database::GetAllIds() const
{
    std::scoped_lock lock(mtx);
    std::vector<Id>  ids;

    for (const auto& [id, obj] : m_storage)
    {
        ids.push_back(id);
    }
    LOG_INFO("Database GetAllIds returned {} items", ids.size());
    return ids;
}
