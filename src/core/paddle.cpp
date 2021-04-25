#include "core/paddle.h"

namespace pong {

Paddle::Paddle(const glm::vec2 &set_top_left_corner,
               const glm::vec2 &set_bottom_left_corner) {
  top_left_corner_ = set_top_left_corner;
  bottom_right_corner_ = set_bottom_left_corner;
}

Paddle::Paddle() {}

glm::vec2 Paddle::GetTopLeftCorner() {
  return top_left_corner_;
}

void Paddle::SetTopLeftCorner(const glm::vec2 &set_corner) {
  top_left_corner_ = set_corner;
}

glm::vec2 Paddle::GetBottomRightCorner() {
  return bottom_right_corner_;
}

void Paddle::SetBottomRightCorner(const glm::vec2 &set_corner) {
  bottom_right_corner_ = set_corner;
}

void Paddle::MoveUpwards() {
  top_left_corner_.y = top_left_corner_.y - kPaddleMovementSpeed;
  bottom_right_corner_.y = bottom_right_corner_.y - kPaddleMovementSpeed;
}

void Paddle::MoveDownwards() {
  top_left_corner_.y = top_left_corner_.y + kPaddleMovementSpeed;
  bottom_right_corner_.y = bottom_right_corner_.y + kPaddleMovementSpeed;
}

}  // namespace pong

