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

namespace insERT::main
{

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
            auto instalState = insERT::logger::Logger::InstallFileBackend(logFile, false);
            if (!instalState)
            {
                insERT::logger::LOG_WARNING(
                    "Failed to initialize file logger, falling back to console");
            }
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
} // namespace insERT::main

int main(int argc, char** argv)
{
    return insERT::main::main(argc, argv);
}
