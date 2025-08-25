#pragma once

#include "BusinessObject/IBusinessObject.h"

namespace insERT::object
{
    class AppUser : public IBusinessObject
    {
        long        m_userId;
        std::string m_login;

      public:
        AppUser(long userId, const std::string& userLogin);

        long               GetId() const override;
        common::ObjectType GetType() const override;
        const std::string& GetName() const override;
    };

} // namespace insERT::object
