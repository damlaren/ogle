/*
Copyright (c) 2015 damlaren

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file Implementation of application.h.
 */

#include "application/application.h"
#include "easylogging++.h"  // NOLINT

namespace ogle {

Application::Application(std::unique_ptr<Engine> engine)
  : elapsed_time_(0.0), engine_(std::move(engine)) {
}

void Application::RunApplication() {
  last_update_timestep_ = 0.0;

  // TODO(damlaren): Tidy up timing stuff.
  auto target_frame_rate_config = engine_->configuration_.Get<double>(
      "render", "target_frame_rate");
  if (!target_frame_rate_config.second ||
      target_frame_rate_config.first == 0.0) {
    LOG(ERROR) << "Cannot find target frame rate in configuration, "
               << "or it is 0.";
    return;
  }
  target_frame_timestep_ = 1.0 / target_frame_rate_config.first;

  bool app_body_success = true;
  main_timer_.Reset();
  double last_update_carry_over = 0;
  do {
    last_update_timestep_ = main_timer_.Measure() + last_update_carry_over;

    if (last_update_timestep_ >= target_frame_timestep_) {
      if (!engine_->window_->HandleWindowEvents()) {
        break;
      }

      app_body_success = ApplicationBody();

      elapsed_time_ += last_update_timestep_;
      last_update_timestep_ -= target_frame_timestep_;
      last_update_carry_over = last_update_timestep_;

      main_timer_.Reset();
    }

    ++loop_count_;
  } while (app_body_success);
}

}  // namespace ogle
