#include "include/sep/world.hpp"
#include "include/sep/dcap.hpp"
#include "include/sep/edev.hpp"
#include "include/sep/frp.hpp"
#include "include/sep/frq.hpp"
#include "include/sep/href.hpp"
#include "include/sep/ps.hpp"
#include "include/sep/rg.hpp"
#include "include/sep/sdev.hpp"
#include "include/sep/time.hpp"
#include "include/sep/uri.hpp"
#include <sstream>
#include <utilities/utilities.hpp>
#include <xml/adapter.hpp>

using namespace gsp;
extern std::string g_program_path;

World *World::instance_{nullptr};
std::mutex World::mutex_;

std::string prependLFDI(const Href &href) {
  return "/" + href.lfdi + href.uri;
};

World::World() {
  world.import <rp::Module>();
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

  if (uri_map.count(href.uri) == 0) {
    return response;
  }

  auto client = world.lookup(href.lfdi.c_str());

  switch (uri_map.at(href.uri)) {
  case (Uri::dcap): {
    auto f = world.filter<sep::DeviceCapability>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.each([&response](const sep::DeviceCapability &dcap) {
      response = xml::Serialize(dcap);
    });
  }; break;
  case (Uri::sdev): {
    auto f =
        world.filter<sep::SelfDevice>().term(flecs::ChildOf, client).build();
    ;

    f.iter([&response](flecs::iter &it, sep::SelfDevice *sdev) {
      for (auto i : it) {
        response = xml::Serialize(sdev[i]);
      }
    });
  }; break;
  case (Uri::edev): {
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&response](flecs::iter &it, sep::EndDevice *edev) {
      for (auto i : it) {
        response = xml::Serialize(edev[i]);
      }
    });
  }; break;
  case (Uri::edev_list): {
    sep::EndDeviceList edev_list;
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&edev_list, href](flecs::iter &it, sep::EndDevice *edev) {
      for (auto i : it) {
        if (accessMatch(lfdi[i], href)) {
          edev_list.emplace_back(edev[i]);
        }
      }
    });

    list.href = href.uri;
    list.all = edev_list.size();
    list.results = edev_list.size();

    response = xml::Serialize(edev_list, list);
  }; break;
  case (Uri::rg): {
    auto f = world.filter<sep::DeviceCapability>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.each([&response, href](const sep::Registration &rg) {
      if (accessMatch(lfdi, href)) {
        response = xml::Serialize(rg);
      }
    });
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
    auto f = world.filter<sep::DeviceCapability>()
                 .term(flecs::ChildOf, client)
                 .build();

    f.each([&response, href](const sep::ResponseSet &rsps) {
      if (accessMatch(lfdi, subject, href)) {
        response = xml::Serialize(rsps);
      }
    });
  }; break;
  case (Uri::rsps_list): {
    sep::ResponseSetList rsps_list;

    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&rsps_list, href](flecs::iter &it, sep::ResponseSet *rsps){
      for (auto i : it) {
        // this should probably be its own compare lambda function
        if (accessMatch(lfdi[i], href)) {
          rsps_list.emplace_back(rsps[i]);
        }
      }
    });

    list.href = href.uri;
    list.all = rsps_list.size();
    list.results = rsps_list.size();

    response = xml::Serialize(rsps_list, list);
  }; break;
  case (Uri::rsp): {
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.each([&response, href](const sep::Response &rsp){
      if (accessMatch(lfdi, subject, href)) {
        response = xml::Serialize(rsp);
      }
    });
  }; break;
  case (Uri::rsp_list): {
    sep::ResponseList rsp_list;
            
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&rsp_list, href](flecs::iter &it, sep::Response *rsp){
      for (auto i : it) {
        // this should probably be its own compare lambda function
        if (accessMatch(lfdi[i], href)) {
          rsp_list.emplace_back(rsp[i]);
        }
      }
    });

    list.href = href.uri;
    list.all = rsp_list.size();
    list.results = rsp_list.size();

    response = xml::Serialize(rsp_list, list);
  }; break;
  case (Uri::tm): {
    auto f = world.filter<sep::Time>();

    f.each([&response, href](const sep::Time &tm) {
      response = xml::Serialize(tm);
    });
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
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.each([&response, href](const sep::FlowReservationRequest &frq){
      // this should probably be its own compare lambda function
      if (accessMatch(lfdi, subject, href)) {
        response = xml::Serialize(frq);
      }
    });
  }; break;
  case (Uri::frq_list): {
    sep::FlowReservationRequestList frq_list;
            
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&frq_list, href](flecs::iter &it, sep::FlowReservationRequest *frq){
      for (auto i : it) {
        // this should probably be its own compare lambda function
        if (accessMatch(lfdi[i], href)) {
          frq_list.emplace_back(frq[i]);
        }
      }
    });

    list.href = href.uri;
    list.all = frq_list.size();
    list.results = frq_list.size();

    response = xml::Serialize(frq_list, list);
  }; break;
  case (Uri::frp): {
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.each([&response, href](const sep::FlowReservationResponse &frp){
      // this should probably be its own compare lambda function
      if (accessMatch(lfdi, subject, href)) {
        response = xml::Serialize(frp);
      }
    });
  }; break;
  case (Uri::frp_list): {
    sep::FlowReservationResponseList frp_list;
            
    auto f =
        world.filter<sep::EndDevice>().term(flecs::ChildOf, client).build();

    f.iter([&frp_list, href](flecs::iter &it, sep::FlowReservationResponse *frp){
      for (auto i : it) {
        // this should probably be its own compare lambda function
        if (accessMatch(lfdi[i], href)) {
          frp_list.emplace_back(frp[i]);
        }
      }
    });

    list.href = href.uri;
    list.all = frp_list.size();
    list.results = frp_list.size();

    response = xml::Serialize(frp_list, list);
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
    auto e = world.entity().child_of(client);
  switch (uri_map.at(href.uri)) {
  case (Uri::rsp_list): {
    sep::Response rsp;
    xml::Parse(message, &rsp);
    e.set<sep::Response>(rsp);
    return href.uri + "/" + subject.value;
  }; break;
  case (Uri::rsps_list): {
    sep::ResponseSet rsps;
    xml::Parse(message, &rsps);
    e.set<sep::ResponseSet>(rsps);
    return href.uri + "/" + subject.value;
  }; break;
  case (Uri::frq_list): {
    sep::FlowReservationRequest frq;
    xml::Parse(message, &frq);
    e.set<sep::FlowReservationRequest>(frq);

    sep::FlowReservationResponse frp;
    frp.energy_available = frq.energy_requested;
    frp.power_available = frq.power_requested;
    frp.subject = xml::util::Hexify(frq.mrid);
    frp.creation_time = psu::utilities::getTime();
    frp.event_status.current_status = sep::CurrentStatus::kScheduled;
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

    auto e2 = world.entity();
    e2.set<sep::FlowReservationResponse>(frp);
    e2.set<access::Fingerprint>(fingerprint);
    e2.set<access::Subject>(subject);

    return href.uri + "/" + subject.value;
  }; break;
  default:
    return "";
    break;
  };
};

