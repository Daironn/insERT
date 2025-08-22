#include "App.h"

#include "AppUser.h"
#include "BusinessOperations.h"
#include "Database.h"
#include "Document.h"
#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

App::App()
    : m_businessOperations(std::make_shared<BusinessOperations>()),
      m_user(std::make_shared<AppUser>(0)) {};

// void App::Login(int userId)
// {
//     m_user->Fetch(userId);
//     LOG_INFO("User login : {}", m_user->Id());
// }

// void App::Logout()
// {
//     LOG_INFO("User logout : {}", m_user->Id());
// }

void App::DoBusinessOperations()
{
    LOG_INFO("Testing new Database operations...");
    Database db;

    auto user = db.Create<AppUser>();
    user->SetLogin("admin");

    auto doc = db.Create<Document>();
    doc->SetNumber("INV-1001");

    auto product = db.Create<Product>();
    product->SetName("Laptop");
    doc->AddProduct(product->GetId());

    if (auto fetchedDocOpt = db.Fetch(doc->GetId()); fetchedDocOpt)
    {
        if (auto fetchedDoc = dynamic_cast<Document*>(*fetchedDocOpt); fetchedDoc)
        {
            LOG_INFO("Fetched document number: {}", fetchedDoc->GetNumber().c_str());
            fetchedDoc->SetNumber("INV-1002");
            db.Update(fetchedDoc);
        }
        else
        {
            LOG_WARNING("Fetched object with id={} is not a Document", doc->GetId());
        }
    }
    else
    {
        LOG_WARNING("Document with id={} not found in database", doc->GetId());
    }

    db.Delete(product->GetId());
}
