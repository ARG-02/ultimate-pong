#include "core/ball.h"

namespace pong {

Ball::Ball(const glm::vec2 &set_ball_position, const glm::vec2 &set_ball_velocity) {
  ball_position_ = set_ball_position;
  ball_velocity_ = set_ball_velocity;
}

glm::vec2 Ball::GetBallPosition() {
  return ball_position_;
}

glm::vec2 Ball::GetBallVelocity() {
  return ball_velocity_;
}

void Ball::SetBallVelocity(const glm::vec2 &set_ball_velocity) {
  ball_velocity_ = set_ball_velocity;
}

void Ball::SetBallPosition(const glm::vec2 &set_ball_position) {
  ball_position_ = set_ball_position;
}

Ball::Ball() {}

void Ball::UpdatePosition() {
  ball_position_ += ball_velocity_;
}
} // namespace pong


