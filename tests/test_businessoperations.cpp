#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "AppUser/AppUser.h"
#include "Document/Document.h"
#include "Operations/BusinessOperations.h"
#include "mocks/MockDatabase.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

SCENARIO("BusinessOperations AddNewDocument adds a new Document", "[BusinessOperations]")
{
    auto mockDb = std::make_shared<StrictMock<MockDatabase>>();

    insERT::ops::BusinessOperations businessOps(mockDb);

    GIVEN("A document name")
    {
        std::string docName = "DC_001";

        EXPECT_CALL(*mockDb, Create(insERT::common::ObjectType::ObjectDocument, docName))
            .WillOnce(Return(std::make_shared<insERT::object::Document>(42, docName)));

        WHEN("AddNewDocument is called")
        {
            businessOps.AddNewDocument(docName);

            THEN("All expected database calls are made")
            {
                SUCCEED();
            }
        }
    }
}

SCENARIO("BusinessOperations FetchMoreDocuments fetches all documents", "[BusinessOperations]")
{
    auto mockDb = std::make_shared<StrictMock<MockDatabase>>();

    insERT::ops::BusinessOperations businessOps(mockDb);

    EXPECT_CALL(*mockDb, GetAllIds()).WillOnce(Return(std::vector<insERT::common::Id>{1, 2, 3}));
    EXPECT_CALL(*mockDb, Fetch(_)).Times(3);

    WHEN("FetchMoreDocuments is called")
    {
        businessOps.FetchMoreDocuments();
        THEN("All expected database calls are made")
        {
            SUCCEED();
        }
    }
}

SCENARIO("BusinessOperations RemoveAllDocuments delegates to Database::Delete",
         "[BusinessOperations]")
{
    auto mockDb = std::make_shared<StrictMock<MockDatabase>>();

    insERT::ops::BusinessOperations businessOps(mockDb);

    GIVEN("Database with some documents and other objects")
    {
        EXPECT_CALL(*mockDb, GetAllIds())
            .WillOnce(Return(std::vector<insERT::common::Id>{2, 3, 4}));

        auto user = std::make_shared<insERT::object::AppUser>(2, "Jerzy");
        auto doc2 = std::make_shared<insERT::object::Document>(3, "DC_001");
        auto doc3 = std::make_shared<insERT::object::Document>(4, "DC_002");

        EXPECT_CALL(*mockDb, Fetch(2)).WillOnce(Return(user));
        EXPECT_CALL(*mockDb, Fetch(3)).WillOnce(Return(doc2));
        EXPECT_CALL(*mockDb, Fetch(4)).WillOnce(Return(doc3));

        EXPECT_CALL(*mockDb, Delete(3, _)).WillOnce(Return(true));
        EXPECT_CALL(*mockDb, Delete(4, _)).WillOnce(Return(true));

        WHEN("RemoveAllDocuments is called")
        {
            bool result = businessOps.RemoveAllDocuments(std::nullopt);

            THEN("All deletions succeed and it returns true")
            {
                REQUIRE(result == true);
            }
        }
    }

    GIVEN("Database with some documents and other objects")
    {
        EXPECT_CALL(*mockDb, GetAllIds()).WillOnce(Return(std::vector<insERT::common::Id>{2, 3}));

        auto doc2 = std::make_shared<insERT::object::Document>(2, "DC_002");
        auto doc3 = std::make_shared<insERT::object::Document>(3, "DC_003");

        EXPECT_CALL(*mockDb, Fetch(2)).WillOnce(Return(doc2));
        EXPECT_CALL(*mockDb, Fetch(3)).WillOnce(Return(doc3));

        EXPECT_CALL(*mockDb, Delete(2, _)).WillOnce(Return(true));
        EXPECT_CALL(*mockDb, Delete(3, _)).WillOnce(Return(false));

        WHEN("RemoveAllDocuments is called")
        {
            bool result = businessOps.RemoveAllDocuments(std::nullopt);

            THEN("One deletion fails and it returns false")
            {
                REQUIRE(result == false);
            }
        }
    }
}
