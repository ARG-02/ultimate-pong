#ifndef FINAL_PROJECT_BALL_H
#define FINAL_PROJECT_BALL_H

#include "cinder/gl/gl.h"

namespace pong {

const double kBallRadius = 15;
const double kBallDefaultSpeedMultiplier = 10;

class Ball {
  public:
    /**
     * Constructor taking in 2 vectors which set the pong ball's initial
     * position and velocity
     */
    Ball(const glm::vec2 &set_ball_position, const glm::vec2 &set_ball_velocity);
    Ball();
    glm::vec2 GetBallPosition();
    glm::vec2 GetBallVelocity();
    void SetBallPosition(const glm::vec2 &set_ball_position);
    void SetBallVelocity(const glm::vec2 &set_ball_velocity);
    /**
     * Updates the ball's position based on its velocity vector
     */
    void UpdatePosition();
  private:
    glm::vec2 ball_position_;
    glm::vec2 ball_velocity_;
};
}

#endif //FINAL_PROJECT_BALL_H
