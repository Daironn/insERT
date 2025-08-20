#pragma once
#include <memory>

class AppUser;
class BusinessOperations;

class App
{
  private:
    std::shared_ptr<BusinessOperations> m_businessOperations;
    std::shared_ptr<AppUser>            m_user;

  public:
    App() = default;

    void Login(int userId);
    void Logout();
    void DoBusinessOperations();
};
