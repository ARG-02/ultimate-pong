#include <catch2/catch.hpp>
#include "core/physics_engine.h"

using pong::PhysicsEngine;
using pong::Ball;

TEST_CASE("Checks if entities are spawned in default locations") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Checks if ball is spawned correctly") {
        test_engine.SpawnEntities();
        REQUIRE(test_engine.GetBall().GetBallPosition().x == pong::kWindowLength/2);
        REQUIRE(test_engine.GetBall().GetBallPosition().y == pong::kWindowHeight/2);
        REQUIRE(glm::length(test_engine.GetBall().GetBallVelocity()) ==
                Approx(pong::kBallDefaultSpeedMultiplier));
    }
    SECTION("Checks if left paddle is spawned correctly") {
        test_engine.SpawnEntities();
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().x ==
                pong::kWindowBuffer);
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y ==
                (pong::kWindowHeight/2) - (pong::kPaddleLength/2));
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner().x ==
                pong::kWindowBuffer + pong::kPaddleWidth);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner().y ==
                (pong::kWindowHeight/2) + (pong::kPaddleLength/2));
    }
    SECTION("Checks if right paddle is spawned correctly") {
        test_engine.SpawnEntities();
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().x ==
                pong::kWindowLength - pong::kWindowBuffer - pong::kPaddleWidth);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y ==
                (pong::kWindowHeight/2) - (pong::kPaddleLength/2));
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner().x ==
                pong::kWindowLength - pong::kWindowBuffer);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner().y ==
                (pong::kWindowHeight/2) + (pong::kPaddleLength/2));
    }
}

TEST_CASE("Checks if pong ball's position is updated") {
    PhysicsEngine test_engine = PhysicsEngine();
    glm::vec2 initial_position = test_engine.GetBall().GetBallPosition();
    glm::vec2 initial_velocity = test_engine.GetBall().GetBallVelocity();
    test_engine.UpdateBallPosition();
    REQUIRE(test_engine.GetBall().GetBallPosition().x ==
    initial_position.x + initial_velocity.x);
    REQUIRE(test_engine.GetBall().GetBallPosition().y ==
    initial_position.y + initial_velocity.y);
}

TEST_CASE("Checks if a round has been won") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Ball is randomly in middle of screen") {
        test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kWindowHeight/2});
        int left_score = test_engine.GetLeftPlayerScore();
        int right_score = test_engine.GetRightPlayerScore();
        test_engine.CheckRoundVictory();
        REQUIRE(test_engine.GetLeftPlayerScore() == left_score);
        REQUIRE(test_engine.GetRightPlayerScore() == right_score);
    }
    SECTION("Ball is past left paddle") {
        test_engine.GetBall().SetBallPosition({pong::kBallRadius, pong::kWindowHeight/2});
        int left_score = test_engine.GetLeftPlayerScore();
        int right_score = test_engine.GetRightPlayerScore();
        test_engine.CheckRoundVictory();
        REQUIRE(test_engine.GetLeftPlayerScore() == left_score);
        REQUIRE(test_engine.GetRightPlayerScore() == right_score);
    }
    SECTION("Ball is past right paddle") {
        test_engine.GetBall().SetBallPosition({pong::kWindowLength - (pong::kBallRadius), pong::kWindowHeight/2});
        int left_score = test_engine.GetLeftPlayerScore();
        int right_score = test_engine.GetRightPlayerScore();
        test_engine.CheckRoundVictory();
        REQUIRE(test_engine.GetLeftPlayerScore() == left_score);
        REQUIRE(test_engine.GetRightPlayerScore() == right_score);
    }
}

TEST_CASE("Check if game is over") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Checks if left player has required score") {
        test_engine.SetLeftPlayerScore(10);
        test_engine.SetRightPlayerScore(0);
        test_engine.CheckGameVictory();
        REQUIRE(test_engine.GetIsInPlay() == false);
    }
    SECTION("Checks if right player has required score") {
        test_engine.SetLeftPlayerScore(4);
        test_engine.SetRightPlayerScore(5);
        test_engine.CheckGameVictory();
        REQUIRE(test_engine.GetIsInPlay() == false);
    }
    SECTION("Checks if neither player has required score") {
        test_engine.SetLeftPlayerScore(2);
        test_engine.SetRightPlayerScore(3);
        test_engine.CheckGameVictory();
        REQUIRE(test_engine.GetIsInPlay() == true);
    }
}

