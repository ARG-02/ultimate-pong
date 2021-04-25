#include <visualizer/pong_app.h>

using pong::visualizer::PongApp;

void prepareSettings(PongApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PongApp, ci::app::RendererGl, prepareSettings);
