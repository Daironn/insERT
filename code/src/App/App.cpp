#include "App.h"

#include "AppUser.h"
#include "BusinessOperations.h"
#include "Database.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

App::App(std::shared_ptr<IDatabase> db, std::shared_ptr<IBusinessOperations> businessOps)
    : m_database(std::move(db)), m_businessOps(std::move(businessOps))
{
}

void App::Login(Id userId)
{
    auto obj = m_database->Fetch(userId);
    if (!obj)
    {
        LOG_ERROR("Login failed: user with id={} not found", userId);
        return;
    }
    if (obj->GetType() != ObjectType::ObjectAppUser)
    {
        LOG_ERROR("Login failed: object with id={} is not an AppUser", userId);
        return;
    }
    auto user = std::dynamic_pointer_cast<AppUser>(obj);
    if (!user)
    {
        LOG_ERROR("Login failed: dynamic cast error for id={}", userId);
        return;
    }
    m_user = user;
    LOG_INFO("User login: {} (id={})", user->GetName(), user->GetId());
}

void App::Logout()
{
    if (auto user = m_user.lock())
    {
        LOG_INFO("User logout: {} (id={})", user->GetName(), user->GetId());
        m_user.reset();
    }
    else
    {
        LOG_WARNING("Logout called but no user logged in");
    }
}

void App::DoBusinessOperations()
{
    auto user = m_user.lock();
    if (!user)
    {
        LOG_ERROR("No user logged in, cannot perform business operations.");
        return;
    }

    LOG_INFO("Starting business operations for user id={}", user->GetId());

    m_businessOps->AddNewDocument("DC_001");
    m_businessOps->AddNewDocument("DC_002");
    m_businessOps->AddNewDocument("DC_003");

    m_businessOps->FetchMoreDocuments();

    m_businessOps->RemoveAllDocuments(user->GetId());

    LOG_INFO("Finished business operations");
}

std::shared_ptr<IDatabase> App::GetDatabase()
{
    return m_database;
}
