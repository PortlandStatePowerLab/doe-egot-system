#include <ecs/server/sep/dcap.hpp>
#include <ecs/server/sep/edev.hpp>
#include <ecs/server/sep/frp.hpp>
#include <ecs/server/sep/frq.hpp>
#include <ecs/server/sep/href.hpp>
#include <ecs/server/sep/ps.hpp>
#include <ecs/server/sep/rg.hpp>
#include <ecs/server/sep/rsp.hpp>
#include <ecs/server/sep/sdev.hpp>
#include <ecs/server/sep/time.hpp>
#include <ecs/server/sep/uri.hpp>
#include <ecs/server/sep/world.hpp>
#include <sstream>
#include <utilities/utilities.hpp>
#include <sep/xml/adapter.hpp>

using namespace gsp;
extern std::string g_program_path;
std::string var;

World *World::instance_{nullptr};
std::mutex World::mutex_;

std::string prependLFDI(const Href &href) {
  return "/" + href.lfdi + href.uri;
};

World::World() {
  world.import <rg::Module>();
  world.import <dcap::Module>();
  world.import <edev::Module>();
  world.import <frp::Module>();
  world.import <frq::Module>();
  world.import <ps::Module>();
  world.import <sdev::Module>();
  world.import <time::Module>();
};

World::~World() {
  // Save entities if required
  delete instance_;
};

World *World::getInstance() {
  std::lock_guard<std::mutex> lock(mutex_);
  if (instance_ == nullptr) {
    instance_ = new World();
  }
  return instance_;
};

