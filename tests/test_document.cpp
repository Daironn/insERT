#include <catch2/catch_test_macros.hpp>
#include <gmock/gmock.h>

#include "Document/Document.h"

SCENARIO("Document basic functionality", "[Document]")
{
    GIVEN("A Document with id=200 and name='Invoice'")
    {
        insERT::object::Document doc(200, "Invoice");

        WHEN("GetId and GetName are called")
        {
            THEN("200 and 'Invoice' should be returned")
            {
                REQUIRE(doc.GetId() == 200);
                REQUIRE(doc.GetName() == "Invoice");
            }
        }

        WHEN("Two products are added with id 1 and 2")
        {
            doc.AddProduct(1);
            doc.AddProduct(2);

            THEN("GetProducts should return both")
            {
                const auto& products = doc.GetProducts();
                REQUIRE(products.size() == 2);
                REQUIRE(products[0] == 1);
                REQUIRE(products[1] == 2);
            }
        }

        WHEN("Product 1 is removed")
        {
            doc.AddProduct(1);
            doc.AddProduct(2);
            doc.RemoveProduct(1);

            THEN("GetProducts should return only product 2")
            {
                const auto& products = doc.GetProducts();
                REQUIRE(products.size() == 1);
                REQUIRE(products[0] == 2);
            }
        }

        WHEN("Removing a non-existing product id 99")
        {
            doc.AddProduct(5);
            doc.RemoveProduct(99);

            THEN("GetProducts should still return product 5")
            {
                const auto& products = doc.GetProducts();
                REQUIRE(products.size() == 1);
                REQUIRE(products[0] == 5);
            }
        }
    }
}
