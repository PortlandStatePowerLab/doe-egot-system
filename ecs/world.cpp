#include "include/world/world.hpp"
#include "include/world/sep_support_module.hpp"
#include <xml/adapter.hpp>

World* World::instance_{nullptr};
std::mutex World::mutex_;

World::World()
{
    world.import<sep::SupportModule>();
};

World::~World()
{
    // Save entities if required
    delete instance_;
};

World* World::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (instance_ == nullptr)
    {
        instance_ = new World();
    }
    return instance_;
};

std::string World::Get(const Href &href)
{
    std::string response;

    auto e = world.lookup(request);

    switch (request)
    {
    case ("/dcap"):
        response = xml::Serialize(*e.get<sep::DeviceCapability>());
        break;

    case ("/sdev"):
        response = xml::Serialize(*e.get<sep::SelfDevice>());
        break;
    
    case ("/frq"):
        response = xml::Serialize(*e.get<sep::FlowReservationRequest>());
        break;
    default:
        response = "";
        break;
    }
};