#include "AppUser.h"

void AppUser::OnFetch()
{
    // m_login = "user" + std::to_string(Id());
    // std::cout << "AppUser fetched: " << m_login << std::endl;
}

void AppUser::OnUpdate()
{
    // std::cout << "AppUser updated: " << m_login << std::endl;
}

void AppUser::OnDelete()
{
    // std::cout << "AppUser deleted: " << m_login << std::endl;
}

void AppUser::SetLogin(std::string login)
{
    // m_login = login;
}

const std::string& AppUser::Login() const
{
    return "";
}
