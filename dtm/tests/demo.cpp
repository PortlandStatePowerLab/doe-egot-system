#include <iostream>
#include <trust_cta2045/trust_device.hpp>
#include <trust_https/trust_https.hpp>
#include <https/https_server.hpp>
#include <dtm/dtm_server.hpp>
#include <utilities/utilities.hpp>
#include <ieee-2030.5/models.hpp>
#include <xml/adapter.hpp>
#include <world/world.hpp>
#include <utilities/utilities.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/time_zone_base.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp> //include all types plus i/o

std::string g_program_path;

bool isClientCertification(const boost::filesystem::directory_entry &entry)
{
    std::string filename = entry.path().filename().string();
    return filename.find("client") != std::string::npos &&
           entry.path().extension() == ".crt";
}

void generateDeviceCapabilities ()
{
    sep::DeviceCapability dcap;
    dcap.poll_rate = 900;
    dcap.href = "/dcap";
    dcap.customer_account_list_link.all = 0;
    dcap.customer_account_list_link.href = "/bill";
    dcap.demand_response_program_list_link.all = 0;
    dcap.demand_response_program_list_link.href = "/dr";
    dcap.der_program_list_link.all = 0;
    dcap.der_program_list_link.href = "/derp";
    dcap.file_list_link.all = 0;
    dcap.file_list_link.href = "/file";
    dcap.messaging_program_list_link.all = 0;
    dcap.messaging_program_list_link.href = "/msg";
    dcap.prepayment_list_link.all = 0;
    dcap.prepayment_list_link.href = "/ppy";
    dcap.response_set_list_link.all = 0;
    dcap.response_set_list_link.href = "/rsps";
    dcap.tariff_profile_list_link.all = 0;
    dcap.tariff_profile_list_link.href = "/tp";
    dcap.time_link.href = "/tm";
    dcap.usage_point_list_link.all = 0;
    dcap.usage_point_list_link.href = "/upt";
    dcap.end_device_list_link.all = 0;
    dcap.end_device_list_link.href = "/edev";
    dcap.mirror_usage_point_list_link.all = 0;
    dcap.mirror_usage_point_list_link.href = "/mup";
    dcap.self_device_link.href = "/sdev";

    World::getInstance().world.entity().set<sep::DeviceCapability>(dcap);
};

void generateEndDevice(const std::string &lfdi)
{
    sep::EndDevice edev;
    edev.subscribable = sep::SubscribableType::kNone;
    edev.href = "/edev/" + lfdi;
    edev.configuration_link.href = "/cfg";
    edev.der_list_link.all = 0;
    edev.der_list_link.href = "/der";
    edev.device_category = sep::DeviceCategoryType::kSmartAppliance;
    edev.device_information_link.href = "/di";
    edev.device_status_link.href = "/ds";
    edev.file_status_link.href = "/fs";
    edev.ip_interface_list_link.all = 0;
    edev.ip_interface_list_link.href = "/ns";
    edev.lfdi = xml::util::Dehexify<sep::LFDIType>(lfdi);
    edev.load_shed_availability_list_link.all = 0;
    edev.load_shed_availability_list_link.href = "/lsl";
    edev.log_event_list_link.all = 0;
    edev.log_event_list_link.href = "/lel";
    edev.power_status_link.href = "/ps";
    edev.sfdi = xml::util::getSFDI(lfdi);
    edev.changed_time = psu::utilities::getTime();
    edev.enabled = true;
    edev.flow_reservation_request_list_link.all = 0;
    edev.flow_reservation_request_list_link.href = "/frq";
    edev.flow_reservation_response_list_link.all = 0;
    edev.flow_reservation_response_list_link.href = "/frp";
    edev.function_set_assignments_list_link.all = 0;
    edev.function_set_assignments_list_link.href = "/fsa";
    edev.post_rate = 900;
    edev.registration_link.href = "/rg";
    edev.subscription_list_link.all = 0;
    edev.subscription_list_link.href = "/sub";

    AccessModule::Fingerprint fingerprint;
    fingerprint.value = lfdi;

    AccessModule::Subject subject;
    subject.value = lfdi;

    World::getInstance().world.entity()
    .set<sep::EndDevice>(edev)
    .set<AccessModule::Fingerprint>(fingerprint)
    .set<AccessModule::Subject>(subject);
};

void generateSelfDevice (const std::string& lfdi)
{
    sep::SelfDevice sdev;
    sdev.subscribable = sep::SubscribableType::kNone;
    sdev.href = "/sdev/" + lfdi;
    sdev.configuration_link.href = "/cfg";
    sdev.der_list_link.all = 0;
    sdev.der_list_link.href = "/der";
    sdev.device_category = sep::DeviceCategoryType::kSmartAppliance;
    sdev.device_information_link.href = "/di";
    sdev.device_status_link.href = "/ds";
    sdev.file_status_link.href = "/fs";
    sdev.ip_interface_list_link.all = 0;
    sdev.ip_interface_list_link.href = "/ns";
    sdev.lfdi = xml::util::Dehexify<sep::LFDIType>(lfdi);
    sdev.load_shed_availability_list_link.all = 0;
    sdev.load_shed_availability_list_link.href = "/lsl";
    sdev.log_event_list_link.all = 0;
    sdev.log_event_list_link.href = "/lel";
    sdev.power_status_link.href = "/ps";
    sdev.sfdi = xml::util::getSFDI(lfdi);

    AccessModule::Fingerprint fingerprint;
    fingerprint.value = lfdi;

    AccessModule::Subject subject;
    subject.value = lfdi;

    World::getInstance().world.entity()
        .set<sep::SelfDevice>(sdev)
        .set<AccessModule::Fingerprint>(fingerprint)
        .set<AccessModule::Subject>(subject);
};

