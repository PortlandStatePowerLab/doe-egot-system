#include "include/sep_support_module.hpp"
#include "include/cta2045_module.hpp"
#include <trust_gsp_client.hpp>
#include <ieee-2030.5/support_models.hpp>
#include <xml/adapter.hpp>
#include <utilities/utilities.hpp>


namespace sep
{
    
SupportModule::SupportModule(flecs::world& ecs) 
{
    // Declare cases 
    struct Movement {
        struct Walking { };
        struct Running { };
    };

    struct Direction {
        struct Front { };
        struct Back { };
        struct Left { };
        struct Right { };
    };

    /* Register module with world */
    ecs.module<sep::SupportModule>();
    ecs.module<cta2045::UniversalModule>();

    // https://ajmmertens.medium.com/why-storing-state-machines-in-ecs-is-a-bad-idea-742de7a18e59
    // Register switch types so flecs knows which cases belong to which switch
    ecs.type().component<Movement>()
        .add<Movement::Walking>()
        .add<Movement::Running>();

    ecs.type().component<Direction>()
        .add<Direction::Front>()
        .add<Direction::Back>()
        .add<Direction::Left>()
        .add<Direction::Right>();

    /* Register components */
    ecs.component<sep::VersionInformation>();
    ecs.component<sep::DeviceCapability>();
    ecs.component<sep::FunctionSetAssignmentsBase>();
    ecs.component<sep::EndDevice>();
    ecs.component<sep::SelfDevice>();
    ecs.component<sep::Response>();
    ecs.component<sep::MeterReadingBase>();
    ecs.component<sep::MirrorMeterReading>();
    ecs.component<sep::MirrorUsagePoint>();

    /* Register system */    
    ecs.system<>("Initialize IEEE Resources")
        .kind(flecs::OnLoad)
        .iter([&](flecs::iter it) {  
            TrustGSPClient *client = TrustGSPClient::getInstance();

            auto resp = client->Get("/dcap");
            std::string msg = boost::beast::buffers_to_string(resp.body().data());
            
            sep::DeviceCapability dcap;
            xml::Parse(msg, &dcap);
            ecs.entity().set<sep::DeviceCapability>(dcap);

            resp = client->Get(dcap.end_device_list_link.href);
            msg = boost::beast::buffers_to_string(resp.body().data());
            
            std::vector<sep::EndDevice> edevs;
            xml::Parse(msg, &edevs);
            for (auto edev : edevs)
            {
                if (edev.lfdi == client->getLFDI())
                {
                    ecs.entity().set<sep::EndDevice>(edev);
                }
            }

            // TODO: implement the MUP parsers
            // resp = client->Get(dcap.mirror_usage_point_list_link.href);
            // std::string msg = boost::beast::buffers_to_string(resp.body().data());

            // std::vector<sep::MirrorUsagePoint> mups;
            // xml::Parse(msg, &mups);
            // for (auto mup : mups)
            // {
            //     if (edev.lfdi == client->getLFDI())
            //     {
            //         ecs.entity().set<sep::EndDevice>(edev);
            //     }
            // }

            resp = client->Get(dcap.self_device_link.href);
            msg = boost::beast::buffers_to_string(resp.body().data());
            
            sep::SelfDevice sdev;
            xml::Parse(msg, &sdev);
            if (sdev.lfdi == client->getLFDI())
            {
                ecs.entity().set<sep::SelfDevice>(sdev);
            }

            resp = client->Get(dcap.self_device_link.href);
            msg = boost::beast::buffers_to_string(resp.body().data());
            
            sep::Time tm;
            xml::Parse(msg, &tm);
            ecs.entity().set<sep::Time>(tm);
        });

    ecs.system<sep::DeviceCapability>("dcap")
        .iter([](flecs::iter it, sep::DeviceCapability* dcap) {    
            if (dcap->poll_rate % psu::utilities::getTime() == 0)
            {
                for (int i : it)
                {
                    auto resp = GSPClient::getInstance()->Get(dcap->href);
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    xml::Parse(msg, &dcap[i]);
                }
            }
        });

    ecs.system<sep::EndDevice>("edev")
        .iter([&](flecs::iter it, sep::EndDevice* edev) {    
            if (900 % psu::utilities::getTime() == 0)
            {
                for (int i : it)
                {
                    auto resp = GSPClient::getInstance()->Get(edev->href);
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    xml::Parse(msg, &edev[i]);
                }
            }
        });

    ecs.system<sep::SelfDevice>("sdev")
        .iter([&](flecs::iter it, sep::SelfDevice* sdev) {    
            if (sdev->poll_rate % psu::utilities::getTime() == 0)
            {
                for (int i : it)
                {
                    auto resp = GSPClient::getInstance()->Get(sdev->href);
                    std::string msg = boost::beast::buffers_to_string(resp.body().data());
                    xml::Parse(msg, &sdev[i]);
                }
            }
        });
}

} // namespace sep


