#include "AppUser.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

namespace insERT::object
{
    AppUser::AppUser(long userId, const std::string& userLogin)
        : m_userId(userId), m_login(userLogin)
    {
    }

    long AppUser::GetId() const
    {
        return m_userId;
    }

    common::ObjectType AppUser::GetType() const
    {
        return common::ObjectType::ObjectAppUser;
    }

    const std::string& AppUser::GetName() const
    {
        return m_login;
    }

} // namespace insERT::object
