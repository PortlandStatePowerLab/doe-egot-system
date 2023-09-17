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
#include <ecs/singleton/clock.hpp>
#include <sep/xml/adapter.hpp>
#include <sstream>
#include <utilities/utilities.hpp>

using namespace gsp;
extern std::string g_program_path;
std::string var;

World *World::instance_{nullptr};
std::mutex World::mutex_;

std::string appendSubject(const Href &href) {
  return href.uri.substr(0, href.uri.size() - 1) + href.subject;
};

std::string prependLFDI(const Href &href) {
  return "/" + href.lfdi + href.uri;
};

World::World() {
  world.import <ecs::singleton::Module>();
  ecs::singleton::generateClock(world);
  world.import <rg::Module>();
  rg::generateRegistration(world);
  world.import <dcap::Module>();
  world.import <edev::Module>();
  world.import <time::Module>();
  time::generateTime(world);

  // world.import <sdev::Module>();
  // world.import <frp::Module>();
  // world.import <frq::Module>();
  // world.import <ps::Module>();
  thread_ = std::thread(&World::run, this);
};

World::~World() {
  // Save entities if required
  delete instance_;
  if (thread_.joinable()) {
    thread_.join();
  }
};

void World::run() { world.app().target_fps(1).run(); };

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
  if (client.id() == 0) {
    return response;
  }

  if (uri_map.count(href.uri) == 0) {
    return response;
  }

  switch (uri_map.at(href.uri)) {
  case (Uri::dcap): {
    sep::DeviceCapability dcap;
    dcap.href = "/dcap";
    dcap.poll_rate = 300;
    sep::EndDeviceListLink edev_ll = {};
    edev_ll.all = world.filter_builder<sep::EndDevice>()
                      .term(flecs::ChildOf, client)
                      .build()
                      .count();
    edev_ll.href = "/edev";
    dcap.end_device_list_link.emplace(edev_ll);
    sep::ResponseSetListLink rsps_ll = {};
    rsps_ll.all = world.filter_builder<sep::ResponseSet>()
                      .term(flecs::ChildOf, client)
                      .build()
                      .count();
    rsps_ll.href = "/rsps";
    dcap.response_set_list_link.emplace(rsps_ll);
    sep::TimeLink tm = {};
    tm.href = "/tm";
    dcap.time_link.emplace(tm);
    return xml::Serialize(dcap);
  }; break;
  case (Uri::sdev): {
    return response;
  }; break;
  case (Uri::edev): {
    auto edev = client.lookup(appendSubject(href).c_str());
    if (edev.id() == 0) {
      return response;
    }
    return xml::Serialize(*edev.get<sep::EndDevice>());
  }; break;
  case (Uri::edev_list): {
    sep::EndDeviceList edev_list;
    auto f = world.filter_builder<sep::EndDevice>()
                 .term(flecs::ChildOf, client)
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
    auto rg = client.lookup(appendSubject(href).c_str());
    if (rg.id() == 0) {
      return response;
    }
    return xml::Serialize(*rg.get<sep::Registration>());
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
    auto rsps = client.lookup(appendSubject(href).c_str());
    if (rsps.id() == 0) {
      return response;
    }
    return xml::Serialize(*rsps.get<sep::ResponseSet>());
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
    auto rsp = client.lookup(appendSubject(href).c_str());
    if (rsp.id() == 0) {
      return response;
    }
    return xml::Serialize(*rsp.get<sep::Response>());
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
    auto time = world.lookup(href.uri.c_str());
    if (time.id() == 0) {
      return response;
    }
    return xml::Serialize(*time.get<sep::Time>());
  }; break;
  case (Uri::di): {
    // TODO
  }; break;
  case (Uri::loc): {
    // TODO
  }; break;
  case (Uri::ps): {
    auto ps = client.lookup(href.uri.c_str());
    if (ps.id() == 0) {
      return response;
    }
    return xml::Serialize(*ps.get<sep::PowerStatus>());
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
    auto frq = client.lookup(appendSubject(href).c_str());
    if (frq.id() == 0) {
      return response;
    }
    return xml::Serialize(*frq.get<sep::FlowReservationRequest>());
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
    auto frp = client.lookup(appendSubject(href).c_str());
    if (frp.id() == 0) {
      return response;
    }
    return xml::Serialize(*frp.get<sep::FlowReservationResponse>());
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
    return response;
    break;
  }
  return response;
};