std::string World::Put(const Href &href, const std::string &message) {
    auto e = world.entity().child_of(client);
  switch (uri_map.at(href.uri)) {
  case (Uri::rsp): {
    sep::Response rsp;
    xml::Parse(message, &rsp);

      e.set<sep::Response>(rsp);
      return href.uri + "/" + subject.value;
    }
  }; break;
  case (Uri::rsps): {
    sep::ResponseSet rsps;
    xml::Parse(message, &rsps);

      e.set<sep::ResponseSet>(rsps);
      return href.uri + "/" + subject.value;
    }
  }; break;
  case (Uri::frq): {
    sep::FlowReservationRequest frq;
    xml::Parse(message, &frq);

      e.set<sep::FlowReservationRequest>(frq);
      return href.uri + "/" + subject.value;
    }
  }; break;
  default:
    return "";
    break;
  };
  return "";
};

void World::Delete(const Href &href) {
  switch (uri_map.at(href.uri)) {
  case (Uri::edev): {
    world.each([href](flecs::entity &e, sep::EndDevice &rsp){
      // this should probably be its own compare lambda function
        // e.destruct();
    });
  }; break;
  case (Uri::rsp): {
    world.each([href](flecs::entity &e, sep::Response &rsp){
      // this should probably be its own compare lambda function
        // e.destruct();
    });
  }; break;
  case (Uri::rsps): {
    world.each([href](flecs::entity &e, sep::ResponseSet &rsps){
      // this should probably be its own compare lambda function
        // e.destruct();
    });
  }; break;
  case (Uri::frq): {
    world.each([href](flecs::entity &e, sep::FlowReservationRequest &frq){
      // this should probably be its own compare lambda function
        // e.destruct();
    });
  }; break;
  default:
    // response = "";
    break;
  };
};