#include <ecs/server/sep/frq.hpp>
#include <sep/xml/utilities.hpp>
#include <utilities/utilities.hpp>

std::string gsp::frq::generateURI(const sep::FlowReservationRequest &frq) {
  return frq.href + "/" + xml::util::Hexify(frq.mrid);
};

sep::FlowReservationResponse
gsp::frq::generateResponse(const sep::FlowReservationRequest &frq) {
  sep::FlowReservationResponse frp;
  frp.href = "/frp/" + xml::util::Hexify(frq.mrid);
  frp.energy_available = frq.energy_requested;
  frp.power_available = frq.power_requested;
  frp.subject = frq.mrid;
  frp.creation_time = psu::utilities::getTime();
  frp.event_status.current_status = sep::EventStatus::CurrentStatus::kScheduled;
  frp.event_status.date_time = frp.creation_time;
  frp.event_status.potentially_superseded = false;
  sep::DateTimeInterval interval = {};
  interval.start =
      frq.interval_requested.start + frq.interval_requested.duration;
  if (frq.duration_requested.is_initialized()) {
    interval.duration = frq.duration_requested.value();
    interval.start -= interval.duration;
  }
  frp.description = frq.description;
  frp.energy_available = frq.energy_requested;
  frp.mrid = frq.mrid;
  frp.description = frq.description;
  frp.version = frq.version;
  frp.subscribable = sep::SubscribableType::kNone;
  return frp;
};

gsp::frq::Module::Module(flecs::world &world) {
  world.module<Module>();
  world.component<sep::FlowReservationRequest>();
};