TEST_CASE("Checks if ball has collied with walls") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Checks if ball is in middle of screen") {
        test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kWindowHeight/2});
        double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
        test_engine.CheckWallCollision();
        REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
    }
    SECTION("Checks if ball is at top of screen") {
        SECTION("Checks if ball is moving towards wall") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kBallRadius - 3});
            test_engine.GetBall().SetBallVelocity({1, -1});
            double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
            test_engine.CheckWallCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
        }
        SECTION("Checks if ball is moving away from wall") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kBallRadius - 3});
            test_engine.GetBall().SetBallVelocity({1, 1});
            double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
            test_engine.CheckWallCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
        }
    }
    SECTION("Checks if ball is at bottom of screen") {
        SECTION("Checks if ball is moving towards wall") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kWindowHeight - pong::kBallRadius + 1});
            test_engine.GetBall().SetBallVelocity({1, 1});
            double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
            test_engine.CheckWallCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
        }
        SECTION("Checks if ball is moving away from wall") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kWindowHeight - pong::kBallRadius + 1});
            test_engine.GetBall().SetBallVelocity({1, -1});
            double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
            test_engine.CheckWallCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
        }
    }
}

TEST_CASE("Checks if ball has collied with paddles") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Checks if ball is in middle of screen") {
        test_engine.GetBall().SetBallPosition({pong::kWindowLength/2, pong::kWindowHeight/2});
        double initial_y_velocity = test_engine.GetBall().GetBallVelocity().y;
        double initial_x_velocity = test_engine.GetBall().GetBallVelocity().x;
        test_engine.CheckPaddleCollision();
        REQUIRE(test_engine.GetBall().GetBallVelocity().y == Approx(initial_y_velocity));
        REQUIRE(test_engine.GetBall().GetBallVelocity().x == Approx(initial_x_velocity));
    }
    SECTION("Checks if ball has collided with left paddle") {
        SECTION("Checks if ball is moving towards paddle") {
            test_engine.GetBall().SetBallPosition({pong::kPaddleWidth + pong::kWindowBuffer + pong::kBallRadius, pong::kBallRadius});
            test_engine.GetBall().SetBallVelocity({-1, -1});
            double initial_x_velocity = test_engine.GetBall().GetBallVelocity().x;
            test_engine.CheckPaddleCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().x == Approx(initial_x_velocity));
        }
        SECTION("Checks if ball is moving away from paddle") {
            test_engine.GetBall().SetBallPosition({pong::kPaddleWidth + pong::kWindowBuffer + pong::kBallRadius, pong::kBallRadius});
            test_engine.GetBall().SetBallVelocity({1, 1});
            double initial_x_velocity = test_engine.GetBall().GetBallVelocity().x;
            test_engine.CheckPaddleCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().x == Approx(initial_x_velocity));
        }
    }
    SECTION("Checks if ball has collided with right paddle") {
        SECTION("Checks if ball is moving towards paddle") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength - pong::kPaddleWidth - pong::kWindowBuffer - pong::kBallRadius, pong::kBallRadius});
            test_engine.GetBall().SetBallVelocity({1, -1});
            double initial_x_velocity = test_engine.GetBall().GetBallVelocity().x;
            test_engine.CheckPaddleCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().x == Approx(initial_x_velocity));
        }
        SECTION("Checks if ball is moving away from paddle") {
            test_engine.GetBall().SetBallPosition({pong::kWindowLength - pong::kPaddleWidth - pong::kWindowBuffer - pong::kBallRadius, pong::kBallRadius});
            test_engine.GetBall().SetBallVelocity({-1, 1});
            double initial_x_velocity = test_engine.GetBall().GetBallVelocity().x;
            test_engine.CheckPaddleCollision();
            REQUIRE(test_engine.GetBall().GetBallVelocity().x == Approx(initial_x_velocity));
        }
    }
}

