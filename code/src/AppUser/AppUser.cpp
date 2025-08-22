#include "AppUser.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

long AppUser::GetId() const
{
    return id;
}

ObjectType AppUser::GetType() const
{
    return ObjectType::ObjectAppUser;
}

const std::string& AppUser::GetLogin() const
{
    return login;
}

void AppUser::SetLogin(const std::string& l)
{
    login = l;
}
