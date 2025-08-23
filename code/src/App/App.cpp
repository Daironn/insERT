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
    auto obj = m_database->Fetch(userId);
    if (!obj)
    {
        LOG_ERROR("Login failed: user with id={} not found", userId);
        return;
    }

    auto user = std::dynamic_pointer_cast<AppUser>(obj);
    if (!user)
    {
        LOG_ERROR("Login failed: object with id={} is not an AppUser", userId);
        return;
    }

    m_user = user;
    LOG_INFO("User login: {} (id={})", user->GetName(), user->GetId());
}

void App::Logout()
{
    if (auto user = m_user.lock())
    {
        LOG_INFO("User logout: {} (id={})", user->GetName(), user->GetId());
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

    RemoveAllDocuments();
}

std::shared_ptr<Document> App::CreateDocument(const std::string& number)
{
    if (auto doc = m_database->Create<Document>(number); doc)
    {
        LOG_INFO("Created document id={} number={}", doc->GetId(), doc->GetName());
        return doc;
    }
    else
    {
        LOG_ERROR("Failed to create document number={}", number);
        return nullptr;
    }
}

void App::AddProductToDocument(std::shared_ptr<Document> doc, const std::string& productName)
{
    if (!doc)
    {
        LOG_ERROR("AddProductToDocument: null document");
        return;
    }

    auto product = m_database->Create<Product>(productName);
    if (!product)
    {
        LOG_ERROR("AddProductToDocument: failed to create product {}", productName);
        return;
    }

    doc->AddProduct(product->GetId());
    LOG_INFO("Added product {} (id={}) to document id={}",
             product->GetName(),
             product->GetId(),
             doc->GetId());
}

void App::RemoveAllDocuments()
{
    std::vector<long> toDelete;
    for (auto id : m_database->GetAllIds())
    {
        auto obj = m_database->Fetch(id);
        if (obj)
        {
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
