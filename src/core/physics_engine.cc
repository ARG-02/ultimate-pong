#include <core/physics_engine.h>

using std::vector;

namespace pong {

PhysicsEngine::PhysicsEngine() {
  SpawnEntities();
  left_player_score_ = 0;
  right_player_score_ = 0;
  is_in_play_ = true;
  is_game_start_ = true;
}

void PhysicsEngine::SpawnEntities() {
  // sets default ball with starting position in center of screen
  double velocity_x = (rand() % 11) - 5;
  double velocity_y = (rand() % 11) - 5;
  while (velocity_y == 0 || velocity_x == 0) {
    velocity_x = (rand() % 11) - 5;
    velocity_y = (rand() % 11) - 5;
  }
  glm::vec2 set_ball_velocity = {velocity_x, velocity_y};
  set_ball_velocity = glm::normalize(set_ball_velocity);
  set_ball_velocity.x = set_ball_velocity.x * kBallDefaultSpeedMultiplier;
  set_ball_velocity.y = set_ball_velocity.y * kBallDefaultSpeedMultiplier;
  ball_ = Ball({kWindowLength / 2, kWindowHeight / 2}, set_ball_velocity);

  // sets default left paddle with starting positions vertically centered
  glm::vec2 left_paddle_top_corner = {kWindowBuffer, (kWindowHeight/2) - (kPaddleLength/2)};
  glm::vec2 left_paddle_bottom_corner =
          {kWindowBuffer + kPaddleWidth, (kWindowHeight/2) + (kPaddleLength/2)};
  left_paddle_ = Paddle(left_paddle_top_corner, left_paddle_bottom_corner);

  // sets default right paddle with starting positions vertically centered
  glm::vec2 right_paddle_top_corner =
      {kWindowLength - kWindowBuffer - kPaddleWidth, (kWindowHeight/2) - (kPaddleLength/2)};
  glm::vec2 right_paddle_bottom_corner =
      {kWindowLength - kWindowBuffer, (kWindowHeight/2) + (kPaddleLength/2)};
  right_paddle_ = Paddle(right_paddle_top_corner, right_paddle_bottom_corner);
}

pong::Ball PhysicsEngine::GetBall() {
  return ball_;
}

pong::Paddle PhysicsEngine::GetLeftPaddle() {
  return left_paddle_;
}

pong::Paddle PhysicsEngine::GetRightPaddle() {
  return right_paddle_;
}

void PhysicsEngine::UserPaddleControl(bool is_left_up_pressed, bool is_left_down_pressed,
                                      bool is_right_up_pressed, bool is_right_down_pressed) {
  if (is_left_up_pressed) {
    if (left_paddle_.GetTopLeftCorner().y > 0) {
      left_paddle_.MoveUpwards();
    }
  }
  if (is_left_down_pressed) {
    if (left_paddle_.GetBottomRightCorner().y < kWindowHeight) {
      left_paddle_.MoveDownwards();
    }
  }
  if (is_right_up_pressed) {
    if (right_paddle_.GetTopLeftCorner().y > 0) {
      right_paddle_.MoveUpwards();
    }
  }
  if (is_right_down_pressed) {
    if (right_paddle_.GetBottomRightCorner().y < kWindowHeight) {
      right_paddle_.MoveDownwards();
    }
  }
}

void PhysicsEngine::UpdateBallPosition() {
  ball_.UpdatePosition();
}

void PhysicsEngine::CheckWallCollision() {
  if (ball_.GetBallPosition().y < kBallRadius &&
    ball_.GetBallVelocity().y < 0) { // check collision with ceiling
    ball_.SetBallVelocity({ball_.GetBallVelocity().x, ball_.GetBallVelocity().y * (-1)});
  } else if (ball_.GetBallPosition().y > (kWindowHeight - kBallRadius) &&
     ball_.GetBallVelocity().y > 0) { // check collision with floor
     ball_.SetBallVelocity({ball_.GetBallVelocity().x, ball_.GetBallVelocity().y * (-1)});
  }
}

void PhysicsEngine::CheckPaddleCollision() {
  if (ball_.GetBallPosition().x <= kWindowBuffer + kPaddleWidth + kBallRadius &&
    ball_.GetBallPosition().x >= kWindowBuffer + kBallRadius) { // check collision with left paddle
    if (ball_.GetBallPosition().y >= left_paddle_.GetTopLeftCorner().y &&
        ball_.GetBallPosition().y <= left_paddle_.GetBottomRightCorner().y &&
        ball_.GetBallVelocity().x < 0) { // check if pong ball will touch left paddle
      ball_.SetBallVelocity({ball_.GetBallVelocity().x * (-1), ball_.GetBallVelocity().y});
    }
  }
  if (ball_.GetBallPosition().x >= kWindowLength - (kWindowBuffer + kPaddleWidth + kBallRadius) &&
    ball_.GetBallPosition().x <= kWindowLength - (kWindowBuffer + kBallRadius)) { // check collision with right paddle
    if (ball_.GetBallPosition().y >= right_paddle_.GetTopLeftCorner().y &&
        ball_.GetBallPosition().y <= right_paddle_.GetBottomRightCorner().y &&
        ball_.GetBallVelocity().x > 0) { // check if pong ball will touch right paddle
      ball_.SetBallVelocity({ball_.GetBallVelocity().x * (-1), ball_.GetBallVelocity().y});
    }
  }
}

void PhysicsEngine::CheckRoundVictory() {
  // Checks if pong ball has touch left or right wall of window
  if (ball_.GetBallPosition().x <= kBallRadius) {
    right_player_score_++;
    SpawnEntities();
    std::chrono::milliseconds timespan(kRoundDelay);
    std::this_thread::sleep_for(timespan);
  }
  if (ball_.GetBallPosition().x >= kWindowLength - (kBallRadius)) {
    left_player_score_++;
    SpawnEntities();
    std::chrono::milliseconds timespan(kRoundDelay);
    std::this_thread::sleep_for(timespan);
  }
}

int PhysicsEngine::GetLeftPlayerScore() {
  return left_player_score_;
}

int PhysicsEngine::GetRightPlayerScore() {
  return right_player_score_;
}

void PhysicsEngine::CheckGameVictory() {
  if (left_player_score_ >= kLeftScoreNeeded ||
    right_player_score_ >= kRightScoreNeeded) {
    is_in_play_ = false;
  }
}

bool PhysicsEngine::GetIsInPlay() {
  return is_in_play_;
}

void PhysicsEngine::SetIsInPlay(bool set_in_play) {
  is_in_play_ = set_in_play;
}

bool PhysicsEngine::GetIsGameStart() {
  return is_game_start_;
}

void PhysicsEngine::SetIsGameStart(bool set_game_start) {
  is_game_start_ = set_game_start;
}

void PhysicsEngine::SetLeftPlayerScore(int set_score) {
  left_player_score_ = set_score;
}
void PhysicsEngine::SetRightPlayerScore(int set_score) {
  right_player_score_ = set_score;
}

void PhysicsEngine::ReverseBallHorizontalDirection() {
  glm::vec2 current_velocity = ball_.GetBallVelocity();
  current_velocity.x = current_velocity.x * (-1);
  ball_.SetBallVelocity(current_velocity);
}

void PhysicsEngine::PaddleLengthIncrement(const std::string &paddle_name) {
  if (paddle_name == "left") {
    left_paddle_.SetTopLeftCorner(
            {left_paddle_.GetTopLeftCorner().x, left_paddle_.GetTopLeftCorner().y - kBonusLengthIncrement / 2});
    left_paddle_.SetBottomRightCorner({left_paddle_.GetBottomRightCorner().x,
                                       left_paddle_.GetBottomRightCorner().y + kBonusLengthIncrement / 2});
  } else if (paddle_name == "right") {
    right_paddle_.SetTopLeftCorner(
            {right_paddle_.GetTopLeftCorner().x, right_paddle_.GetTopLeftCorner().y - kBonusLengthIncrement / 2});
    right_paddle_.SetBottomRightCorner({right_paddle_.GetBottomRightCorner().x,
                                        right_paddle_.GetBottomRightCorner().y + kBonusLengthIncrement / 2});
  }
}

void PhysicsEngine::PaddleLengthDecrement(const std::string &paddle_name) {
  if (paddle_name == "left") {
    left_paddle_.SetTopLeftCorner(
            {left_paddle_.GetTopLeftCorner().x, left_paddle_.GetTopLeftCorner().y + kBonusLengthIncrement / 2});
    left_paddle_.SetBottomRightCorner({left_paddle_.GetBottomRightCorner().x,
                                       left_paddle_.GetBottomRightCorner().y - kBonusLengthIncrement / 2});
  } else if (paddle_name == "right") {
    right_paddle_.SetTopLeftCorner(
            {right_paddle_.GetTopLeftCorner().x, right_paddle_.GetTopLeftCorner().y + kBonusLengthIncrement / 2});
    right_paddle_.SetBottomRightCorner({right_paddle_.GetBottomRightCorner().x,
                                        right_paddle_.GetBottomRightCorner().y - kBonusLengthIncrement / 2});
  }
}

}  // namespace pong