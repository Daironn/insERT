#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "AppUser/AppUser.h"

SCENARIO("AppUser basic functionality", "[AppUser]")
{
    GIVEN("A AppUser with id=42 and name='test_user'")
    {
        AppUser user(42, "test_user");

        WHEN("GetId is calleds")
        {
            THEN("42 should be returned")
            {
                REQUIRE(user.GetId() == 42);
            }
        }

        WHEN("GetName is called")
        {
            THEN("'test_user' should be returned")
            {
                REQUIRE(user.GetName() == "test_user");
            }
        }

        WHEN("GetType is called")
        {
            THEN("ObjectAppUser should be returned")
            {
                REQUIRE(user.GetType() == ObjectType::ObjectAppUser);
            }
        }
    }
}
