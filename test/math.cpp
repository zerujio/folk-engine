//
// Created by sergio on 29-01-22.
//

#include "catch.hpp"

#include "folk/math.hpp"

using namespace Folk;

TEST_CASE("Vector")
{
    SECTION("Addition/subtraction") {
        Vec3 x, y;

        REQUIRE(x + y == Vec3(0, 0, 0));

        x = {1, 0, 0};
        REQUIRE(x + y == x);

        y = {-1, 1, -1};
        REQUIRE(x + y == Vec3(0, 1, -1));

        x += Vec3(1, 1, 1);
        REQUIRE(x == Vec3(2, 1, 1));

        REQUIRE(x - y == Vec3(3, 0, 2));
    }

    SECTION("Multiplication/division") {
        Vec3 x = {1, 1, 1};

        REQUIRE(x * 1.0f == x);
        REQUIRE(x * 2.0f == Vec3(2, 2, 2));
        REQUIRE(x / 2.0f == Vec3(.5f, .5f, .5f));
    }
}
