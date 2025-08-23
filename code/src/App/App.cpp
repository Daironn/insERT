#include "App.h"

#include "AppUser.h"
#include "Database.h"
#include "Document.h"
#include "Product.h"

// TODO: Change CMake to include only needed files
#include "common/Logger.h"

App::App() : m_database(std::make_shared<Database>()) {}

void App::Login(int userId)
{
    auto objOpt = m_database->Fetch(userId);
    if (!objOpt)
    {
        LOG_ERROR("Login failed: user with id={} not found", userId);
        return;
    }

    auto user = std::dynamic_pointer_cast<AppUser>(*objOpt);
    if (!user)
    {
        LOG_ERROR("Login failed: object with id={} is not an AppUser", userId);
        return;
    }

    m_user = user;
    LOG_INFO("User login: {} (id={})", user->GetLogin(), user->GetId());
}

void App::Logout()
{
    if (auto user = m_user.lock())
    {
        LOG_INFO("User logout: {} (id={})", user->GetLogin(), user->GetId());
        m_user.reset();
    }
    else
    {
        LOG_WARNING("Logout called but no user logged in");
    }
}

void App::DoBusinessOperations()
{
    LOG_INFO("Testing new Database operations...");

    auto user = m_user.lock();
    if (!user)
    {
        LOG_ERROR("No user logged in, cannot perform business operations.");
        return;
    }

    m_database->Fetch(user->GetId());

    CreateDocument("DC_001");
    CreateDocument("DC_002");
    CreateDocument("DC_003");

    // m_database->FetchMoreDocument();

    RemoveAllDocuments();
}

Document* App::CreateDocument(const std::string& number)
{
    auto doc = m_database->Create<Document>(number);
    LOG_INFO("Created document id=%ld number=%s", doc->GetId(), number.c_str());
    return doc;
}

void App::AddProductToDocument(Document* doc, const std::string& productName)
{
    auto product = m_database->Create<Product>(productName);
    doc->AddProduct(product->GetId());
    LOG_INFO("Added product %s to document %ld", productName.c_str(), doc->GetId());
}

void App::RemoveAllDocuments()
{
    std::vector<long> toDelete;
    for (auto id : m_database->GetAllIds())
    {
        auto objOpt = m_database->Fetch(id);
        if (objOpt)
        {
            auto obj = *objOpt;
            if (obj->GetType() == ObjectType::ObjectDocument)
                toDelete.push_back(id);
        }
    }
    for (auto id : toDelete)
    {
        m_database->Delete(id);
    }
    LOG_INFO("Removed all documents");
}
