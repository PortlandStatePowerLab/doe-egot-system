#include <boost/asio/write.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <cstdint>
#include <flecs.h>
#include <iostream>
#include <unordered_map>
// Applications can pass context data to a system. A common use case where this
// comes in handy is when a system needs to iterate more than one query. The
// following example shows how to pass a custom query into a system for a simple
// collision detection example.

struct Service {
  std::string group_id;
  std::string name;
  std::string type;
  uint64_t start_time;
  uint64_t interval_start;
  uint64_t interval_duration;
};

struct Energy : public Service {
  float power;
  float price;
  float ramp;
};
struct Reserve : public Energy {};
struct Voltage : public Service {
  std::unordered_map<double, double> curve;
};
struct Regulation : public Service {
  std::unordered_map<double, double> curve;
};
struct Blackstart : public Energy {};

struct Power {
  double real, imag;
};

struct Forecast {
  double power;
};

struct Available {};

std::string getProgramPath(char *arg[]) {
  boost::filesystem::path p = arg[0];
  p = canonical(p);
  return p.parent_path().string();
};

using boost::property_tree::ptree;
void spawnTopology(const ptree &pt, flecs::entity &e) {
  ptree::const_iterator end = pt.end();
  for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
    std::string name = it->second.get("<xmlattr>.name", "");
    if (!name.empty()) {
      auto child = e.world().entity(name.c_str()).child_of(e);
      std::cout << child.path() << std::endl;
      spawnTopology(it->second, child);
    } else {
      spawnTopology(it->second, e);
    }
  }
};

int decendingPower(flecs::entity_t e1, const Power *p1, flecs::entity_t e2,
                   const Power *p2) {
  (void)e1;
  (void)e2;
  return (p1->real < p2->real);
}

int main(int argc, char *argv[]) {
  flecs::world ecs;

  std::string base = getProgramPath(argv);

  // Create empty property tree object
  ptree tree;

  // Parse the XML into the property tree.
  try {
    std::string file = base + "/data/groups.xml";
    read_xml(file, tree);
    auto root = ecs.entity("root");
    spawnTopology(tree, root);
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  auto sys2 =
      ecs.system<Power>("reallocate").each([](flecs::entity e, Power &pwr) {
        e.set<Power>({pwr.real, pwr.imag});
        auto p = e.parent();
        auto f =
            e.world().filter_builder<Energy>().term(flecs::ChildOf, p).build();
        if (f.count() == 0) {
          std::cout << e.name() << " reallocated to " << p.parent().name()
                    << std::endl;
          e.remove<Available>();
          e.child_of(p.parent());
        }
      });

  auto sys1 = ecs.system<Energy>("substation-energy")
                  .each([](flecs::entity e, Energy &t) {
                    auto p = e.parent();
                    auto f = e.world()
                                 .filter_builder<Power>()
                                 .term(flecs::ChildOf, p)
                                 .build();
                    std::cout << p.name() << " : " << t.power << std::endl;
                    double cum_sum{0};
                    f.each([&cum_sum, p, t](flecs::entity e2, Power &pwr) {
                      std::cout << '\t' << e2.name() << ":" << pwr.real
                                << std::endl;
                      cum_sum += pwr.real;
                      if (cum_sum > t.power) {
                        std::cout << e2.name() << " moving to "
                                  << p.parent().name() << "\n";
                        e2.add<Available>();
                        e2.child_of(p.parent());
                      }
                    });
                  });

  ecs.observer<Power>().event(flecs::OnSet).each([](flecs::entity e, Power &p) {
    std::cout << "Power value has changed !!!! " << e.name() << std::endl;
  });

  Energy abc;
  abc.name = "abc";
  abc.type = "Energy";
  abc.group_id = "global";
  abc.power = 3;
  abc.ramp = 3;
  abc.price = 0;
  abc.start_time = 0;
  abc.interval_duration = 0;
  auto root = ecs.lookup("root");
  std::cout << root.id() << std::endl;
  ecs.entity(abc.name.c_str()).child_of(root).set<Energy>(abc);

  Energy def;
  def.name = "def";
  def.type = "Energy";
  def.group_id = "OL630-632";
  def.power = 2;
  def.ramp = 2;
  def.price = 0;
  def.start_time = 0;
  def.interval_duration = 0;
  auto feeder = ecs.lookup("::root::group-1::OL630-632");
  std::cout << feeder.id() << std::endl;
  ecs.entity(def.name.c_str()).child_of(feeder).set<Energy>(def);

  Energy ghi;
  ghi.name = "ghi";
  ghi.type = "Energy";
  ghi.group_id = "UL632-633";
  ghi.power = 1;
  ghi.ramp = 1;
  ghi.price = 0;
  ghi.start_time = 0;
  ghi.interval_duration = 0;
  auto segment = ecs.lookup("::root::group-1::OL630-632::UL632-633");
  std::cout << segment.id() << std::endl;
  ecs.entity(ghi.name.c_str()).child_of(segment).set<Energy>(ghi);

  auto sp1 = ecs.lookup(
      "::root::group-1::OL630-632::UL632-633::xfmr_633_a_1::tlx_633_a_h_1");
  std::cout << sp1.id() << std::endl;
  auto sp2 = ecs.lookup(
      "::root::group-1::OL630-632::UL632-633::xfmr_633_a_1::tlx_633_a_h_2");
  std::cout << sp2.id() << std::endl;
  auto sp3 = ecs.lookup(
      "::root::group-1::OL630-632::UL632-633::xfmr_633_a_1::tlx_633_a_h_3");
  std::cout << sp3.id() << std::endl;
  ecs.entity("A").child_of(sp1).set<Power>({1, 0});
  ecs.entity("B").child_of(sp2).set<Power>({2, 0});
  ecs.entity("C").child_of(sp3).set<Power>({3, 0});

  // Run the system
  ecs.app().target_fps(1).run();
}
