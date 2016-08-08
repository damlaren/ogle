#ifndef OGLE_INCLUDES_APPLICATION_APPLICATION_H_
#define OGLE_INCLUDES_APPLICATION_APPLICATION_H_

#include "std/ogle_std.inc"
#include "engine/engine.h"

/**
 * @file Defines Application.
 */

namespace ogle {

/**
 * @brief Base class for all ogle applications.
 *
 * All applications are implemented as children of this class, by overriding
 * the #ApplicationBody member.
 */
class Application {
 public:
  /**
   * @brief The entry point and main loop of the Application.
   *
   * It takes the following steps while ApplicationBody() returns true:
   * - Calls #HandleWindowEvents on its Window, exits if it returns false.
   * - Calls #ApplicationBody.
   */
  void RunApplication();

 protected:
  /**
   * @brief Constructor.
   *
   * It exists to receive passed resources. It should not do any other
   * initialization-- that is the responsibility of #Create().
   *
   * unique_ptr parameters refer to objects the Application will take ownership
   * over. They are invalid after constructing the Application.
   *
   * @param engine ogle Engine object.
   */
  explicit Application(std::unique_ptr<Engine> engine);

  /**
   * @brief Destructor.
   *
   * Responsible for releasing all objects owned by the Application.
   */
  virtual ~Application() = default;

  /**
   * @brief Creates a usable Application.
   * @return success or failure.
   */
  virtual bool Create() = 0;

  /**
   * @brief Function to execute in main loop.
   * @return true to run next loop iteration, false to stop.
   */
  virtual bool ApplicationBody() = 0;

  // TODO(damlaren): All timer stuff should go into the engine, eventually.
  // Probably once the app framework is scrapped altogether in favor of
  // individual scripts.

  /// Timer for application's main loop.
  Timer main_timer_;

  /// Target timestep at which to update frames.
  double target_frame_timestep_;

  /// Last timestep for updating object state.
  double last_update_timestep_;

  /// Total time elapsed while running application.
  double elapsed_time_;

  /// ogle Engine object.
  std::unique_ptr<Engine> engine_;

  /// How many times the body has completed.
  std::uint64_t loop_count_ = 0;
};

}  // namespace ogle

#endif  // OGLE_INCLUDES_APPLICATION_APPLICATION_H_
