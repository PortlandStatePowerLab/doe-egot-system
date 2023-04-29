#include "include/world/world.hpp"
#include "include/world/access_module.hpp"
#include "include/world/sep_support_module.hpp"
#include "include/world/sep_common_module.hpp"
#include "include/world/sep_smart_energy_module.hpp"
#include "include/world/uri.hpp"
#include <xml/adapter.hpp>
#include <utilities/utilities.hpp>
#include <sstream>

extern std::string g_program_path;

bool accessMatch(const AccessModule::Fingerprint& lfdi, const AccessModule::Subject& subject, const Href &href)
{
    return lfdi.value == href.lfdi && subject.value == href.subject;
}

bool accessMatch(const AccessModule::Fingerprint& lfdi, const Href &href)
{
    return lfdi.value == href.lfdi;
}

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
    // TODO: save state
};

World &World::getInstance()
{
    static World instance_;
    return instance_;
};

std::string World::Get(const Href &href)
{
    std::string response = "";

    if (uri_map.count(href.uri) == 0)
    {
        return response;
    }

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
        auto f = world.filter<sep::SelfDevice, AccessModule::Fingerprint, AccessModule::Subject>();

        f.iter([&response, href](flecs::iter& it, sep::SelfDevice* sdev, AccessModule::Fingerprint *lfdi, AccessModule::Subject *subject) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i], subject[i], href))
                {
                    response = xml::Serialize(sdev[i]);
                }
            }
        });
    };
    break;
    case (Uri::edev):
    {
        // More complex filters can first be created, then iterated
        auto f = world.filter<sep::EndDevice, AccessModule::Fingerprint, AccessModule::Subject>();

        f.iter([&response,href](flecs::iter& it, sep::EndDevice* edev, AccessModule::Fingerprint *lfdi, AccessModule::Subject *subject) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i], subject[i], href))
                {
                    response = xml::Serialize(edev[i]);
                }
            }
        });
    };
    break;
    case (Uri::edev_list):
    {
        sep::EndDeviceList edev_list;
        //auto e = world.lookup(prependLFDI(href).c_str());

        // More complex filters can first be created, then iterated
        auto f = world.filter<sep::EndDevice, AccessModule::Fingerprint>();

        f.iter([&edev_list,href](flecs::iter& it, sep::EndDevice* edev, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                if (accessMatch(lfdi[i], href))
                {
                    edev_list.end_devices.emplace_back(edev[i]);
                }
            }
        });

        response = xml::Serialize(edev_list);
    };
    break;
    case (Uri::rg):
    {
        auto f = world.filter<sep::Registration, AccessModule::Fingerprint>();

        f.each([&response, href](const sep::Registration& rg, const AccessModule::Fingerprint& lfdi) 
        {        
            if (accessMatch(lfdi, href))
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
        auto f = world.filter<sep::ResponseSet, AccessModule::Fingerprint, AccessModule::Subject>();

        f.each([&response, href](const sep::ResponseSet& rsps, const AccessModule::Fingerprint& lfdi, const AccessModule::Subject& subject) 
        {        
            if (accessMatch(lfdi, subject, href))
            {
                response = xml::Serialize(rsps);
            }
        });
    };
    break;
    case (Uri::rsps_list):
    {
        std::vector<sep::ResponseSet> rsps_list;
        sep::List list;

        auto f = world.filter<sep::ResponseSet, AccessModule::Fingerprint>();

        f.iter([&rsps_list,href](flecs::iter& it, sep::ResponseSet* rsps, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i], href))
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
        auto f = world.filter<sep::Response, AccessModule::Fingerprint, AccessModule::Subject>();

        f.each([&response, href](const sep::Response& rsp, const AccessModule::Fingerprint& lfdi, const AccessModule::Subject& subject) 
        {        
            if (accessMatch(lfdi, subject, href))
            {
                response = xml::Serialize(rsp);
            }
        });
    };
    break;
    case (Uri::rsp_list):
    {
        std::vector<sep::Response> rsp_list;
        sep::List list;

        auto f = world.filter<sep::Response, AccessModule::Fingerprint>();

        f.iter([&rsp_list,href](flecs::iter& it, sep::Response* rsp, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i], href))
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
        auto f = world.filter<sep::FlowReservationRequest, AccessModule::Fingerprint, AccessModule::Subject>();

        f.each([&response, href](const sep::FlowReservationRequest& frq, const AccessModule::Fingerprint &lfdi, const AccessModule::Subject& subject) 
        {        
            // this should probably be its own compare lambda function
            if (accessMatch(lfdi, subject, href))
            {
                response = xml::Serialize(frq);
            }
        });
    };
    break;
    case (Uri::frq_list):
    {
        std::vector<sep::FlowReservationRequest> frq_list;
        sep::List list;

        auto f = world.filter<sep::FlowReservationRequest, AccessModule::Fingerprint>();

        f.iter([&frq_list,href](flecs::iter& it, sep::FlowReservationRequest* frq, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i],href))
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
        auto f = world.filter<sep::FlowReservationResponse, AccessModule::Fingerprint, AccessModule::Subject>();

        f.each([&response, href](const sep::FlowReservationResponse& frp, const AccessModule::Fingerprint &lfdi, const AccessModule::Subject& subject) 
        {        
            // this should probably be its own compare lambda function
            if (accessMatch(lfdi, subject, href))
            {
                response = xml::Serialize(frp);
            }
        });
    };
    break;
    case (Uri::frp_list):
    {
        std::vector<sep::FlowReservationResponse> frp_list;
        sep::List list;

        auto f = world.filter<sep::FlowReservationResponse, AccessModule::Fingerprint>();

        f.iter([&frp_list,href](flecs::iter& it, sep::FlowReservationResponse* frp, AccessModule::Fingerprint *lfdi) 
        {        
            for (auto i : it) 
            {
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi[i], href))
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

std::string World::Post(const Href &href, const std::string& message)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::rsp_list):
        {
            auto e = world.entity();

            sep::Response rsp;
            xml::Parse(message, &rsp);
            e.set<sep::Response>(rsp);

            AccessModule::Fingerprint fingerprint;
            fingerprint.value = href.lfdi;
            e.set<AccessModule::Fingerprint>(fingerprint);

            AccessModule::Subject subject;
            subject.value = rsp.subject.convert_to<std::string>();
            e.set<AccessModule::Subject>(subject);
            return href.uri + "/" + subject.value;
        };
        break;
        case (Uri::rsps_list):
        {
            auto e = world.entity();

            sep::ResponseSet rsps;
            xml::Parse(message, &rsps);
            e.set<sep::ResponseSet>(rsps);

            AccessModule::Fingerprint fingerprint;
            fingerprint.value = href.lfdi;
            e.set<AccessModule::Fingerprint>(fingerprint);

            AccessModule::Subject subject;
            subject.value = rsps.mrid.convert_to<std::string>();
            e.set<AccessModule::Subject>(subject);
            return href.uri + "/" + subject.value;
        };
        break;
        case (Uri::frq_list):
        {
            auto e = world.entity();

            sep::FlowReservationRequest frq;
            xml::Parse(message, &frq);
            e.set<sep::FlowReservationRequest>(frq);

            AccessModule::Fingerprint fingerprint;
            fingerprint.value = href.lfdi;
            e.set<AccessModule::Fingerprint>(fingerprint);

            AccessModule::Subject subject;
            subject.value = xml::util::Hexify(frq.mrid);
            e.set<AccessModule::Subject>(subject);

            sep::FlowReservationResponse frp;
            frp.href = href.uri + "/" + subject.value;
            frp.energy_available = frq.energy_requested;
            frp.power_available = frq.power_requested;
            frp.subject = xml::util::Hexify(frq.mrid);
            frp.creation_time = psu::utilities::getTime();
            frp.event_status.current_status = sep::CurrentStatus::kScheduled;
            frp.event_status.date_time = frp.creation_time;
            frp.event_status.potentially_superseded = false;
            frp.interval.duration = frq.duration_requested;
            frp.interval.start = frq.interval_requested.start 
                + frq.interval_requested.duration 
                - frq.duration_requested;
            frp.description = frq.description;
            frp.energy_available = frq.energy_requested;
            frp.mrid = frq.mrid;
            frp.description = frq.description;
            frp.version = frq.version;
            frp.subscribable = sep::SubscribableType::kNone;

            auto e2 = world.entity();
            e2.set<sep::FlowReservationResponse>(frp);
            e2.set<AccessModule::Fingerprint>(fingerprint);
            e2.set<AccessModule::Subject>(subject);

            return frp.href;
        };
        break;
        default:
            return "";
            break;
    };
};

