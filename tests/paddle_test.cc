#include <catch2/catch.hpp>
#include "core/paddle.h"

using pong::Paddle;

TEST_CASE("Cases for Paddle's upward movement") {
    SECTION("Paddle moves upwards starting at random position") {
        Paddle test_paddle = Paddle({10, 10}, {20, 60});
        REQUIRE(test_paddle.GetTopLeftCorner().y == 10);
        REQUIRE(test_paddle.GetBottomRightCorner().y == 60);
        test_paddle.MoveUpwards();
        REQUIRE(test_paddle.GetTopLeftCorner().y == 10 - 10);
        REQUIRE(test_paddle.GetBottomRightCorner().y == 60 - 10);
    }
}

TEST_CASE("Cases for Paddle's downward movement") {
    SECTION("Paddle moves downwards starting at random position") {
        Paddle test_paddle = Paddle({10, 10}, {20, 60});
        REQUIRE(test_paddle.GetTopLeftCorner().y == 10);
        REQUIRE(test_paddle.GetBottomRightCorner().y == 60);
        test_paddle.MoveDownwards();
        REQUIRE(test_paddle.GetTopLeftCorner().y == 10 + 10);
        REQUIRE(test_paddle.GetBottomRightCorner().y == 60 + 10);
    }
}
