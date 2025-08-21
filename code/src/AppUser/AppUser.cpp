#include "AppUser.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

void AppUser::OnFetch()
{
    m_login = "user" + std::to_string(Id());
    LOG_INFO("AppUser fetched: {}", m_login);
}

void AppUser::OnUpdate()
{
    LOG_INFO("AppUser updated: {}", m_login);
}

void AppUser::OnDelete()
{
    LOG_INFO("AppUser deleted: {}", m_login);
}

void AppUser::SetLogin(std::string login)
{
    m_login = login;
}

const std::string& AppUser::Login() const
{
    return "TEST_LOGIN";
}
