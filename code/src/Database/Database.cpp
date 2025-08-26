#include "Database.h"

#include "AppUser/AppUser.h"
#include "Document/Document.h"
#include "Product/Product.h"
#include "common/Logger.h"

namespace insERT::database
{

    Database::Database()
    {
        m_nextId   = common::ADMIN_USER_ID + 1;
        auto admin = std::make_shared<object::AppUser>(common::ADMIN_USER_ID, "admin");
        m_storage[common::ADMIN_USER_ID] = admin;
        logger::LOG_INFO("Initialized database with default admin (id={})", common::ADMIN_USER_ID);
    }

    std::shared_ptr<object::IBusinessObject> Database::Create(common::ObjectType type,
                                                              const std::string& payload)
    {
        try
        {
            std::shared_ptr<object::IBusinessObject> created;
            switch (type)
            {
            case common::ObjectType::ObjectAppUser:
                created = CreateImpl<object::AppUser>(payload);
                break;
            case common::ObjectType::ObjectProduct:
                created = CreateImpl<object::Product>(payload);
                break;
            case common::ObjectType::ObjectDocument:
                created = CreateImpl<object::Document>(payload);
                break;
            default:
                logger::LOG_ERROR("Database cannot create unsupported common::ObjectType");
                return nullptr;
            }

            logger::LOG_INFO("Database created object: ({}, {})",
                             common::ObjectTypeToString(type),
                             created->GetId());
            return created;
        }
        catch (const std::exception& e)
        {
            logger::LOG_ERROR("Database create exception for type={} and name={} : {}",
                              common::ObjectTypeToString(type),
                              payload,
                              e.what());
            return nullptr;
        }
    }

    std::shared_ptr<object::IBusinessObject> Database::Fetch(common::Id id)
    {
        std::scoped_lock lock(mtx);
        try
        {
            auto it = m_storage.find(id);

            if (it == m_storage.end())
            {
                logger::LOG_WARNING("Database fetch failed: Object not found (id={})", id);
                return nullptr;
            }
            logger::LOG_INFO("Database fetched object: ({}, {})",
                             common::ObjectTypeToString(it->second->GetType()),
                             it->second->GetId());
            return it->second;
        }
        catch (const std::exception& e)
        {
            logger::LOG_ERROR("Database fetch exception for id={} : {}", id, e.what());
            return nullptr;
        }
    }

    bool Database::Update(const std::shared_ptr<object::IBusinessObject>& obj)
    {
        if (!obj)
        {
            logger::LOG_ERROR("Database update failed: null object provided");
            return false;
        }

        std::scoped_lock lock(mtx);
        try
        {
            auto it = m_storage.find(obj->GetId());
            if (it == m_storage.end())
            {
                logger::LOG_ERROR("Database cannot update missing object id={}", obj->GetId());
                return false;
            }

            if (it->second->GetType() != obj->GetType())
            {
                logger::LOG_ERROR(
                    "Database cannot update object: type mismatch for id={}. Stored={} Provided={}",
                    obj->GetId(),
                    common::ObjectTypeToString(it->second->GetType()),
                    common::ObjectTypeToString(obj->GetType()));
                return false;
            }

            it->second = obj;
            logger::LOG_INFO("Database updated object: ({}, {})",
                             common::ObjectTypeToString(obj->GetType()),
                             obj->GetId());
            return true;
        }
        catch (const std::exception& e)
        {
            logger::LOG_ERROR("Database update exception for id={} : {}", obj->GetId(), e.what());
            return false;
        }
    }

    bool Database::Delete(common::Id id, std::optional<common::Id> currentUserId)
    {
        std::scoped_lock lock(mtx);
        try
        {
            if (id == common::ADMIN_USER_ID)
            {
                logger::LOG_ERROR("Database attempt to delete admin user id={}",
                                  common::ADMIN_USER_ID);
                return false;
            }
            if (currentUserId && *currentUserId == id)
            {
                logger::LOG_ERROR("Database attempt to delete currently logged user id={}", id);
                return false;
            }

            auto it = m_storage.find(id);
            if (it == m_storage.end())
            {
                logger::LOG_WARNING("Database delete failed: Object not found (id={})", id);
                return false;
            }

            if (it->second->GetType() == common::ObjectType::ObjectProduct)
            {
                common::Id pid = it->second->GetId();
                for (auto& [did, obj] : m_storage)
                {
                    if (obj->GetType() != common::ObjectType::ObjectDocument)
                    {
                        continue;
                    }

                    if (auto doc = std::dynamic_pointer_cast<object::Document>(obj); doc)
                    {
                        doc->RemoveProduct(pid);
                    }
                }
            }

            logger::LOG_INFO("Database deleted object ({}, {})",
                             common::ObjectTypeToString(it->second->GetType()),
                             id);
            m_storage.erase(it);
            return true;
        }
        catch (const std::exception& e)
        {
            logger::LOG_ERROR("Database delete exception for id={} : {}", id, e.what());
            return false;
        }
    }

    std::vector<common::Id> Database::GetAllIds() const
    {
        std::scoped_lock        lock(mtx);
        std::vector<common::Id> ids;

        for (const auto& [id, obj] : m_storage)
        {
            ids.push_back(id);
        }
        logger::LOG_INFO("Database GetAllIds returned {} items", ids.size());
        return ids;
    }
} // namespace insERT::database
