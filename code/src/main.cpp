#include <memory>

#include "App.h"
#include "BusinessOperations.h"
#include "Database.h"
#include "Document.h"
#include "Product.h"
#include "SystemOperations.h"
#include "common/Logger.h"
#include "common/common.h"

int main(int argc, char** argv)
{
    auto db = std::make_shared<insERT::database::Database>();

    std::shared_ptr<insERT::ops::IBusinessOperations> bizIface
        = std::make_shared<insERT::ops::BusinessOperations>(db);
    std::shared_ptr<insERT::ops::ISystemOperations> sysIface
        = std::make_shared<insERT::ops::SystemOperations>(db);

    insERT::app::App app(db, bizIface);

    if (argc == 1)
    {
        app.Login(insERT::common::ADMIN_USER_ID);
        app.DoBusinessOperations();
        app.Logout();
    }
    else if (argc == 2 && std::string{argv[1]} == "-backup")
    {
        sysIface->BackupDocuments();
    }

    return 0;
}