std::string World::Get(const Href &href) {
  std::string response = "";

  auto client = world.lookup(href.lfdi.c_str());
  if (client){
    std::cout << "Client is not empty" << std::endl;
  }
  switch (uri_map.at(href.uri)) {
  case (Uri::dcap): {
    // const sep::DeviceCapability *dcap =
    //     client.lookup(href.uri.c_str()).get<sep::DeviceCapability>();
    // if (dcap != nullptr) {
    //   return xml::Serialize(*dcap);
    // }
      client.each([](flecs::id e){
        std::cout << e.first().name() << " : " << e.second().name() << std::endl;
      });
  }; break;
  case (Uri::sdev): {
    const sep::SelfDevice *sdev =
        client.lookup(href.uri.c_str()).get<sep::SelfDevice>();
    if (sdev != nullptr) {
      return xml::Serialize(*sdev);
    }
  }; break;
  case (Uri::edev): {
    const sep::EndDevice *edev =
        client.lookup(href.uri.c_str()).get<sep::EndDevice>();
    if (edev != nullptr) {
      return xml::Serialize(*edev);
    }
  }; break;
  case (Uri::edev_list): {
    sep::EndDeviceList edev_list;
    auto f = world.filter_builder<sep::EndDevice>()
                 .term(client, flecs::ChildOf)
                 .build();

    f.iter([&edev_list, href](flecs::iter &it, sep::EndDevice *edev) {
      for (auto i : it) {
        edev_list.end_devices.emplace_back(edev[i]);
      }
    });

    edev_list.href = href.uri;
    edev_list.all = edev_list.end_devices.size();
    edev_list.results = edev_list.end_devices.size();

    return xml::Serialize(edev_list);
  }; break;
  case (Uri::rg): {
    const sep::Registration *rg =
        client.lookup(href.uri.c_str()).get<sep::Registration>();
    if (rg != nullptr) {
      return xml::Serialize(*rg);
    }
  }; break;
  case (Uri::dstat): {
    // TODO
  }; break;
  case (Uri::fsa): {
    // TODO
  }; break;
  case (Uri::sub): {
    // TODO
  }; break;
  case (Uri::ntfy): {
    // TODO
  }; break;
  case (Uri::rsps): {
    const sep::ResponseSet *rsps =
        client.lookup(href.uri.c_str()).get<sep::ResponseSet>();
    if (rsps != nullptr) {
      return xml::Serialize(*rsps);
    }
  }; break;
  case (Uri::rsps_list): {
    sep::ResponseSetList rsps_list;

    auto f = world.filter_builder<sep::ResponseSet>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.iter([&rsps_list, href](flecs::iter &it, sep::ResponseSet *rsps) {
      for (auto i : it) {
        // this should probably be its own compare lambda function
        rsps_list.response_sets.emplace_back(rsps[i]);
      }
    });

    rsps_list.href = href.uri;
    rsps_list.all = rsps_list.response_sets.size();
    rsps_list.results = rsps_list.response_sets.size();

    return xml::Serialize(rsps_list);
  }; break;
  case (Uri::rsp): {
    const sep::Response *rsp =
        client.lookup(href.uri.c_str()).get<sep::Response>();
    if (rsp != nullptr) {
      return xml::Serialize(*rsp);
    }
  }; break;
  case (Uri::rsp_list): {
    sep::ResponseList rsp_list;

    auto f = world.filter_builder<sep::Response>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.iter([&rsp_list, href](flecs::iter &it, sep::Response *rsp) {
      for (auto i : it) {
        rsp_list.responses.emplace_back(rsp[i]);
      }
    });

    rsp_list.href = href.uri;
    rsp_list.all = rsp_list.responses.size();
    rsp_list.results = rsp_list.responses.size();

    return xml::Serialize(rsp_list);
  }; break;
  case (Uri::tm): {
    const sep::Time *time = world.lookup(href.uri.c_str()).get<sep::Time>();
    if (time != nullptr) {
      return xml::Serialize(*time);
    }
  }; break;
  case (Uri::di): {
    // TODO
  }; break;
  case (Uri::loc): {
    // TODO
  }; break;
  case (Uri::ps): {
    // TODO
  }; break;
  case (Uri::ns): {
    // TODO
  }; break;
  case (Uri::addr): {
    // TODO
  }; break;
  case (Uri::rpl): {
    // TODO
  }; break;
  case (Uri::srt): {
    // TODO
  }; break;
  case (Uri::ll): {
    // TODO
  }; break;
  case (Uri::nbh): {
    // TODO
  }; break;
  case (Uri::lel): {
    // TODO
  }; break;
  case (Uri::cfg): {
    // TODO
  }; break;
  case (Uri::prcfg): {
    // TODO
  }; break;
  case (Uri::file): {
    // TODO
  }; break;
  case (Uri::fs): {
    // TODO
  }; break;
  case (Uri::dr): {
    // TODO
  }; break;
  case (Uri::actedc): {
    // TODO
  }; break;
  case (Uri::edc): {
    // TODO
  }; break;
  case (Uri::lsl): {
    // TODO
  }; break;
  case (Uri::upt): {
    // TODO
  }; break;
  case (Uri::mr): {
    // TODO
  }; break;
  case (Uri::rt): {
    // TODO
  }; break;
  case (Uri::rs): {
    // TODO
  }; break;
  case (Uri::r): {
    // TODO
  }; break;
  case (Uri::mup): {
    // TODO
  }; break;
  case (Uri::tp): {
    // TODO
  }; break;
  case (Uri::rc): {
    // TODO
  }; break;
  case (Uri::acttti): {
    // TODO
  }; break;
  case (Uri::tti): {
    // TODO
  }; break;
  case (Uri::cti): {
    // TODO
  }; break;
  case (Uri::msg): {
    // TODO
  }; break;
  case (Uri::acttxt): {
    // TODO
  }; break;
  case (Uri::txt): {
    // TODO
  }; break;
  case (Uri::bill): {
    // TODO
  }; break;
  case (Uri::ca): {
    // TODO
  }; break;
  case (Uri::actbp): {
    // TODO
  }; break;
  case (Uri::bp): {
    // TODO
  }; break;
  case (Uri::pro): {
    // TODO
  }; break;
  case (Uri::brs): {
    // TODO
  }; break;
  case (Uri::br): {
    // TODO
  }; break;
  case (Uri::tar): {
    // TODO
  }; break;
  case (Uri::ver): {
    // TODO
  }; break;
  case (Uri::ss): {
    // TODO
  }; break;
  case (Uri::ppy): {
    // TODO
  }; break;
  case (Uri::ab): {
    // TODO
  }; break;
  case (Uri::os): {
    // TODO
  }; break;
  case (Uri::actsi): {
    // TODO
  }; break;
  case (Uri::si): {
    // TODO
  }; break;
  case (Uri::cr): {
    // TODO
  }; break;
  case (Uri::frq): {
    const sep::FlowReservationRequest *frq =
        client.lookup(href.uri.c_str()).get<sep::FlowReservationRequest>();
    if (frq != nullptr) {
      return xml::Serialize(*frq);
    }
  }; break;
  case (Uri::frq_list): {
    sep::FlowReservationRequestList frq_list;

    auto f = world.filter_builder<sep::FlowReservationRequest>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.iter(
        [&frq_list, href](flecs::iter &it, sep::FlowReservationRequest *frq) {
          for (auto i : it) {
            frq_list.flow_reservation_requests.emplace_back(frq[i]);
          }
        });

    frq_list.href = href.uri;
    frq_list.all = frq_list.flow_reservation_requests.size();
    frq_list.results = frq_list.flow_reservation_requests.size();

    return xml::Serialize(frq_list);
  }; break;
  case (Uri::frp): {
    const sep::FlowReservationResponse *frp =
        client.lookup(href.uri.c_str()).get<sep::FlowReservationResponse>();
    if (frp != nullptr) {
      return xml::Serialize(*frp);
    }
  }; break;
  case (Uri::frp_list): {
    sep::FlowReservationResponseList frp_list;

    auto f = world.filter_builder<sep::FlowReservationResponse>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.iter(
        [&frp_list, href](flecs::iter &it, sep::FlowReservationResponse *frp) {
          for (auto i : it) {
            frp_list.flow_reservation_responses.emplace_back(frp[i]);
          }
        });

    frp_list.href = href.uri;
    frp_list.all = frp_list.flow_reservation_responses.size();
    frp_list.results = frp_list.flow_reservation_responses.size();

    return xml::Serialize(frp_list);
  }; break;
  case (Uri::der): {
    // TODO
  }; break;
  case (Uri::aupt): {
    // TODO
  }; break;
  case (Uri::derp): {
    // TODO
  }; break;
  case (Uri::cdp): {
    // TODO
  }; break;
  case (Uri::derg): {
    // TODO
  }; break;
  case (Uri::ders): {
    // TODO
  }; break;
  case (Uri::dercap): {
    // TODO
  }; break;
  case (Uri::actderc): {
    // TODO
  }; break;
  case (Uri::dderc): {
    // TODO
  }; break;
  case (Uri::dc): {
    // TODO
  }; break;
  default:
    // TODO
    break;
  }
  return response;
};

