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

int main(int, char *[]) {
  flecs::world ecs;

  auto sys1 = ecs.system<Energy>("substation-energy")
                  .each([](flecs::entity e, Energy &t) {
                    auto p = e.parent();
                    auto f = e.world()
                                 .filter_builder<Power>()
                                 .term(flecs::ChildOf, p)
                                 .build();
                    std::cout << e.name() << " child of " << p.name()
                              << std::endl;

                    double cum_sum{0};
                    f.each([&cum_sum, p, t](flecs::entity e2, Power &pwr) {
                      std::cout << e2.name() << " : " << pwr.real << std::endl;
                      cum_sum += pwr.real;
                      if (cum_sum > t.power) {
                        e2.child_of(p.parent());
                      }
                    });
                  });

  auto ieee13 = ecs.entity("ieee13");
  auto bus650 = ecs.entity("bus650").child_of(ieee13).set<Forecast>({3});
  auto bus633 = ecs.entity("bus633").child_of(bus650).set<Forecast>({2});
  auto bus634 = ecs.entity("bus634").child_of(bus633).set<Forecast>({1});

  Energy abc;
  abc.name = "abc";
  abc.type = "Energy";
  abc.group_id = "ieee13";
  abc.power = 3;
  abc.ramp = 3;
  abc.price = 0;
  abc.start_time = 0;
  abc.interval_duration = 0;

  ecs.entity(abc.name.c_str()).child_of(ieee13).set<Energy>(abc);

  Energy def;
  def.name = "def";
  def.type = "Energy";
  def.group_id = "bus650";
  def.power = 2;
  def.ramp = 2;
  def.price = 0;
  def.start_time = 0;
  def.interval_duration = 0;

  ecs.entity(def.name.c_str()).child_of(bus650).set<Energy>(def);

  Energy ghi;
  ghi.name = "ghi";
  ghi.type = "Energy";
  ghi.group_id = "bus633";
  ghi.power = 1;
  ghi.ramp = 1;
  ghi.price = 0;
  ghi.start_time = 0;
  ghi.interval_duration = 0;

  ecs.entity(ghi.name.c_str()).child_of(bus633).set<Energy>(ghi);

  ecs.entity("A").child_of(bus633).set<Power>({1, 0});
  ecs.entity("B").child_of(bus633).set<Power>({2, 0});
  ecs.entity("C").child_of(bus633).set<Power>({3, 0});

  // Run the system
  ecs.app().target_fps(1).run();
}
