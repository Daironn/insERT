#include <iostream>
#include <memory>
#include <string>

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
    std::string logFile;
    bool        doBackup = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "--log-file" && i + 1 < argc)
        {
            logFile = argv[++i];
            continue;
        }

        if (arg == "--backup")
        {
            doBackup = true;
            continue;
        }
    }

    if (!logFile.empty())
    {
        insERT::logger::Logger::InstallFileBackend(logFile, false);
    }

    auto db = std::make_shared<insERT::database::Database>();
    std::shared_ptr<insERT::ops::IBusinessOperations> bizIface
        = std::make_shared<insERT::ops::BusinessOperations>(db);
    std::shared_ptr<insERT::ops::ISystemOperations> sysIface
        = std::make_shared<insERT::ops::SystemOperations>(db);

    insERT::app::App app(db, bizIface);

    if (doBackup)
    {
        sysIface->BackupDocuments();
        return 0;
    }

    app.Login(insERT::common::ADMIN_USER_ID);
    app.DoBusinessOperations();
    app.Logout();

    return 0;
}