std::string World::Put(const Href &href, const std::string& message)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::rsp):
        {
            auto e = world.entity();

            sep::Response rsp;
            xml::Parse(message, &rsp);

            AccessModule::Fingerprint lfdi;
            lfdi.value = xml::util::Hexify(rsp.end_device_lfdi);

            AccessModule::Subject subject;
            subject.value = xml::util::Hexify(rsp.subject);

            if (accessMatch(lfdi, subject, href))
            {
                e.set<sep::Response>(rsp);
                e.set<AccessModule::Fingerprint>(lfdi);
                e.set<AccessModule::Subject>(subject);
                return href.uri + "/" + subject.value;
            }
        };
        break;
        case (Uri::rsps):
        {
            auto e = world.entity();

            sep::ResponseSet rsps;
            xml::Parse(message, &rsps);

            AccessModule::Fingerprint lfdi;
            lfdi.value = href.lfdi;

            AccessModule::Subject subject;
            subject.value = xml::util::Hexify(rsps.mrid);

            if (accessMatch(lfdi, subject, href))
            {
                e.set<sep::ResponseSet>(rsps);
                e.set<AccessModule::Fingerprint>(lfdi);
                e.set<AccessModule::Subject>(subject);
                return href.uri + "/" + subject.value;
            }
        };
        break;
        case (Uri::frq):
        {
            auto e = world.entity();

            sep::FlowReservationRequest frq;
            xml::Parse(message, &frq);

            AccessModule::Fingerprint lfdi;
            lfdi.value = href.lfdi;

            AccessModule::Subject subject;
            subject.value = xml::util::Hexify(frq.mrid);

            if (accessMatch(lfdi, subject, href))
            {
                e.set<sep::FlowReservationRequest>(frq);
                e.set<AccessModule::Fingerprint>(lfdi);
                e.set<AccessModule::Subject>(subject);
                return href.uri + "/" + subject.value;
            }
        };
        break;
        case (Uri::ps):
        {
            auto e = world.entity();

            sep::PowerStatus ps;
            xml::Parse(message, &ps);
            e.set<sep::PowerStatus>(ps);

            AccessModule::Fingerprint fingerprint;
            fingerprint.value = href.lfdi;
            e.set<AccessModule::Fingerprint>(fingerprint);

            return "";
        };
        break;
        default:
            return "";
            break;
    };
    return "";
};