std::string World::Post(const Href &href, const std::string &message) {
  auto client = world.lookup(href.lfdi.c_str());
  switch (uri_map.at(href.uri)) {
  case (Uri::rsp_list): {
    sep::Response rsp;
    xml::Parse(message, &rsp);
    auto e = world.entity().child_of(client);
    e.set<sep::Response>(rsp);
    return href.uri + "/" + std::to_string(e.id());
  }; break;
  case (Uri::rsps_list): {
    sep::ResponseSet rsps;
    xml::Parse(message, &rsps);
    auto e = world.entity().child_of(client);
    e.set<sep::ResponseSet>(rsps);
    return href.uri + "/" + std::to_string(e.id());
  }; break;
  case (Uri::frq_list): {
    sep::FlowReservationRequest frq;
    xml::Parse(message, &frq);
    auto e = world.entity().child_of(client);
    e.set<sep::FlowReservationRequest>(frq);

    sep::FlowReservationResponse frp;
    frp.energy_available = frq.energy_requested;
    frp.power_available = frq.power_requested;
    frp.subject = frq.mrid;
    frp.creation_time = psu::utilities::getTime();
    frp.event_status.current_status =
        sep::EventStatus::CurrentStatus::kScheduled;
    frp.event_status.date_time = frp.creation_time;
    frp.event_status.potentially_superseded = false;
    frp.interval.duration = frq.duration_requested;
    frp.interval.start = frq.interval_requested.start +
                         frq.interval_requested.duration -
                         frq.duration_requested;
    frp.description = frq.description;
    frp.energy_available = frq.energy_requested;
    frp.mrid = frq.mrid;
    frp.description = frq.description;
    frp.version = frq.version;
    frp.subscribable = sep::SubscribableType::kNone;

    auto e2 = world.entity().child_of(client);
    e2.set<sep::FlowReservationResponse>(frp);
    return href.uri + "/" + std::to_string(e2.id());
  }; break;
  default:
    return "";
    break;
  };
};

std::string World::Put(const Href &href, const std::string &message) {
  auto client = world.lookup(href.lfdi.c_str());

  switch (uri_map.at(href.uri)) {
  case (Uri::rsp): {
    sep::Response rsp;
    xml::Parse(message, &rsp);

    auto e = client.lookup(href.uri.c_str());

    if (e == false) {
      return "";
    }
    e.set<sep::Response>(rsp);
    return href.uri + "/" + std::to_string(e.id());
  }; break;
  case (Uri::rsps): {
    sep::ResponseSet rsps;
    xml::Parse(message, &rsps);
    auto e = client.lookup(href.uri.c_str());

    if (e == false) {
      return "";
    }

    e.set<sep::ResponseSet>(rsps);
    return href.uri + "/" + std::to_string(e.id());
  }; break;
  case (Uri::frq): {
    sep::FlowReservationRequest frq;
    xml::Parse(message, &frq);
    auto e = client.lookup(href.uri.c_str());

    if (e == false) {
      return "";
    }

    e.set<sep::FlowReservationRequest>(frq);
    return href.uri + "/" + std::to_string(e.id());
  }; break;
  default:
    return "";
    break;
  };
};
void World::Delete(const Href &href) {
  switch (uri_map.at(href.uri)) {
  case (Uri::edev): {
    world.each([href](flecs::entity &e, sep::EndDevice &rsp) {
      // this should probably be its own compare lambda function
      // e.destruct();
    });
  }; break;
  case (Uri::rsp): {
    world.each([href](flecs::entity &e, sep::Response &rsp) {
      // this should probably be its own compare lambda function
      // e.destruct();
    });
  }; break;
  case (Uri::rsps): {
    world.each([href](flecs::entity &e, sep::ResponseSet &rsps) {
      // this should probably be its own compare lambda function
      // e.destruct();
    });
  }; break;
  case (Uri::frq): {
    world.each([href](flecs::entity &e, sep::FlowReservationRequest &frq) {
      // this should probably be its own compare lambda function
      // e.destruct();
    });
  }; break;
  default:
    // response = "";
    break;
  };
};