void generateRegistration(const std::string &lfdi)
{
    sep::Registration rg;
    rg.href = "/rg/" + lfdi;
    rg.poll_rate = 900;
    rg.date_time_registered = psu::utilities::getTime();
    rg.pin = xml::util::generatePIN(lfdi);

    AccessModule::Fingerprint fingerprint;
    fingerprint.value = lfdi;

    AccessModule::Subject subject;
    subject.value = lfdi;

    World::getInstance().world.entity()
        .set<sep::Registration>(rg)
        .set<AccessModule::Fingerprint>(fingerprint)
        .set<AccessModule::Subject>(subject);
};

void generateTime()
{
    boost::posix_time::ptime local(boost::posix_time::second_clock::local_time());
    boost::posix_time::ptime universal(boost::posix_time::second_clock::universal_time());
    
    boost::local_time::tz_database tz_db;
    tz_db.load_from_file(g_program_path + "/timezone/date_time_zonespec.csv");
    
    boost::local_time::time_zone_ptr tz_ptr = tz_db.time_zone_from_region("America/Los_Angeles");
    boost::local_time::local_date_time ldt(local, tz_ptr);

    sep::Time tm;
    tm.poll_rate = 900;
    tm.href = "/tm";
    tm.current_time = to_time_t(universal);
    tm.dst_end_time = boost::posix_time::to_time_t(tz_ptr->dst_local_end_time(ldt.date().year()));
    tm.dst_offset = (tz_ptr->dst_offset()).total_seconds();
    tm.dst_start_time = boost::posix_time::to_time_t(tz_ptr->dst_local_start_time(ldt.date().year()));
    tm.local_time = boost::posix_time::to_time_t(local);
    tm.quality = 7; // low accuracy
    tm.tz_offset = (tz_ptr->base_utc_offset()).total_seconds();

    World::getInstance().world.entity().set<sep::Time>(tm);
};

void Initialize(const std::string &doc_root)
{
    generateDeviceCapabilities();
    generateTime();
    
    boost::filesystem::path p = doc_root + "/root-ca";
    if (boost::filesystem::exists(p)) // does path p actually exist?
    {
        if (boost::filesystem::is_directory(p)) // is path p a directory?
        {
            for (auto &entry : boost::make_iterator_range(boost::filesystem::directory_iterator(p), {}))
            {
                if (isClientCertification(entry))
                {
                    FILE *fp = fopen(entry.path().c_str(), "r");
                    X509 *cert = PEM_read_X509(fp, NULL, NULL, NULL);

                    // fingerprint
                    unsigned char md[EVP_MAX_MD_SIZE];
                    unsigned int n;
                    X509_digest(cert, EVP_sha256(), md, &n);

                    // 40 hex character length for fingerprint
                    std::ostringstream oss;
                    for (size_t i = 0; i < n; i++)
                    {
                        oss << std::hex << (int)md[i];
                    };
                    std::string lfdi = oss.str().substr(0, 40);

                    generateEndDevice(lfdi);
                    generateSelfDevice(lfdi);
                    generateRegistration(lfdi);
                    
                    X509_free(cert);
                    fclose(fp);
                }
            }
        }
        else
        {
            std::cout << p << " exists, but is not a regular file or directory\n";
        }
    }
    else
    {
        std::cout << p << " does not exist\n";
    }
};

void spawnDTM(int argc, char **argv)
{
    std::cout << "\tSpawning DTM...\n";
    DistributedTrustManagment dtm(argc, argv);
};

void spawnGSP()
{
    std::cout << "\tSpawning GSP...\n";
    Initialize(g_program_path);
    
    HttpsServer server("0.0.0.0", 8080, g_program_path, 8);
};

int main(int argc, char **argv)
{
    std::cout << "Communication demo...\n";
    g_program_path = psu::utilities::getProgramPath(argv);
    std::cout << "Parent Path : " << g_program_path << std::endl;

    std::thread gsp (spawnGSP);
    std::thread dtm (spawnDTM, argc, argv);

    std::this_thread::sleep_for (std::chrono::seconds(1));

    std::cout << "\tSpawning DCM...\n";
    https::Context gsp_ctx = {"1", g_program_path, "0.0.0.0", "8080"};  
    https::Context dtm_ctx = {"1", g_program_path, "0.0.0.0", "8090"};  
    trust::HttpsClient::getInstance(gsp_ctx, dtm_ctx).Get("/dcap");

    gsp.detach(); 
    dtm.detach();
    
    return 0;    
}