#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <ecs/server/sep/time.hpp>
#include <ecs/singleton/clock.hpp>
#include <https/client/single_client.hpp>

extern std::string g_program_path;

namespace ecs {
namespace server {
namespace time {
void generateTime(flecs::world &world) {
  boost::posix_time::ptime local(boost::posix_time::second_clock::local_time());
  boost::posix_time::ptime universal(
      boost::posix_time::second_clock::universal_time());

  boost::local_time::tz_database tz_db;
  tz_db.load_from_file(g_program_path + "/timezone/date_time_zonespec.csv");

  boost::local_time::time_zone_ptr tz_ptr =
      tz_db.time_zone_from_region("America/Los_Angeles");
  boost::local_time::local_date_time ldt(local, tz_ptr);

  sep::Time tm;
  tm.poll_rate = 900;
  tm.href = "/tm";
  tm.current_time = boost::posix_time::to_time_t(universal);
  tm.dst_end_time = boost::posix_time::to_time_t(
      tz_ptr->dst_local_end_time(ldt.date().year()));
  tm.dst_offset = (tz_ptr->dst_offset()).total_seconds();
  tm.dst_start_time = boost::posix_time::to_time_t(
      tz_ptr->dst_local_start_time(ldt.date().year()));
  tm.local_time = boost::posix_time::to_time_t(local);
  tm.quality = 7; // low accuracy
  tm.tz_offset = (tz_ptr->base_utc_offset()).total_seconds();
  world.entity(tm.href.c_str()).set<sep::Time>(tm);
};

void Module::updateTime(flecs::entity e, sep::Time &tm) {
  auto *clock = e.world().get_mut<ecs::singleton::Clock>();
  tm.current_time = clock->utc;
  tm.local_time = clock->local;
};

Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::Time>();

  world.system<sep::Time>("update-time").each(Module::updateTime);
};
} // namespace time
} // namespace server
} // namespace ecs
