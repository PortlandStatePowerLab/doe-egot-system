#include "include/command_pattern/ecs_dcm.hpp"

using namespace dcm;

ECS_DCM::ECS_DCM() : 
        combined_client_(nullptr),
        receiver_(nullptr),
        sim_flow_invoker_(nullptr),
        import_energy_c_(nullptr),
        export_energy_c_(nullptr),
        get_energy_c_(nullptr),
        get_nameplate_c_(nullptr),
        idle_c_(nullptr),
        crit_peak_c_(nullptr),
        grid_emergency_c_(nullptr)
{
    //SetReceiver();
    //need a program path
}

ECS_DCM::ECS_DCM(const std::string &root) : 
        combined_client_(nullptr),
        receiver_(nullptr),
        sim_flow_invoker_(nullptr),
        import_energy_c_(nullptr),
        export_energy_c_(nullptr),
        get_energy_c_(nullptr),
        get_nameplate_c_(nullptr),
        idle_c_(nullptr),
        crit_peak_c_(nullptr),
        grid_emergency_c_(nullptr)
{
    std::cout << " ECS_DCM root arg overload constructor reduced" << std::endl;
    
    combined_client_ = new CombinedHttpsClient(root, "localhost", "4430", root, "localhost", "4430");
    SetReceiver(); //have to init after https init
    import_energy_c_ = new ImportEnergy(combined_client_, receiver_);
    export_energy_c_ = new ExportEnergy(combined_client_, receiver_);
    get_energy_c_ = new GetEnergy(combined_client_, receiver_);
    get_nameplate_c_ = new GetNameplate(combined_client_, receiver_);
    idle_c_ = new Idle(combined_client_, receiver_);
    sim_flow_invoker_ = new SimpleSimulatorFlowResInvoker(&dcm_world_, import_energy_c_,
                                                          export_energy_c_, get_energy_c_,
                                                          get_nameplate_c_, idle_c_, crit_peak_c_); 
    crit_peak_c_ = new CriticalPeakEvent(combined_client_, receiver_);
    grid_emergency_c_ = new GridEmergencyEvent(combined_client_, receiver_);
    dcm_world_.import<dcm::dcm_components_module>();
    std::string startup_msg = xml_writer_.WriteMsg("DCM", "DTM", "CTA2045_Message", "DCM_Startup", "DCM system starting up");
    combined_client_->Post("DTM", startup_msg);
}

ECS_DCM::~ECS_DCM()
{
    std::string shutdown_msg = xml_writer_.WriteMsg("DCM", "DTM", "CTA2045_Message", "DCM_Shutdown", "DCM system shutting down");
    combined_client_->Post("DTM", shutdown_msg);
    std::cout << "  ECS_DCM Destructor" << std::endl;
    if (combined_client_)
        delete combined_client_;
    std::cout << "1" << std::endl;
    if (sim_flow_invoker_)
    {
        std::cout << "1.5" << std::endl;
        delete sim_flow_invoker_;
    }
    std::cout << "2" << std::endl;
    if (receiver_)
        delete receiver_;
    std::cout << "3" << std::endl;
    if (import_energy_c_)
        delete import_energy_c_;
    std::cout << "4" << std::endl;
    if (export_energy_c_)
        delete export_energy_c_;
    std::cout << "5" << std::endl;
    if (get_energy_c_)
        delete get_energy_c_;
    std::cout << "6" << std::endl;
    if (get_nameplate_c_)
        delete get_nameplate_c_;
    std::cout << "7" << std::endl;
    if (idle_c_)
        delete idle_c_;
    std::cout << "8" << std::endl;
    if (crit_peak_c_)
        delete crit_peak_c_;
    std::cout << "9" << std::endl;
    if (grid_emergency_c_)
        delete grid_emergency_c_;
    std::cout << "10" << std::endl;
}

void ECS_DCM::SetReceiver()
{
    std::cout << " ECS_DCM::SetReceiver(), please type 0 for simulator and 1 for CTA2045 " << std::endl;
    // imaginary comms tests, or pre-defined binary init
    int choice = 0;
    std::cin >> choice;
    std::cin.ignore(100, '\n');
    if (choice)
    {
        receiver_ = new CTA2045Receiver(combined_client_);
    }
    else
        receiver_ = new SimpleSimulatorReceiver; //emulated DER
}

void ECS_DCM::RunSimulatorLoop()
{
    // TODO
}

void ECS_DCM::TestCTA2045Commands()
{
    
    bool shutdown = false;

    while (!shutdown)
	{
        std::cout << "TESTING CTA-2045 COMMANDS" << std::endl;
        std::cout << "c - GetEnergy() " << std::endl;
        std::cout << "n - GetNameplate() " << std::endl;
        std::cout << "i - ImportEnergy() " << std::endl;
        std::cout << "e - ExportEnergy() " << std::endl;
        std::cout << "d - Idle() " << std::endl;
        std::cout << "p - CriticalPeakEvent() " << std::endl;
        std::cout << "q - quit " << std::endl;
        std::cout << "==============" << std::endl;

		char c = getchar();
        std::cin.ignore(100, '\n');
        
		switch (c)
		{
			case 'c':
				get_energy_c_->Execute();
				break;
			case 'n':
				get_nameplate_c_->Execute();
				break;
            case 'i':
				import_energy_c_->Execute();
				break;
            case 'e':
				export_energy_c_->Execute();
				break;
            case 'd':
				idle_c_->Execute();
				break;
            case 'p':
				crit_peak_c_->Execute();
				break;
			case 'q':
				shutdown = true;
				break;
			default:
				std::cout << "invalid command" << std::endl;;
				break;
		}
        std::cout << "==============" << std::endl;
	}
    
}

void ECS_DCM::AddFlowResRespEntity(sep::FlowReservationResponse &flowresresp)
{
    // TODO
}

sep::FlowReservationResponse ECS_DCM::GetFlowResRespFromGSP()
{
    // TODO
}

void ECS_DCM::InitializeFlowResInvokingSystems()
{
    // TODO
}