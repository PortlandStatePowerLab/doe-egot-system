#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include <sep/models.hpp>
#include <flecs.h>
#include "handler.hpp"

//
// Tags
//
// In C++ it is more convenient to define tags as empty structs
struct Scheduled { };
struct Active { };
struct Cancelled { };
struct CancelledWithRandomization { };
struct Superseded { };

//
// Components
//
struct Link
{
    std::string href;
    uint32_t poll_rate;
};

struct LinkList
{
    std::vector<flecs::entity> links;
};

//
// Systems
//
// System names ('Move') use PascalCase. API types use snake_case_t
void Poll(flecs::iter& it, Link *link) {
    for (auto i : it) {
        std::cout << "href: " << link[i].href << ", " << link[i].poll_rate << std::endl;
    }
};

class TestDCM : public ::testing::Test 
{
protected:
    void SetUp() override 
    {   
        // Register the component with the world
        world.component<Link>();
        world.component<LinkList>();

        // Register systems with the world
        world.system<Link>("Poll").iter(Poll);

        boost::property_tree::ptree pt;
        pt.put("DeviceCapability.<xmlattr>.pollRate", 900);
        pt.put("DeviceCapability.<xmlattr>.href", "https://gsp.com/dcap");

        dcap_handler = new handler::DeviceCapability();
        dcap_handler->Handle(pt);
    }

    void TearDown() override
    {
        // do nothing
    }

protected:    
    flecs::world world;
    handler::DeviceCapability *dcap_handler;
};

TEST_F(TestDCM, IsSampleValid) 
{   
   std::cout << "Hello DCM Test" << std::endl;
   world.progress();
}