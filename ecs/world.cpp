#include "include/world/world.hpp"
#include "include/world/access_module.hpp"
#include "include/world/sep_support_module.hpp"
#include "include/world/sep_common_module.hpp"
#include "include/world/sep_smart_energy_module.hpp"
#include "include/world/uri.hpp"
#include <xml/adapter.hpp>
#include <sstream>

extern std::string g_program_path;

World *World::instance_{nullptr};
std::mutex World::mutex_;

std::string prependLFDI(const Href &href)
{
    return "/" + href.lfdi + href.uri;
};

World::World()
{
    world.import<AccessModule>();
    world.import<sep::CommonModule>();
    world.import<sep::SupportModule>();
    world.import<sep::SmartEnergyModule>();
};

World::~World()
{
    // Save entities if required
    delete instance_;
};

World *World::getInstance()
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
    std::string response = "";

    switch (uri_map.at(href.uri))
    {
    case (Uri::dcap):
    {
        // More complex filters can first be created, then iterated
        auto f = world.filter<sep::DeviceCapability>();

        f.each([&response](const sep::DeviceCapability& dcap) 
        {        
            response = xml::Serialize(dcap);
        });
    };
    break;
    case (Uri::sdev):
    {
        auto f = world.filter<sep::SelfDevice, AccessModule::Fingerprint>();

        f.each([&response, href](const sep::SelfDevice& sdev, const AccessModule::Fingerprint& lfdi) 
        {        
            if (href.lfdi == lfdi.value)
            {
                response = xml::Serialize(sdev);
            }
        });
    };
    break;
    case (Uri::edev):
    {
        std::vector<sep::EndDevice> edev_list;
        sep::List list;
        //auto e = world.lookup(prependLFDI(href).c_str());

        // More complex filters can first be created, then iterated
        auto f = world.filter<sep::EndDevice, AccessModule::Fingerprint>();

        f.iter([&edev_list,href](flecs::iter& it, sep::EndDevice* edev, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (lfdi[i].value == href.lfdi)
                {
                    edev_list.emplace_back(edev[i]);
                }
            }
        });

        list.href = href.uri;
        list.all = edev_list.size();
        list.results = edev_list.size();

        response = xml::Serialize(edev_list, list);
    };
    break;
    case (Uri::rg):
    {
        auto f = world.filter<sep::Registration, AccessModule::Fingerprint>();

        f.each([&response, href](const sep::Registration& rg, const AccessModule::Fingerprint& lfdi) 
        {        
            if (href.lfdi == lfdi.value)
            {
                response = xml::Serialize(rg);
            }
        });
    };
    break;
    case (Uri::dstat):
    {
        // TODO
    };
    break;
    case (Uri::fsa):
    {
        // TODO
    };
    break;
    case (Uri::sub):
    {
        // TODO
    };
    break;
    case (Uri::ntfy):
    {
        // TODO
    };
    break;
    case (Uri::rsps):
    {
        std::vector<sep::ResponseSet> rsps_list;
        sep::List list;

        auto f = world.filter<sep::ResponseSet, AccessModule::Fingerprint>();

        f.iter([&rsps_list,href](flecs::iter& it, sep::ResponseSet* rsps, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (lfdi[i].value == href.lfdi)
                {
                    rsps_list.emplace_back(rsps[i]);
                }
            }
        });

        list.href = href.uri;
        list.all = rsps_list.size();
        list.results = rsps_list.size();

        response = xml::Serialize(rsps_list, list);
    };
    break;
    case (Uri::rsp):
    {
        std::vector<sep::Response> rsp_list;
        sep::List list;

        auto f = world.filter<sep::Response, AccessModule::Fingerprint>();

        f.iter([&rsp_list,href](flecs::iter& it, sep::Response* rsp, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (lfdi[i].value == href.lfdi)
                {
                    rsp_list.emplace_back(rsp[i]);
                }
            }
        });

        list.href = href.uri;
        list.all = rsp_list.size();
        list.results = rsp_list.size();

        response = xml::Serialize(rsp_list, list);
    };
    break;
    case (Uri::tm):
    {
        auto f = world.filter<sep::Time>();

        f.each([&response, href](const sep::Time& tm) 
        {        
            response = xml::Serialize(tm);
        });
    };
    break;
    case (Uri::di):
    {
        // TODO
    };
    break;
    case (Uri::loc):
    {
        // TODO
    };
    break;
    case (Uri::ps):
    {
        // TODO
    };
    break;
    case (Uri::ns):
    {
        // TODO
    };
    break;
    case (Uri::addr):
    {
        // TODO
    };
    break;
    case (Uri::rpl):
    {
        // TODO
    };
    break;
    case (Uri::srt):
    {
        // TODO
    };
    break;
    case (Uri::ll):
    {
        // TODO
    };
    break;
    case (Uri::nbh):
    {
        // TODO
    };
    break;
    case (Uri::lel):
    {
        // TODO
    };
    break;
    case (Uri::cfg):
    {
        // TODO
    };
    break;
    case (Uri::prcfg):
    {
        // TODO
    };
    break;
    case (Uri::file):
    {
        // TODO
    };
    break;
    case (Uri::fs):
    {
        // TODO
    };
    break;
    case (Uri::dr):
    {
        // TODO
    };
    break;
    case (Uri::actedc):
    {
        // TODO
    };
    break;
    case (Uri::edc):
    {
        // TODO
    };
    break;
    case (Uri::lsl):
    {
        // TODO
    };
    break;
    case (Uri::upt):
    {
        // TODO
    };
    break;
    case (Uri::mr):
    {
        // TODO
    };
    break;
    case (Uri::rt):
    {
        // TODO
    };
    break;
    case (Uri::rs):
    {
        // TODO
    };
    break;
    case (Uri::r):
    {
        // TODO
    };
    break;
    case (Uri::mup):
    {
        // TODO
    };
    break;
    case (Uri::tp):
    {
        // TODO
    };
    break;
    case (Uri::rc):
    {
        // TODO
    };
    break;
    case (Uri::acttti):
    {
        // TODO
    };
    break;
    case (Uri::tti):
    {
        // TODO
    };
    break;
    case (Uri::cti):
    {
        // TODO
    };
    break;
    case (Uri::msg):
    {
        // TODO
    };
    break;
    case (Uri::acttxt):
    {
        // TODO
    };
    break;
    case (Uri::txt):
    {
        // TODO
    };
    break;
    case (Uri::bill):
    {
        // TODO
    };
    break;
    case (Uri::ca):
    {
        // TODO
    };
    break;
    case (Uri::actbp):
    {
        // TODO
    };
    break;
    case (Uri::bp):
    {
        // TODO
    };
    break;
    case (Uri::pro):
    {
        // TODO
    };
    break;
    case (Uri::brs):
    {
        // TODO
    };
    break;
    case (Uri::br):
    {
        // TODO
    };
    break;
    case (Uri::tar):
    {
        // TODO
    };
    break;
    case (Uri::ver):
    {
        // TODO
    };
    break;
    case (Uri::ss):
    {
        // TODO
    };
    break;
    case (Uri::ppy):
    {
        // TODO
    };
    break;
    case (Uri::ab):
    {
        // TODO
    };
    break;
    case (Uri::os):
    {
        // TODO
    };
    break;
    case (Uri::actsi):
    {
        // TODO
    };
    break;
    case (Uri::si):
    {
        // TODO
    };
    break;
    case (Uri::cr):
    {
        // TODO
    };
    break;
    case (Uri::frq):
    {
        std::vector<sep::FlowReservationRequest> frq_list;
        sep::List list;

        auto f = world.filter<sep::FlowReservationRequest, AccessModule::Fingerprint>();

        f.iter([&frq_list,href](flecs::iter& it, sep::FlowReservationRequest* frq, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (lfdi[i].value == href.lfdi)
                {
                    frq_list.emplace_back(frq[i]);
                }
            }
        });

        list.href = href.uri;
        list.all = frq_list.size();
        list.results = frq_list.size();

        response = xml::Serialize(frq_list, list);
    };
    break;
    case (Uri::frp):
    {
        std::vector<sep::FlowReservationResponse> frp_list;
        sep::List list;

        auto f = world.filter<sep::FlowReservationResponse, AccessModule::Fingerprint>();

        f.iter([&frp_list,href](flecs::iter& it, sep::FlowReservationResponse* frp, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (lfdi[i].value == href.lfdi)
                {
                    frp_list.emplace_back(frp[i]);
                }
            }
        });

        list.href = href.uri;
        list.all = frp_list.size();
        list.results = frp_list.size();

        response = xml::Serialize(frp_list, list);
    };
    break;
    case (Uri::der):
    {
        // TODO
    };
    break;
    case (Uri::aupt):
    {
        // TODO
    };
    break;
    case (Uri::derp):
    {
        // TODO
    };
    break;
    case (Uri::cdp):
    {
        // TODO
    };
    break;
    case (Uri::derg):
    {
        // TODO
    };
    break;
    case (Uri::ders):
    {
        // TODO
    };
    break;
    case (Uri::dercap):
    {
        // TODO
    };
    break;
    case (Uri::actderc):
    {
        // TODO
    };
    break;
    case (Uri::dderc):
    {
        // TODO
    };
    break;
    case (Uri::dc):
    {
        // TODO
    };
    break;
    default:
        // TODO
        break;
    }
    return response;
};

