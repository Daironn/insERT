#pragma once

#include "BusinessObject/BusinessObject.h"

class AppUser : public BusinessObject
{
  private:
    std::string m_login{"TEST_LOGIN"};

  public:
    AppUser() = default;

    void OnFetch() override;
    void OnUpdate() override;
    void OnDelete() override;

    void SetLogin(std::string login);

    const std::string& Login() const;
};
