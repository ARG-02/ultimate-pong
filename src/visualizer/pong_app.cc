#include <visualizer/pong_app.h>

namespace pong {

namespace visualizer {

PongApp::PongApp() {
  physics_engine_ = PhysicsEngine();
  is_left_up_pressed_ = false;
  is_left_down_pressed_ = false;
  is_right_up_pressed_ = false;
  is_right_down_pressed_ = false;
}


void PongApp::draw() {
    if (physics_engine_.GetIsInPlay()) {
        // refreshes window
        ci::gl::clear("black");
        ci::app::setWindowSize(kWindowLength, kWindowHeight);
        if (physics_engine_.GetIsGameStart()) {
            // draws intro
            ci::gl::color(1, 1, 1); // white
            ci::gl::drawStringCentered("ULTIMATE PONG",
                                       ci::vec2(kWindowLength / 2, kWindowHeight / 3),
                                       ci::Color("white"),
                                       kTitleFont);
            ci::gl::drawStringCentered("Press [c] to start game!",
                                       ci::vec2(kWindowLength / 2, kWindowHeight / 2),
                                       ci::Color("white"),
                                       kStartFont);
            return;
        }
        // draws left paddle
        ci::gl::color(1, 1, 1); // white
        ci::gl::drawSolidRect(ci::Rectf(physics_engine_.GetLeftPaddle().GetTopLeftCorner(),
                                        physics_engine_.GetLeftPaddle().GetBottomRightCorner()));
        // draws right paddle
        ci::gl::color(1, 1, 1); // white
        ci::gl::drawSolidRect(ci::Rectf(physics_engine_.GetRightPaddle().GetTopLeftCorner(),
                                        physics_engine_.GetRightPaddle().GetBottomRightCorner()));
        // draws ball
        ci::gl::color(1, 1, 1); // white
        ci::gl::drawSolidCircle(physics_engine_.GetBall().GetBallPosition(), kBallRadius);

        // draws player scores
        ci::gl::drawStringCentered(std::to_string(physics_engine_.GetLeftPlayerScore()),
                                   ci::vec2(kWindowLength / 4, kWindowHeight / 8),
                                   ci::Color("white"),
                                   kScoreFont);
        ci::gl::drawStringCentered(std::to_string(physics_engine_.GetRightPlayerScore()),
                                   ci::vec2(3 * kWindowLength / 4, kWindowHeight / 8),
                                   ci::Color("white"),
                                   kScoreFont);
    } else {
        // refreshes window
        ci::gl::clear("black");
        ci::app::setWindowSize(kWindowLength, kWindowHeight);

        // draws player scores
        ci::gl::drawStringCentered(std::to_string(physics_engine_.GetLeftPlayerScore()),
                                   ci::vec2(kWindowLength / 4, kWindowHeight / 8),
                                   ci::Color("white"),
                                   kScoreFont);
        ci::gl::drawStringCentered(std::to_string(physics_engine_.GetRightPlayerScore()),
                                   ci::vec2(3 * kWindowLength / 4, kWindowHeight / 8),
                                   ci::Color("white"),
                                   kScoreFont);

        // draws game over
        ci::gl::drawStringCentered("GAME OVER",
                                   ci::vec2(kWindowLength / 2, kWindowHeight / 3),
                                   ci::Color("white"),
                                   kTitleFont);
        ci::gl::drawStringCentered("Press [r] to replay!",
                                   ci::vec2(kWindowLength / 2, kWindowHeight / 2),
                                   ci::Color("white"),
                                   kStartFont);
    }
}

void PongApp::update() {
  if (!physics_engine_.GetIsGameStart()) {
    if (physics_engine_.GetIsInPlay()) {
        physics_engine_.UserPaddleControl(is_left_up_pressed_,
                                          is_left_down_pressed_,
                                          is_right_up_pressed_,
                                          is_right_down_pressed_);
      physics_engine_.CheckWallCollision();
      physics_engine_.CheckPaddleCollision();
      physics_engine_.CheckRoundVictory();
      physics_engine_.CheckGameVictory();
      physics_engine_.UpdateBallPosition();
    }
  }
}

void PongApp::keyDown(ci::app::KeyEvent event) {
  // paddle movement
  if (event.getChar() == left_up_) {
    is_left_up_pressed_ = true;
  }
  if (event.getChar() == left_down_) {
    is_left_down_pressed_ = true;
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_UP) {
    is_right_up_pressed_ = true;
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_DOWN) {
    is_right_down_pressed_ = true;
  }
  // game state controllers
  if (event.getChar() == start_key_) {
    physics_engine_.SetIsGameStart(false);
  }
  if (event.getChar() == restart_key_) {
    physics_engine_.SetLeftPlayerScore(0);
    physics_engine_.SetRightPlayerScore(0);
    physics_engine_.SpawnEntities();
    physics_engine_.SetIsInPlay(true);
  }
  // reverse ball direction
  if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
    physics_engine_.ReverseBallHorizontalDirection();
  }
  // paddle length modifiers
  if (event.getChar() == left_length_decrease_) {
    physics_engine_.PaddleLengthDecrement("left");
  }
  if (event.getCode() == left_length_increase_) {
    physics_engine_.PaddleLengthIncrement("left");
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_LEFT) {
    physics_engine_.PaddleLengthDecrement("right");
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT) {
    physics_engine_.PaddleLengthIncrement("right");
  }
  // player score modifiers
  if (event.getChar() == reduce_right_score_) {
    physics_engine_.SetRightPlayerScore(physics_engine_.GetRightPlayerScore() - 1);
  }
  if (event.getChar() == increase_right_score_) {
    physics_engine_.SetRightPlayerScore(physics_engine_.GetRightPlayerScore() + 1);
  }
  if (event.getChar() == reduce_left_score_) {
    physics_engine_.SetLeftPlayerScore(physics_engine_.GetLeftPlayerScore() - 1);
  }
  if (event.getChar() == increase_left_score_) {
    physics_engine_.SetLeftPlayerScore(physics_engine_.GetLeftPlayerScore() + 1);
  }
}

void PongApp::keyUp(ci::app::KeyEvent event) {
  if (event.getChar() == left_up_) {
    is_left_up_pressed_ = false;
  }
  if (event.getChar() == left_down_) {
    is_left_down_pressed_ = false;
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_UP) {
    is_right_up_pressed_ = false;
  }
  if (event.getCode() == ci::app::KeyEvent::KEY_DOWN) {
    is_right_down_pressed_ = false;
  }
}

}  // namespace visualizer

}  // namespace pong
