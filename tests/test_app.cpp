#include <catch2/catch_session.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>
#include <string>

#include "App.h"
#include "AppUser/AppUser.h"
#include "IBusinessOperations.h"
#include "IDatabase.h"
#include "mocks/MockDatabase.h"

using ::testing::_;
using ::testing::Eq;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::StrictMock;

class MockBusinessOperations : public IBusinessOperations
{
  public:
    MOCK_METHOD(void, AddNewDocument, (const std::string& docName), (override));
    MOCK_METHOD(void, FetchMoreDocuments, (), (override));
    MOCK_METHOD(bool, RemoveAllDocuments, (std::optional<Id> currentUserId), (override));
};

class MockBusinessObject : public IBusinessObject
{
  public:
    MockBusinessObject(long id, ObjectType t, std::string name)
        : m_id(id), m_type(t), m_name(std::move(name))
    {
    }

    long GetId() const override
    {
        return m_id;
    }
    ObjectType GetType() const override
    {
        return m_type;
    }
    const std::string& GetName() const override
    {
        return m_name;
    }

  private:
    long        m_id;
    ObjectType  m_type;
    std::string m_name;
};

SCENARIO("App::GetDatabase returns injected database", "[App][GetDatabase]")
{
    GIVEN("An App constructed with a mock database")
    {
        auto database    = std::make_shared<NiceMock<MockDatabase>>();
        auto businessOps = std::make_shared<NiceMock<MockBusinessOperations>>();
        App  app(database, businessOps);

        WHEN("GetDatabase is called")
        {
            auto ret = app.GetDatabase();

            THEN("The same database instance is returned")
            {
                REQUIRE(ret == database);
            }
        }
    }
}

SCENARIO("Successful login followed by business operations", "[App][Login][Success]")
{
    GIVEN("An App with database returning a valid AppUser for Fetch")
    {
        auto mockDb          = std::make_shared<StrictMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);
        auto user = std::make_shared<AppUser>(42, "test_user");

        WHEN("Login called for existing AppUser id")
        {
            InSequence seq;
            EXPECT_CALL(*mockDb, Fetch(42)).WillOnce(Return(user));
            EXPECT_CALL(*mockBusinessOps, AddNewDocument("DC_001")).Times(1);
            EXPECT_CALL(*mockBusinessOps, AddNewDocument("DC_002")).Times(1);
            EXPECT_CALL(*mockBusinessOps, AddNewDocument("DC_003")).Times(1);
            EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(1);
            EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).WillOnce(Return(true));

            app.Login(42);

            THEN("DoBusinessOperations calls business operations in order")
            {
                app.DoBusinessOperations();
            }
        }
    }
}

SCENARIO("Login fails when user id does not exist", "[App][Login][Failure]")
{
    GIVEN("An App with database returning nullptr for Fetch")
    {
        auto mockDb          = std::make_shared<StrictMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);

        WHEN("Login called for non-existing id")
        {
            EXPECT_CALL(*mockDb, Fetch(999)).WillOnce(Return(nullptr));

            app.Login(999);

            THEN("DoBusinessOperations should not call business operations")
            {
                EXPECT_CALL(*mockBusinessOps, AddNewDocument(_)).Times(0);
                EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(0);
                EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).Times(0);

                app.DoBusinessOperations();
            }
        }
    }
}

SCENARIO("Login fails when Fetch returns object of wrong type", "[App][Login][Failure]")
{
    GIVEN("Database returns non-AppUser type for Fetch")
    {
        auto mockDb          = std::make_shared<StrictMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);

        auto other
            = std::make_shared<MockBusinessObject>(43, ObjectType::ObjectDocument, "not_user");

        WHEN("Fetch returns object of wrong type")
        {
            EXPECT_CALL(*mockDb, Fetch(43)).WillOnce(Return(other));

            app.Login(43);

            THEN("DoBusinessOperations should not call business operations")
            {
                EXPECT_CALL(*mockBusinessOps, AddNewDocument(_)).Times(0);
                EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(0);
                EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).Times(0);

                app.DoBusinessOperations();
            }
        }
    }
}

SCENARIO("Login fails when Fetch returns non-AppUser instance", "[App][Login][Failure]")
{
    GIVEN("Database returns non-AppUser instance for Fetch")
    {
        auto mockDb          = std::make_shared<StrictMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);

        auto fakeUser
            = std::make_shared<MockBusinessObject>(44, ObjectType::ObjectAppUser, "pretend");

        WHEN("Fetch returns non-AppUser instance")
        {
            EXPECT_CALL(*mockDb, Fetch(44)).WillOnce(Return(fakeUser));

            app.Login(44);

            THEN("DoBusinessOperations should not call business operations")
            {
                EXPECT_CALL(*mockBusinessOps, AddNewDocument(_)).Times(0);
                EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(0);
                EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).Times(0);

                app.DoBusinessOperations();
            }
        }
    }
}

SCENARIO("Logout clears logged in user and prevents further business ops", "[App][Logout]")
{
    GIVEN("An App with no user logged in")
    {
        auto mockDb          = std::make_shared<StrictMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);
        auto user = std::make_shared<AppUser>(55, "logout_user");

        WHEN("Login followed by Logout is called")
        {
            EXPECT_CALL(*mockDb, Fetch(55)).WillOnce(Return(user));
            app.Login(55);

            app.Logout();

            THEN("DoBusinessOperations should not call business operations")
            {
                EXPECT_CALL(*mockBusinessOps, AddNewDocument(_)).Times(0);
                EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(0);
                EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).Times(0);

                app.DoBusinessOperations();
            }
        }
    }
}

SCENARIO("Logout when no user logged in", "[App][Logout]")
{
    GIVEN("An App with no logged in user")
    {
        auto mockDb          = std::make_shared<NiceMock<MockDatabase>>();
        auto mockBusinessOps = std::make_shared<StrictMock<MockBusinessOperations>>();
        App  app(mockDb, mockBusinessOps);

        WHEN("Logout is called")
        {
            app.Logout();

            THEN("DoBusinessOperations should not call business operations")
            {
                EXPECT_CALL(*mockBusinessOps, AddNewDocument(_)).Times(0);
                EXPECT_CALL(*mockBusinessOps, FetchMoreDocuments()).Times(0);
                EXPECT_CALL(*mockBusinessOps, RemoveAllDocuments(_)).Times(0);

                app.DoBusinessOperations();
            }
        }
    }
}
