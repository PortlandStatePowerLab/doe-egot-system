#ifndef __WORLD_H__
#define __WORLD_H__

#include "href.hpp"
#include <flecs.h>
#include <mutex>
#include <thread>

namespace ecs {
namespace server {
///
/// Singleton ECS world to store all server resources
///
class World {
public:
  // rule of 5
  World(World &other) = delete;           // clonable
  void operator=(const World &) = delete; // assignable
  World();
  ~World();

  ///
  /// get instance of the world
  ///
  /// Note: this is not the best idea for a multi-threaded application, but it
  /// works for now
  ///
  static World *getInstance();
  ///
  /// Handle all HTTP Get requests from clients
  ///
  std::string Get(const Href &href);

  ///
  /// Handle all HTTP Post requests from clients
  ///
  std::string Post(const Href &href, const std::string &message);

  ///
  /// Handle all HTTP Put requests from clients
  ///
  std::string Put(const Href &href, const std::string &message);

  ///
  /// Handle all HTTP Delete requests from clients
  ///
  void Delete(const Href &href);

public:
  flecs::world world;

private:
  ///
  /// start the ECS systems that will run to ensure resources are updated
  /// correctly
  ///
  void run();

  // thread-safe singleton instance
  std::thread thread_;
  static World *instance_;
  static std::mutex mutex_;
};

} // namespace server
} // namespace ecs
#endif // __WORLD_H__
