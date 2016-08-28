/**
 * @file application.cc
 * @brief Implementation of application.h.
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
