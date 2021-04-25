#ifndef FINAL_PROJECT_PADDLE_H
#define FINAL_PROJECT_PADDLE_H

#include "cinder/gl/gl.h"

namespace pong {

const double kPaddleLength = 100;
const double kPaddleWidth = 15;
const double kWindowBuffer = 30;
const double kPaddleMovementSpeed = 10;
const double kBonusLengthIncrement = 25;

class Paddle {
  public:
    /**
     * creates rectangular Paddle using two corners vectors as bounds
     */
    Paddle(const glm::vec2 &set_top_left_corner,
           const glm::vec2 &set_bottom_left_corner);
    Paddle();
    glm::vec2 GetTopLeftCorner();
    void SetTopLeftCorner(const glm::vec2 &set_corner);
    glm::vec2 GetBottomRightCorner();
    void SetBottomRightCorner(const glm::vec2 &set_corner);
    /**
     * Moves paddle upwards to top of window
     */
    void MoveUpwards();
    /**
     * Moves paddle downwards to bottom of window
     */
    void MoveDownwards();

  private:
    glm::vec2 top_left_corner_;
    glm::vec2 bottom_right_corner_;
};

}

#endif //FINAL_PROJECT_PADDLE_H
