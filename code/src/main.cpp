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
        // for (auto id : db.GetAllIds())
        // {
        //     auto obj = db.Fetch(id);
        //     if (obj->Type() == ObjectDocument)
        //     {
        //         auto doc = dynamic_cast<Document*>(obj);
        //         LOG_INFO("Backup: Document %ld, number=%s", doc->Id(), doc->Number().c_str());
        //     }
        // }
    }
} // namespace SystemOperations

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        LOG_INFO("Application started");
        App app{};
        // app.Login(1);
        app.DoBusinessOperations();
        // app.Logout();
    }
    // else if (argc == 2 && std::string{argv[1]} == "-backup")
    // {
    //     SystemOperations::BackupDocuments();
    // }

    // return 0;
}
