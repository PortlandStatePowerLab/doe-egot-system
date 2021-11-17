# doe-egot-system
Department of Energy - Energy Grid of Things System

## Distributed Control Module (DCM)

The DCM facilitate TLS and HTTP communications using the IEEE 2030.5 resource models. The client is responsible for translating the common IEEE 2030.5 models into the specific DER interfaces to implement controls and energy services.

## Distributed Trust Module (DTM)

A DTM evaluates data flows of DCMs and GSPs to check the trust status, update the trust, and create alerts/events. A DTM augments other grid security mechanisms to improve the reliability of the system. The DTM evaluation, which is based on history, expectation, and specific events, outputs appropriate levels of response to different actors.

## Grid Service Provider (GSP)

A GSP provides grid services to a GO through the dispatch of DER that have subscribed to respond to a GO program or mandate. Grid services are the means by which a GO achieves operational objectives.

## Active Branches

* [temp-system-updates](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/temp-system-updates)
  * In an effort to make navigation of this project as well as stream line the development process we are reorganizing the project folders. This work is still in development and will be integrated in parallel to other research efforts.  
  * All of the recent IEEE 2030.5 model additions have been made to this branch as well as the updated sep.xsd to restrict data values to the prescribed restrictions from within the schema. 
* [content-fix](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/content-fix)
  * This branch was setup to fix some of the initial issues when we created a all enclusive system repository rather than several seperate repositories for each individule actor. Since testing requires all actors to be compiled and ran, it seemed best to have them all in a single location for development and testing.
  * This branch also includes the addition of a bash script to automate the build process for the DCM and will eventually have a bash script for each actor.
