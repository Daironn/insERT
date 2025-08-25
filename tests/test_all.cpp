#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "AppUser/AppUser.h"

SCENARIO("AppUser basic functionality", "[AppUser]")
{
    GIVEN("An AppUser with id=42 and login=test_user")
    {
        AppUser user(42, "test_user");

        WHEN("we call GetId()")
        {
            THEN("it should return 42")
            {
                REQUIRE(user.GetId() == 42);
            }
        }

        WHEN("we call GetName()")
        {
            THEN("it should return 'test_user'")
            {
                REQUIRE(user.GetName() == "test_user");
            }
        }

        WHEN("we call GetType()")
        {
            THEN("it should return ObjectAppUser")
            {
                REQUIRE(user.GetType() == ObjectType::ObjectAppUser);
            }
        }
    }
}
