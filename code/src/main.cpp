#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "App.h"
#include "Document.h"
#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"
// #include "common/common.h"

namespace SystemOperations
{
    void BackupDocuments()
    {
        for (int i = 1; i < 5; i++)
        {
            try
            {
                Document document{};
                document.Fetch(i);
                std::cout << "Backup document: " << document.Id() << std::endl;
            }
            catch (std::exception& e)
            {
                std::cerr << "Backup exception: " << i << " " << e.what() << std::endl;
            }
        }
    }
} // namespace SystemOperations

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        LOG_INFO("Application started");
        App app{};
        app.Login(1);
        app.DoBusinessOperations();
        app.Logout();
    }
    else if (argc == 2 && std::string{argv[1]} == "-backup")
    {
        SystemOperations::BackupDocuments();
    }

    // return 0;
}
