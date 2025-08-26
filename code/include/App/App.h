#pragma once
#include <memory>

#include "common/common.h"

namespace insERT::object
{
    class AppUser;
}

namespace insERT::database
{
    class IDatabase;
}
namespace insERT::ops
{
    class IBusinessOperations;
}
namespace insERT::app
{
    class App
    {
      private:
        std::weak_ptr<object::AppUser>            m_user;
        std::shared_ptr<database::IDatabase>      m_database;
        std::shared_ptr<ops::IBusinessOperations> m_businessOps;

      public:
        App(std::shared_ptr<database::IDatabase>      database,
            std::shared_ptr<ops::IBusinessOperations> businessOps);
        ~App() = default;

        void Login(common::Id userId);
        void Logout();
        void DoBusinessOperations();

        std::shared_ptr<database::IDatabase> GetDatabase();
    };

} // namespace insERT::app