void World::Delete(const Href &href)
{
    switch (uri_map.at(href.uri))
    {
        case (Uri::edev):
        {
            world.each([href](flecs::entity& e, sep::EndDevice &rsp, AccessModule::Fingerprint &lfdi, AccessModule::Subject& subject) 
            {        
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi, subject, href))
                {
                    e.destruct();
                }
            });
        };
        break;
        case (Uri::rsp):
        {
            world.each([href](flecs::entity& e, sep::Response &rsp, AccessModule::Fingerprint &lfdi, AccessModule::Subject& subject) 
            {        
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi, subject, href))
                {
                    e.destruct();
                }
            });
        };
        break;
        case (Uri::rsps):
        {
            world.each([href](flecs::entity& e, sep::ResponseSet &rsps, AccessModule::Fingerprint &lfdi, AccessModule::Subject& subject) 
            {        
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi, subject, href))
                {
                    e.destruct();
                }
            });
        };
        break;
        case (Uri::frq):
        {
            world.each([href](flecs::entity& e, sep::FlowReservationRequest &frq, AccessModule::Fingerprint &lfdi, AccessModule::Subject& subject) 
            {        
                // this should probably be its own compare lambda function
                if (accessMatch(lfdi, subject, href))
                {
                    e.destruct();
                }
            });
        };
        break;
        default:
            // response = "";
            break;
    };
};