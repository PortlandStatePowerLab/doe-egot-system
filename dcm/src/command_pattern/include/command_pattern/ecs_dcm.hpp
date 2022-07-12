#ifndef __ECS_DCM_H__
#define __ECS_DCM_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <flecs.h>
#include <sstream>
#include <https/https_client.hpp>
#include <https/combined_client.hpp>
#include <sep/models.hpp>
#include <xml/adapter.hpp>
#include <xml/xml_validator.hpp>
#include <ecs/der_simulator.hpp>
#include <ecs/der_components_module.hpp>
#include <ecs/dcm_components_module.hpp>
#include "../../../cta2045_receiver/include/cta2045_receiver/cta2045_receiver.hpp"
#include "s_sim_invoker.hpp"

static const std::string FLOW_RESERVATION_REQUEST = R"(<?xml version="1.0" encoding="utf-8"?>
<FlowReservationRequest href="http://uri1" xmlns="urn:ieee:std:2030.5:ns">
  <mRID>0FB7</mRID>
  <description>description1</description>
  <version>0</version>
  <creationTime>1</creationTime>
  <durationRequested>0</durationRequested>
  <energyRequested>
    <multiplier>1</multiplier>
    <value>-140737488355328</value>
  </energyRequested>
  <intervalRequested>
    <duration>0</duration>
    <start>1</start>
  </intervalRequested>
  <powerRequested>
    <multiplier>1</multiplier>
    <value>1</value>
  </powerRequested>
  <RequestStatus>
    <dateTime>1</dateTime>
    <requestStatus>0</requestStatus>
  </RequestStatus>
</FlowReservationRequest>)";

namespace dcm
{

class ECS_DCM
{
public:
  ECS_DCM();
  ECS_DCM(const std::string &root);
  ~ECS_DCM();
  void SetReceiver();
  void RunSimulatorLoop();
  void TestCTA2045Commands();
  void AddFlowResRespEntity(sep::FlowReservationResponse &flowresresp);
  sep::FlowReservationResponse GetFlowResRespFromGSP();
  void InitializeFlowResInvokingSystems();

private:
  flecs::world dcm_world_;
  xml::XMLCommandAdapter xml_writer_;
  CombinedHttpsClient *combined_client_;
  BaseInvoker *sim_flow_invoker_;
  BaseReceiver *receiver_;
  ImportEnergy *import_energy_c_;
  ExportEnergy *export_energy_c_;
  GetEnergy *get_energy_c_;
  GetNameplate *get_nameplate_c_;
  Idle *idle_c_;
  CriticalPeakEvent *crit_peak_c_;
  GridEmergencyEvent *grid_emergency_c_;

  //BaseInvoker * sim_invoker_;
};

} //namespace dcm
#endif //__ECS_DCM_H__