TEST_CASE("Checks for user paddle control") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Checks if left paddle is moving upwards") {
        SECTION("Checks if paddle is at top of screen") {
            test_engine.GetLeftPaddle().SetTopLeftCorner({10, 0});
            test_engine.UserPaddleControl(true, false, false, false);
            REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == 265);
        }
        SECTION("Checks if paddle is below top of screen") {
            test_engine.GetLeftPaddle().SetTopLeftCorner({10, 100});
            test_engine.UserPaddleControl(true, false, false, false);
            REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == 265);
        }
    }
    SECTION("Checks if left paddle is moving downwards") {
        SECTION("Checks if paddle is at bottom of screen") {
            test_engine.GetLeftPaddle().SetTopLeftCorner({10, pong::kWindowHeight});
            test_engine.UserPaddleControl(false, true, false, false);
            REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == 285);
        }
        SECTION("Checks if paddle is above bottom of screen") {
            test_engine.GetLeftPaddle().SetTopLeftCorner({10, pong::kWindowHeight - 20});
            test_engine.UserPaddleControl(false, true, false, false);
            REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == 285);
        }
    }
    SECTION("Checks if right paddle is moving upwards") {
        SECTION("Checks if paddle is at top of screen") {
            test_engine.GetRightPaddle().SetTopLeftCorner({10, 0});
            test_engine.UserPaddleControl(false, false, true, false);
            REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == 265);
        }
        SECTION("Checks if paddle is below top of screen") {
            test_engine.GetRightPaddle().SetTopLeftCorner({10, 100});
            test_engine.UserPaddleControl(false, false, true, false);
            REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == 265);
        }
    }
    SECTION("Checks if right paddle is moving downwards") {
        SECTION("Checks if paddle is at bottom of screen") {
            test_engine.GetRightPaddle().SetTopLeftCorner({10, pong::kWindowHeight});
            test_engine.UserPaddleControl(false, false, false, true);
            REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == 285);
        }
        SECTION("Checks if paddle is above bottom of screen") {
            test_engine.GetRightPaddle().SetTopLeftCorner({10, pong::kWindowHeight - 20});
            test_engine.UserPaddleControl(false, false, false, true);
            REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == 285);
        }
    }
}

TEST_CASE("Cases for ReverseBallHorizontalDirection()") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Reverses ball's direction") {
        glm::vec2 initial_velocity = test_engine.GetBall().GetBallVelocity();
        test_engine.ReverseBallHorizontalDirection();
        glm::vec2 updated_velocity = test_engine.GetBall().GetBallVelocity();
        REQUIRE(initial_velocity.x == updated_velocity.x * (-1));
        REQUIRE(initial_velocity.y == updated_velocity.y);
    }
}

TEST_CASE("Cases for PaddleLengthIncrement()") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Incrementing the length of the left paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthIncrement("left");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == left_top_corner.y - pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner().y == left_bottom_corner.y + pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner() == right_top_corner);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner() == right_bottom_corner);
    }
    SECTION("Incrementing the length of the right paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthIncrement("right");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner() == left_top_corner);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner() == left_bottom_corner);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == right_top_corner.y - pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner().y == right_bottom_corner.y + pong::kBonusLengthIncrement/2);
    }
    SECTION("Incrementing the length of the neither paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthIncrement("random");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner() == left_top_corner);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner() == left_bottom_corner);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner() == right_top_corner);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner() == right_bottom_corner);
    }
}

TEST_CASE("Cases for PaddleLengthDecrement()") {
    PhysicsEngine test_engine = PhysicsEngine();
    SECTION("Decrementing the length of the left paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthDecrement("left");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner().y == left_top_corner.y + pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner().y == left_bottom_corner.y - pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner() == right_top_corner);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner() == right_bottom_corner);
    }
    SECTION("Decrementing the length of the right paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthDecrement("right");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner() == left_top_corner);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner() == left_bottom_corner);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner().y == right_top_corner.y + pong::kBonusLengthIncrement/2);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner().y == right_bottom_corner.y - pong::kBonusLengthIncrement/2);
    }
    SECTION("Decrementing the length of the neither paddle") {
        glm::vec2 left_top_corner = test_engine.GetLeftPaddle().GetTopLeftCorner();
        glm::vec2 left_bottom_corner = test_engine.GetLeftPaddle().GetBottomRightCorner();
        glm::vec2 right_top_corner = test_engine.GetRightPaddle().GetTopLeftCorner();
        glm::vec2 right_bottom_corner = test_engine.GetRightPaddle().GetBottomRightCorner();
        test_engine.PaddleLengthDecrement("random");
        REQUIRE(test_engine.GetLeftPaddle().GetTopLeftCorner() == left_top_corner);
        REQUIRE(test_engine.GetLeftPaddle().GetBottomRightCorner() == left_bottom_corner);
        REQUIRE(test_engine.GetRightPaddle().GetTopLeftCorner() == right_top_corner);
        REQUIRE(test_engine.GetRightPaddle().GetBottomRightCorner() == right_bottom_corner);
    }
}