# doe-egot-system
Department of Energy - Energy Grid of Things System

## Development

### Linux OS

```
cd doe-egot-system
./setup.sh
```

## Building

```
cd doe-egot-system
cmake -S . -B build
cmake --build build
```

## Project Organization

Compartmentalize all functions into their own folders. 
Build as static or dynamic libraries. 
Allows for easy unit testing
Reduce duplication of work within the main GSP, DCM, and DTM

## Primary Updates

* [ecs](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/temp-system-updates/ecs)
  * The entity component system modules for IEEE 2030.5 Common, Support, and Smart Energy resources has be created and primary components have be registered.
  * The next step will include the addition of specific systems for each resource as needed. 
* [interfaces](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/temp-system-updates/interfaces)
  * The https client and server have been implemented using the Singleton design pattern to make the GSP and DCM implementation easier.
  * The https server now uses the ECS as its backend for resource storage and processing. Currently only the Device Capability resource has been tested, but the remaining resources will be added as we progress through the Test Plan. 
* [standards](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/temp-system-updates/standards)
  * There have been a few updates to the models to bring them more inline with the IEEE standard representation. Most notably all Link and ListLink member variables have been changed.
  * The edits where updated with the xml adapter class and further tests will be written as the Test Plans are develeped.
* [test plans](https://github.com/PortlandStatePowerLab/doe-egot-system/tree/temp-system-updates/test-plans)
  * Stubs have been made for each of the main EGoT components and a Unit Test will be written for each Product Requirment.
  * Currently supporting test outputs have been stored in text files. The XML tests and Https Test using the new ECS as a backend for the server are stored within this folder.


## Scripts Execution

Running a specific script requires users to be in the doe-egot-system main directory. The following guidelines show how to run each script within the bin folder.
* Change the directory to where this repository is cloned by typing:
    * ```cd doe-egot-system```
* To run the ''test_demo'' script, type the following:
    * ```./build/bin/trust_demo```
* To run the ''ScalingClient'' scripts, be sure to run the ``ScalingServer'' first:
    * ```./build/bin/ScalingServer```
* Then run the client script:
    * ```./build/bin/ScalingClient #```
* Note that the "#" at the end of the above command must be repolaced by a number arg as shown [in this issue](https://github.com/PortlandStatePowerLab/doe-egot-system/issues/11#issuecomment-1332925184).
