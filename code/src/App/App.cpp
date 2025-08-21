#include "App.h"

#include "AppUser.h"
#include "BusinessOperations.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

App::App()
    : m_businessOperations(std::make_shared<BusinessOperations>()),
      m_user(std::make_shared<AppUser>()) {};

void App::Login(int userId)
{
    m_user->Fetch(userId);
    LOG_INFO("User login : {}", m_user->Id());
}

void App::Logout()
{
    LOG_INFO("User logout : {}", m_user->Id());
}

void App::DoBusinessOperations()
{
    LOG_INFO("Performing business operations...");
    if (!m_user->Id())
    {
        LOG_ERROR("User not logged in, cannot perform business operations.");
        return;
    }

    LOG_INFO("Fetching user with ID: {}", m_user->Id());
    m_businessOperations->FetchUser(m_user->Id());

    LOG_INFO("Adding new documents...");
    m_businessOperations->AddNewDocument();
    m_businessOperations->AddNewDocument();
    m_businessOperations->AddNewDocument();

    m_businessOperations->FetchMoreDocument();

    m_businessOperations->RemoveAllDocuments();
}
