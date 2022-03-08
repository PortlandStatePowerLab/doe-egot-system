#include "include/world/world.hpp"
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
    world.import<sep::CommonModule>();
    world.import<sep::SupportModule>();
    world.import<sep::SmartEnergyModule>();

    // TODO: move to an initialization/registration system
    // sep::DeviceCapability dcap;
    // dcap.customer_account_list_link.all = 1;
    // dcap.customer_account_list_link.href = "/bill";
    // dcap.demand_response_program_list_link.all = 1;
    // dcap.demand_response_program_list_link.href = "/dr";
    // dcap.der_program_list_link.all = 1;
    // dcap.der_program_list_link.href = "/derp";
    // dcap.end_device_list_link.all = 1;
    // dcap.end_device_list_link.href = "/edev";
    // dcap.file_list_link.all = 1;
    // dcap.file_list_link.href = "/file";
    // dcap.href = "/dcap";
    // dcap.messaging_program_list_link.all = 1;
    // dcap.messaging_program_list_link.href = "/msg";
    // dcap.mirror_usage_point_list_link.all = 1;
    // dcap.mirror_usage_point_list_link.href = "/mup";
    // dcap.poll_rate = 900;
    // dcap.prepayment_list_link.all = 1;
    // dcap.prepayment_list_link.href = "/ppy";
    // dcap.response_set_list_link.all = 1;
    // dcap.response_set_list_link.href = "/rsps";
    // dcap.self_device_link.href = "/sdev";
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
    std::string response;

    switch (uri_map.at(href.uri))
    {
    case (Uri::dcap):
    {
        auto e = world.lookup(href.uri.c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::DeviceCapability>());
        }
    };
    break;
    case (Uri::sdev):
    {
        auto e = world.lookup(href.uri.c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::SelfDevice>());
        }
    };
    break;
    case (Uri::edev):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::EndDevice>());
        }
    };
    break;
    case (Uri::rg):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Registration>());
        }
    };
    break;
    case (Uri::dstat):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DeviceStatus>());
        }
    };
    break;
    case (Uri::fsa):
    {
        auto e = world.lookup(href.uri.c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::FunctionSetAssignmentsBase>());
        }
    };
    break;
    case (Uri::sub):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Subscription>());
        }
    };
    break;
    case (Uri::ntfy):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Notification>());
        }
    };
    break;
    case (Uri::rsps):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ResponseSet>());
        }
    };
    break;
    case (Uri::rsp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Response>());
        }
    };
    break;
    case (Uri::tm):
    {
        auto e = world.lookup(href.uri.c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::Time>());
        }
    };
    break;
    case (Uri::di):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DeviceInformation>());
        }
    };
    break;
    case (Uri::loc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::SupportedLocale>());
        }
    };
    break;
    case (Uri::ps):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::PowerStatus>());
        }
    };
    break;
    case (Uri::ns):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::NetworkStatus>());
        }
    };
    break;
    case (Uri::addr):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::IPAddress>());
        }
    };
    break;
    case (Uri::rpl):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::RPLInstance>());
        }
    };
    break;
    case (Uri::srt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::RPLSourceRoutes>());
        }
    };
    break;
    case (Uri::ll):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::LLinterface>());
        }
    };
    break;
    case (Uri::nbh):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Neighbor>());
        }
    };
    break;
    case (Uri::lel):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::LogEvent>());
        }
    };
    break;
    case (Uri::cfg):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Configuration>());
        }
    };
    break;
    case (Uri::prcfg):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::PriceResponseCfg>());
        }
    };
    break;
    case (Uri::file):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::File>());
        }
    };
    break;
    case (Uri::fs):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::FileStatus>());
        }
    };
    break;
    case (Uri::dr):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DemandResponseProgram>());
        }
    };
    break;
    case (Uri::actedc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ActiveEndDeviceControl>());
        }
    };
    break;
    case (Uri::edc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::EndDeviceControl>());
        }
    };
    break;
    case (Uri::lsl):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::LoadShedAvailability>());
        }
    };
    break;
    case (Uri::upt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::UsagePoint>());
        }
    };
    break;
    case (Uri::mr):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::MeterReading>());
        }
    };
    break;
    case (Uri::rt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ReadingType>());
        }
    };
    break;
    case (Uri::rs):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ReadingSet>());
        }
    };
    break;
    case (Uri::r):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Reading>());
        }
    };
    break;
    case (Uri::mup):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::MirrorUsagePoint>());
        }
    };
    break;
    case (Uri::tp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::TariffProfile>());
        }
    };
    break;
    case (Uri::rc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::RateComponenet>());
        }
    };
    break;
    case (Uri::acttti):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ActriveTimeTariffInterval>());
        }
    };
    break;
    case (Uri::tti):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::TimeTariffInterval>());
        }
    };
    break;
    case (Uri::cti):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ConsumptionTariffInterval>());
        }
    };
    break;
    case (Uri::msg):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::MessagingProgram>());
        }
    };
    break;
    case (Uri::acttxt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ActiveTextMessage>());
        }
    };
    break;
    case (Uri::txt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::TextMessage>());
        }
    };
    break;
    case (Uri::bill):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::CustomerAccount>());
        }
    };
    break;
    case (Uri::ca):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::CustomerAgreement>());
        }
    };
    break;
    case (Uri::actbp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ActiveBillingPeriod>());
        }
    };
    break;
    case (Uri::bp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::BillingPeriod>());
        }
    };
    break;
    case (Uri::pro):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ProjectionReading>());
        }
    };
    break;
    case (Uri::brs):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::BillingReadingSet>());
        }
    };
    break;
    case (Uri::br):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::BillingReading>());
        }
    };
    break;
    case (Uri::tar):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::TargetReading>());
        }
    };
    break;
    case (Uri::ver):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::HistoricalReading>());
        }
    };
    break;
    case (Uri::ss):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::ServiceSupplier>());
        }
    };
    break;
    case (Uri::ppy):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::Prepayment>());
        }
    };
    break;
    case (Uri::ab):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::AccountBalance>());
        }
    };
    break;
    case (Uri::os):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::PrepayOperationStatus>());
        }
    };
    break;
    case (Uri::actsi):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::SupplyInterruptionOverride>());
        }
    };
    break;
    case (Uri::si):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::SupplyInterruptionOverride>());
        }
    };
    break;
    case (Uri::cr):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::CreditRegister>());
        }
    };
    break;
    case (Uri::frq):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::FlowReservationRequest>());
        }
    };
    break;
    case (Uri::frp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            response = xml::Serialize(*e.get<sep::FlowReservationResponse>());
        }
    };
    break;
    case (Uri::der):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DER>());
        }
    };
    break;
    case (Uri::aupt):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::UsagePoint>());
        }
    };
    break;
    case (Uri::derp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERProgram>());
        }
    };
    break;
    case (Uri::cdp):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERProgram>());
        }
    };
    break;
    case (Uri::derg):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERSettings>());
        }
    };
    break;
    case (Uri::ders):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERStatus>());
        }
    };
    break;
    case (Uri::dercap):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERCapability>());
        }
    };
    break;
    case (Uri::actderc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERControl>());
        }
    };
    break;
    case (Uri::dderc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DefaultDERControl>());
        }
    };
    break;
    case (Uri::dc):
    {
        auto e = world.lookup(prependLFDI(href).c_str());
        if (e.id() == 0)
        {
            response = "";
        }
        else
        {
            // TODO: response = xml::Serialize(*e.get<sep::DERCurve>());
        }
    };
    break;
    default:
        // response = "";
        break;
    }
    return response;
};