#ifndef IDEAL_GAS_APP_H
#define IDEAL_GAS_APP_H

#include "cinder/app/KeyEvent.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "../core/physics_engine.h"

namespace pong {

namespace visualizer {

// font from http://www.mattlag.com/bitfonts/
const ci::Font kScoreFont = ci::Font("Bit5x3", 100);
const ci::Font kTitleFont = ci::Font("Bit5x3", 110);
const ci::Font kStartFont = ci::Font("Bit5x3", 45);

class PongApp : public ci::app::App {
  public:
    PongApp();
    void draw() override;
    void update() override;
    // implementation of keyDown and keyUp inspired by:
    // https://libcinder.org/docs/guides/tour/hello_cinder_chapter3.html
    void keyDown(ci::app::KeyEvent event) override;
    void keyUp(ci::app::KeyEvent event) override;

  private:
    pong::PhysicsEngine physics_engine_;
    bool is_left_up_pressed_;
    bool is_left_down_pressed_;
    bool is_right_up_pressed_;
    bool is_right_down_pressed_;
    const char left_up_ = 'w';
    const char left_down_ = 's';
    const char start_key_ = 'c';
    const char restart_key_ = 'r';
    const char left_length_increase_ = 'd';
    const char left_length_decrease_ = 'a';
    const char reduce_right_score_ = 'q';
    const char increase_left_score_ = 'e';
    const char reduce_left_score_ = ',';
    const char increase_right_score_ = '.';
};

}  // namespace visualizer

}  // namespace pong

#endif /* IDEAL_GAS_APP_H */