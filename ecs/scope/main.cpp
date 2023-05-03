#include <flecs.h>
#include <iostream>
#include <string>

struct Fingerprint {
  std::string lfdi;
};

struct Resource {
  std::string data;
};

void iter_tree(flecs::entity e) {
  std::cout << e.path() << std::endl;
  e.children([&](flecs::entity child) { iter_tree(child); });
};

int main(int argc, char **argv) {
  flecs::world ecs;

  auto parent = ecs.entity("First").set<Fingerprint>({"123"});

  auto child =
      ecs.entity("Second").child_of(parent).set<Resource>({"some data"});
	
	auto not_child = 
		ecs.entity("Third").set<Resource>({"some other data"});

  iter_tree(parent);

  const std::string name = "First";
  auto e = ecs.lookup(name.c_str());
  std::cout << "lookup : " << e.path() << std::endl;

	auto base_filter = ecs.filter<Resource>();
	base_filter.each([](flecs::entity e, Resource &res){
		std::cout << "base: " <<  e.path() << std::endl;
	});

	auto scope_filter = ecs.filter_builder<Resource>().term(flecs::ChildOf, parent).build();
	scope_filter.each([](flecs::entity e, Resource &res){
		std::cout << "scope: " << e.path() << std::endl;
	});

  return 0;
}
