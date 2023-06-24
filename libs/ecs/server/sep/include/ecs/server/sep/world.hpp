#ifndef __WORLD_H__
#define __WORLD_H__

#include "href.hpp"
#include <flecs.h>
#include <mutex>
#include <thread>

class World {
public:
  // rule of 5
  World(World &other) = delete;           // clonable
  void operator=(const World &) = delete; // assignable
  World();
  ~World();

  static World *getInstance();
  std::string Get(const Href &href);
  std::string Post(const Href &href, const std::string &message);
  std::string Put(const Href &href, const std::string &message);
  void Delete(const Href &href);

public:
  flecs::world world;

private:
  void run();
  // thread-safe singleton instance
  std::thread thread_;
  static World *instance_;
  static std::mutex mutex_;
};

#endif // __WORLD_H__