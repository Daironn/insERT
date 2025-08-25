#include "App.h"

#include "AppUser.h"
#include "BusinessOperations.h"
#include "Database.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

namespace insERT::app
{
    App::App(std::shared_ptr<database::IDatabase>      db,
             std::shared_ptr<ops::IBusinessOperations> businessOps)
        : m_database(std::move(db)), m_businessOps(std::move(businessOps))
    {
    }

    void App::Login(common::Id userId)
    {
        auto obj = m_database->Fetch(userId);
        if (!obj)
        {
            logger::LOG_ERROR("Login failed: User id={} not found", userId);
            return;
        }
        if (obj->GetType() != common::ObjectType::ObjectAppUser)
        {
            logger::LOG_ERROR("Login failed: Object id={} is not an AppUser", userId);
            return;
        }
        auto user = std::dynamic_pointer_cast<object::AppUser>(obj);
        if (!user)
        {
            logger::LOG_ERROR("Login failed: Cannot cast object id={} to AppUser", userId);
            return;
        }
        m_user = user;
        logger::LOG_INFO("User login: {} (id={})", user->GetName(), user->GetId());
    }

    void App::Logout()
    {
        if (auto user = m_user.lock())
        {
            logger::LOG_INFO("User logout: {} (id={})", user->GetName(), user->GetId());
            m_user.reset();
        }
        else
        {
            logger::LOG_WARNING("Logout called, but no user was logged in");
        }
    }

    void App::DoBusinessOperations()
    {
        auto user = m_user.lock();
        if (!user)
        {
            logger::LOG_ERROR("No user logged in, cannot perform business operations.");
            return;
        }

        logger::LOG_INFO("Starting business operations for user id={}", user->GetId());

        m_businessOps->AddNewDocument("DC_001");
        m_businessOps->AddNewDocument("DC_002");
        m_businessOps->AddNewDocument("DC_003");

        m_businessOps->FetchMoreDocuments();

        m_businessOps->RemoveAllDocuments(user->GetId());

        logger::LOG_INFO("Business operations completed for user id={}", user->GetId());
    }

    std::shared_ptr<database::IDatabase> App::GetDatabase()
    {
        return m_database;
    }

} // namespace insERT::app
