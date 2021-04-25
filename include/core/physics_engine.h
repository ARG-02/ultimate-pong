#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <string>
#include <vector>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "stdlib.h"

#include "ball.h"
#include "paddle.h"

namespace pong {

const double kWindowLength = 1000;
const double kWindowHeight = 650;
const long kRoundDelay = 3000;
const int kLeftScoreNeeded = 5;
const int kRightScoreNeeded = 5;

class PhysicsEngine {
  public:
    PhysicsEngine();
    /**
     * Sets default ball and two paddles in original starting positions
     */
    void SpawnEntities();
    pong::Ball GetBall();
    pong::Paddle GetLeftPaddle();
    pong::Paddle GetRightPaddle();
    /**
     * Controls paddle movement based on input parameters
     */
    void UserPaddleControl(bool is_left_up_pressed, bool is_left_down_pressed,
                           bool is_right_up_pressed, bool is_right_down_pressed);
    /**
     * Updates the pong ball's position
     */
    void UpdateBallPosition();
    /**
     * Checks if the pong ball hits the ceiling or floor of window
     */
    void CheckWallCollision();
    /**
     * Checks if the ball hit either of the paddles
     */
    void CheckPaddleCollision();
    /**
     * Checks if pong ball has gone past paddle earning one player a point
     */
    void CheckRoundVictory();
    int GetLeftPlayerScore();
    int GetRightPlayerScore();
    /**
     * Checks if either player has won the game based on their score
     */
    void CheckGameVictory();
    void SetLeftPlayerScore(int new_score);
    void SetRightPlayerScore(int new_score);
    bool GetIsInPlay();
    void SetIsInPlay(bool set_in_play);
    bool GetIsGameStart();
    void SetIsGameStart(bool set_game_start);
    /**
     * Reverses the pong ball's horizontal velocity
     */
    void ReverseBallHorizontalDirection();
    /**
     * Increases length of specified paddle
     */
    void PaddleLengthIncrement(const std::string &paddle_name);
    /**
     * Decreases length of specified paddle
     */
    void PaddleLengthDecrement(const std::string &paddle_name);

  private:
    pong::Ball ball_;
    pong::Paddle left_paddle_;
    pong::Paddle right_paddle_;
    int left_player_score_;
    int right_player_score_;
    bool is_in_play_;
    bool is_game_start_;
};

}  // namespace pong

#endif /* PHYSICS_ENGINE_H */