std::string World::Post(const Href &href, const std::string &message) {
  auto client = world.lookup(href.lfdi.c_str());
  switch (uri_map.at(href.uri)) {
  case (Uri::edev_list): {
    sep::EndDevice edev;
    xml::Parse(message, &edev);
    std::string uri = gsp::edev::generateURI(edev);
    auto e = client.lookup(uri.c_str());
    if (e.id() == 0) {
      world.entity(uri.c_str()).child_of(client).set<sep::EndDevice>(edev);
      return uri;
    }
    return "";
  }; break;
  case (Uri::rsp_list): {
    sep::Response rsp;
    xml::Parse(message, &rsp);
    std::string uri = gsp::rsp::generateURI(rsp);
    auto e = client.lookup(uri.c_str());
    if (e.id() == 0) {
      auto e2 = world.entity(uri.c_str()).child_of(client);
      e2.set<sep::Response>(rsp);
      return uri;
    }
    e.set<sep::Response>(rsp);
    return uri;
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
    std::string uri = gsp::frq::generateURI(frq);
    auto e = client.lookup(uri.c_str());
    if (e.id() == 0) {
      world.entity(uri.c_str())
          .child_of(client)
          .set<sep::FlowReservationRequest>(frq);
      sep::FlowReservationResponse frp = gsp::frq::generateResponse(frq);
      world.entity(frp.href.c_str())
          .child_of(client)
          .set<sep::FlowReservationResponse>(frp);
      return frp.href;
    }
    return "";
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
    std::string uri = gsp::rsp::generateURI(rsp);
    auto e = client.lookup(uri.c_str());
    if (e.id() == 0) {
      auto e2 = world.entity(uri.c_str()).child_of(client);
      e2.set<sep::Response>(rsp);
      return uri;
    }
    e.set<sep::Response>(rsp);
    return uri;
  }; break;
  case (Uri::ps): {
    sep::PowerStatus ps;
    xml::Parse(message, &ps);
    auto e = client.lookup(href.uri.c_str());
    if (e.id() == 0) {
      auto e2 = world.entity(href.uri.c_str()).child_of(client);
      e2.set<sep::PowerStatus>(ps);
      return "/ps";
    }
    e.set<sep::PowerStatus>(ps);
    return "/ps";
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
    std::string uri = gsp::frq::generateURI(frq).c_str();
    auto e = client.lookup(uri.c_str());

    if (e.id() == 0) {
      world.entity(uri.c_str())
          .child_of(client)
          .set<sep::FlowReservationRequest>(frq);
    } else {
      e.set<sep::FlowReservationRequest>(frq);
    }
    sep::FlowReservationResponse frp = gsp::frq::generateResponse(frq);
    auto e2 = client.lookup(frp.href.c_str());
    if (e2.id() == 0) {
      world.entity(frp.href.c_str())
          .child_of(client)
          .set<sep::FlowReservationResponse>(frp);
    }
    return frq.href;

  }; break;
  default:
    return "";
    break;
  };
};
void World::Delete(const Href &href) {
  auto client = world.lookup(href.lfdi.c_str());
  switch (uri_map.at(href.uri)) {
  case (Uri::edev): {
    auto e = client.lookup(href.uri.c_str());
    if (e.id() != 0) {
      e.destruct();
    }
  }; break;
  case (Uri::rsp): {
    auto e = client.lookup(href.uri.c_str());
    if (e.id() != 0) {
      e.destruct();
    }
  }; break;
  case (Uri::rsps): {
    auto e = client.lookup(href.uri.c_str());
    if (e.id() != 0) {
      e.destruct();
    }
  }; break;
  case (Uri::frq): {
    auto e = client.lookup(href.uri.c_str());
    if (e.id() != 0) {
      e.destruct();
    }
  }; break;
  default:
    // response = "";
    break;
  };
};