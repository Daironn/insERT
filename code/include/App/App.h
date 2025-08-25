#pragma once
#include <memory>

#include "common/common.h"

class AppUser;
class IDatabase;
class IBusinessOperations;
class App
{
  private:
    std::weak_ptr<AppUser>               m_user;
    std::shared_ptr<IDatabase>           m_database;
    std::shared_ptr<IBusinessOperations> m_businessOps;

  public:
    App(std::shared_ptr<IDatabase> database, std::shared_ptr<IBusinessOperations> businessOps);
    ~App() = default;

    void Login(Id userId);
    void Logout();
    void DoBusinessOperations();

    std::shared_ptr<IDatabase> GetDatabase();
};
