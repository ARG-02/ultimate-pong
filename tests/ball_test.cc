#include <catch2/catch.hpp>
#include "core/ball.h"

using pong::Ball;

TEST_CASE("Setting pong ball's velocity") {
    Ball test_ball = Ball({3,1}, {0,0});
    SECTION("Positive component entries") {
        REQUIRE(test_ball.GetBallVelocity().x == 0);
        REQUIRE(test_ball.GetBallVelocity().y == 0);
        test_ball.SetBallVelocity({1,2});
        REQUIRE(test_ball.GetBallVelocity().x == 1);
        REQUIRE(test_ball.GetBallVelocity().y == 2);
    }
    SECTION("Negative component entries") {
        REQUIRE(test_ball.GetBallVelocity().x == 0);
        REQUIRE(test_ball.GetBallVelocity().y == 0);
        test_ball.SetBallVelocity({-1,-2});
        REQUIRE(test_ball.GetBallVelocity().x == -1);
        REQUIRE(test_ball.GetBallVelocity().y == -2);
    }
}

TEST_CASE("Updating the pong ball's position") {
    Ball test_ball = Ball({3,1}, {0,0});
    SECTION("Positive component entries") {
        REQUIRE(test_ball.GetBallPosition().x == 3);
        REQUIRE(test_ball.GetBallPosition().y == 1);
        test_ball.SetBallVelocity({5,3});
        test_ball.UpdatePosition();
        REQUIRE(test_ball.GetBallPosition().x == 8);
        REQUIRE(test_ball.GetBallPosition().y == 4);
    }
    SECTION("Negative component entries") {
        REQUIRE(test_ball.GetBallPosition().x == 3);
        REQUIRE(test_ball.GetBallPosition().y == 1);
        test_ball.SetBallVelocity({-1,-3});
        test_ball.UpdatePosition();
        REQUIRE(test_ball.GetBallPosition().x == 2);
        REQUIRE(test_ball.GetBallPosition().y == -2);
    }

}
