#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "Document/Document.h"
#include "Operations/SystemOperations.h"
#include "mocks/MockDatabase.h"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

SCENARIO("SystemOperations BackupDocuments fetches and logs all documents", "[SystemOperations]")
{
    auto             mockDb = std::make_shared<StrictMock<MockDatabase>>();
    SystemOperations sys(mockDb);

    GIVEN("Database that contains some documents")
    {
        EXPECT_CALL(*mockDb, GetAllIds()).WillOnce(Return(std::vector<Id>{2, 3}));
        EXPECT_CALL(*mockDb, Fetch(2)).WillOnce(Return(std::make_shared<Document>(2, "doc1")));
        EXPECT_CALL(*mockDb, Fetch(3)).WillOnce(Return(std::make_shared<Document>(3, "doc2")));

        WHEN("BackupDocuments is called")
        {
            sys.BackupDocuments();

            THEN("Database Fetch should be called for all IDs")
            {
                SUCCEED();
            }
        }
    }
}
