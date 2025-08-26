#include <catch2/catch_test_macros.hpp>

#include "AppUser/AppUser.h"
#include "Database/Database.h"
#include "Document/Document.h"
#include "Product/Product.h"

constexpr long NEXT_ID = 2;

SCENARIO("Database initializes with admin user", "[Database][Init]")
{
    GIVEN("An empty Database")
    {
        insERT::database::Database db;

        WHEN("GetAllIds is called")
        {
            auto ids = db.GetAllIds();

            THEN("insERT::common::ADMIN_USER_ID should be present")
            {
                REQUIRE(ids.size() == 1);
                REQUIRE(ids[0] == insERT::common::ADMIN_USER_ID);
            }
        }
    }
}

SCENARIO("Database Create works correctly", "[Database][Create]")
{
    GIVEN("An empty Database")
    {
        insERT::database::Database db;

        WHEN("AppUser is created")
        {
            auto user = db.Create(insERT::common::ObjectType::ObjectAppUser, "Jerzy");

            THEN("AppUser object is returned with correct name, type and insERT::common::Id")
            {
                REQUIRE(user != nullptr);
                REQUIRE(user->GetType() == insERT::common::ObjectType::ObjectAppUser);
                REQUIRE(user->GetName() == "Jerzy");
                REQUIRE(user->GetId() == NEXT_ID);
            }
        }

        WHEN("Product is created")
        {
            auto prod = db.Create(insERT::common::ObjectType::ObjectProduct, "Laptop");

            THEN("Product object is returned with correct name, type and insERT::common::Id")
            {
                REQUIRE(prod != nullptr);
                REQUIRE(prod->GetType() == insERT::common::ObjectType::ObjectProduct);
                REQUIRE(prod->GetName() == "Laptop");
                REQUIRE(prod->GetId() == NEXT_ID);
            }
        }

        WHEN("Document is created")
        {
            auto doc = db.Create(insERT::common::ObjectType::ObjectDocument, "DC_001");

            THEN("Document object is returned with correct name, type and insERT::common::Id")
            {
                REQUIRE(doc != nullptr);
                REQUIRE(doc->GetType() == insERT::common::ObjectType::ObjectDocument);
                REQUIRE(doc->GetName() == "DC_001");
                REQUIRE(doc->GetId() == NEXT_ID);
            }
        }

        WHEN("Unsupported type is passed")
        {
            auto obj = db.Create(static_cast<insERT::common::ObjectType>(999), "unknown");

            THEN("nullptr is returned")
            {
                REQUIRE(obj == nullptr);
            }
        }
    }
}

SCENARIO("Database Fetch works correctly", "[Database][Fetch]")
{
    GIVEN("A Database with a product")
    {
        insERT::database::Database db;
        auto prod = db.Create(insERT::common::ObjectType::ObjectProduct, "Laptop");

        WHEN("Fetching existing ID")
        {
            auto fetched = db.Fetch(prod->GetId());

            THEN("Object with correct insERT::common::Id and name is returned")
            {
                REQUIRE(fetched != nullptr);
                REQUIRE(fetched->GetId() == prod->GetId());
                REQUIRE(fetched->GetName() == "Laptop");
                REQUIRE(fetched->GetId() == NEXT_ID);
            }
        }

        WHEN("Fetching non-existing ID")
        {
            auto fetched = db.Fetch(9999);

            THEN("nullptr is returned")
            {
                REQUIRE(fetched == nullptr);
            }
        }
    }
}

SCENARIO("Database Update replaces object correctly", "[Database][Update]")
{
    GIVEN("A Database with a document")
    {
        insERT::database::Database db;
        auto baseDoc = db.Create(insERT::common::ObjectType::ObjectDocument, "DC_001");

        WHEN("Update is called with nullptr")
        {
            bool ret = db.Update(nullptr);

            THEN("No update is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Update is called with non-existing object")
        {
            auto doc = std::make_shared<insERT::object::Document>(9999, "DC_001");
            bool ret = db.Update(doc);

            THEN("No update is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Update with wrong type but correct id")
        {
            auto wrong = std::make_shared<insERT::object::Product>(baseDoc->GetId(), "conflict");
            bool ret   = db.Update(wrong);

            THEN("No update is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Update with correct type and id")
        {
            auto replacement
                = std::make_shared<insERT::object::Document>(baseDoc->GetId(), "DC_002");
            bool ret = db.Update(replacement);

            THEN("it succeeds and fetch returns new name")
            {
                REQUIRE(ret);
                auto fetched = db.Fetch(baseDoc->GetId());
                REQUIRE(fetched->GetName() == "DC_002");
            }
        }
    }
}

SCENARIO("Database Delete rules are enforced", "[Database][Delete]")
{
    GIVEN("A Database with an admin user, a normal user and a product")
    {
        insERT::database::Database db;
        auto user = db.Create(insERT::common::ObjectType::ObjectAppUser, "Jerzy");
        auto prod = db.Create(insERT::common::ObjectType::ObjectProduct, "Laptop");

        WHEN("Attempting to delete admin user")
        {
            bool ret = db.Delete(insERT::common::ADMIN_USER_ID);

            THEN("No deletion is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Attempting to delete currently logged user")
        {
            bool ret = db.Delete(user->GetId(), user->GetId());

            THEN("No deletion is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Attempting to delete non-existing id")
        {
            bool ret = db.Delete(9999);

            THEN("No deletion is performed and it fails")
            {
                REQUIRE_FALSE(ret);
            }
        }

        WHEN("Deleting a product")
        {
            auto doc       = db.Create(insERT::common::ObjectType::ObjectDocument, "DC_001");
            auto castedDoc = std::dynamic_pointer_cast<insERT::object::Document>(doc);
            castedDoc->AddProduct(prod->GetId());

            bool ret = db.Delete(prod->GetId());

            THEN("Deletion succeeds and product is removed from documents")
            {
                REQUIRE(ret);
                auto fetchedDoc
                    = std::dynamic_pointer_cast<insERT::object::Document>(db.Fetch(doc->GetId()));
                REQUIRE(fetchedDoc != nullptr);
                REQUIRE(fetchedDoc->GetProducts().empty());
            }
        }
    }
}

SCENARIO("Database GetAllIds reflects storage", "[Database][Ids]")
{
    GIVEN("A Database with an admin user, a normal user and a product")
    {
        insERT::database::Database db;
        auto user    = db.Create(insERT::common::ObjectType::ObjectAppUser, "Jeerzy");
        auto product = db.Create(insERT::common::ObjectType::ObjectProduct, "Laptop");

        WHEN("GetAllIds is called")
        {
            auto ids = db.GetAllIds();

            THEN("All three IDs are present")
            {
                REQUIRE(std::find(ids.begin(), ids.end(), insERT::common::ADMIN_USER_ID)
                        != ids.end());
                REQUIRE(std::find(ids.begin(), ids.end(), user->GetId()) != ids.end());
                REQUIRE(std::find(ids.begin(), ids.end(), product->GetId()) != ids.end());
            }
        }

        WHEN("The user is deleted")
        {
            db.Delete(user->GetId());
            auto ids = db.GetAllIds();

            THEN("Only admin and product IDs are present")
            {
                REQUIRE(ids.size() == 2);
                REQUIRE(std::find(ids.begin(), ids.end(), insERT::common::ADMIN_USER_ID)
                        != ids.end());
                REQUIRE(std::find(ids.begin(), ids.end(), product->GetId()) != ids.end());
            }
        }
    }
}
