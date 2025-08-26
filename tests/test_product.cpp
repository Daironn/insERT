#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "Product/Product.h"

SCENARIO("Product basic functionality", "[Product]")
{
    GIVEN("A Product with id=100 and name='Laptop'")
    {
        insERT::object::Product product(100, "Laptop");

        WHEN("GetId is called")
        {
            THEN("100 should be returned")
            {
                REQUIRE(product.GetId() == 100);
            }
        }

        WHEN("GetName is called")
        {
            THEN("'Laptop' should be returned")
            {
                REQUIRE(product.GetName() == "Laptop");
            }
        }

        WHEN("GetType is called")
        {
            THEN("ObjectProduct should be returned")
            {
                REQUIRE(product.GetType() == insERT::common::ObjectType::ObjectProduct);
            }
        }
    }
}
