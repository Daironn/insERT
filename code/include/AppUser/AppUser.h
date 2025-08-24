#pragma once

#include "BusinessObject/IBusinessObject.h"

class AppUser : public IBusinessObject
{
    long        m_userId;
    std::string m_login;

  public:
    AppUser(long userId, const std::string& userLogin) : m_userId(m_userId), m_login(userLogin) {}

    long       GetId() const override;
    ObjectType GetType() const override;

    const std::string& GetLogin() const;
};
