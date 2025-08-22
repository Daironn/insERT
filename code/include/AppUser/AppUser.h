#pragma once

#include "BusinessObject/IBusinessObject.h"

class AppUser : public IBusinessObject
{
    long        id{};
    std::string login;

  public:
    AppUser(long userId) : id(userId) {}

    long       GetId() const override;
    ObjectType GetType() const override;

    const std::string& GetLogin() const;
    void               SetLogin(const std::string& userLogin);
};