void World::Post(const Href &href, const std::string& message)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::rsp):
        {
            std::cout << message << std::endl;
            sep::Response rsp;
            xml::Parse(message, &rsp);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(rsp.subject);
            world.entity(entity_id.c_str()).set<sep::Response>(rsp);
        };
        break;
        case (Uri::rsps):
        {
            sep::ResponseSet *rsps;
            xml::Parse(message, rsps);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(rsps->mrid);
            world.entity(entity_id.c_str()).set<sep::ResponseSet>(*rsps);
        };
        break;
        case (Uri::frq):
        {
            sep::FlowReservationRequest *frq;
            xml::Parse(message, frq);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(frq->mrid);
            world.entity(entity_id.c_str()).set<sep::FlowReservationRequest>(*frq);
        };
        break;
        default:
            // response = "";
            break;
    };
};

void World::Put(const Href &href, const std::string& message)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::rsp):
        {
            sep::Response *rsp;
            xml::Parse(message, rsp);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(rsp->subject);
            world.entity(entity_id.c_str()).set<sep::Response>(*rsp);
        };
        break;
        case (Uri::rsps):
        {
            sep::ResponseSet *rsps;
            xml::Parse(message, rsps);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(rsps->mrid);
            world.entity(entity_id.c_str()).set<sep::ResponseSet>(*rsps);
        };
        break;
        case (Uri::frq):
        {
            sep::FlowReservationRequest *frq;
            xml::Parse(message, frq);
            std::string entity_id = prependLFDI(href) + "/" + xml::util::Hexify(frq->mrid);
            world.entity(entity_id.c_str()).set<sep::FlowReservationRequest>(*frq);
        };
        break;
        default:
            // response = "";
            break;
    };
};

void World::Delete(const Href &href)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::rsp):
        {
            std::string entity_id = prependLFDI(href);
            auto e = world.lookup(prependLFDI(href).c_str());
            if (e != 0)
            {
                e.destruct();
            }
        };
        break;
        case (Uri::rsps):
        {
            std::string entity_id = prependLFDI(href);
            auto e = world.lookup(prependLFDI(href).c_str());
            if (e != 0)
            {
                e.destruct();
            }
        };
        break;
        case (Uri::frq):
        {
            std::string entity_id = prependLFDI(href);
            auto e = world.lookup(prependLFDI(href).c_str());
            if (e != 0)
            {
                e.destruct();
            }
        };
        break;
        default:
            // response = "";
            break;
    };
};