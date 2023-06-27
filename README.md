# ICSs Virtualized Lab for Cybersecurity Testing

**Project Status:** `Development`

> Supported by [@sfl0r3nz05](sfigueroa@ceit.es).

## Description 

- The aim of this project is to develop and deploy an ICS virtualized network on which to perform security tests.

- The specific use case to be implemented is that of a *Waster Water Treatment Plant (WWTP)*. However the project may integrate other use cases such as the [Tennesse-Eastman](http://depts.washington.edu/control/LARRY/TE/download.html).

- This project is related to the [OT-NWbasedOnGNS3](https://github.com/sfl0r3nz05/OT-NWbasedOnGNS3) project, aiming to deploy the use case of this project on a larger ICS network.

- The project can be deployed in two ways: [Docker compose network](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/Components/Deployment/Docker-Compose.md) and [GNS3 network simulation](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/Components/Deployment/GNS3.md).

## State of the Art

Compilation of documents related to the project theme

  1. [Development of an Open-Source Testbed Based on the Modbus Protocol for Cybersecurity Analysis of Nuclear Power Plants](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/StateOfArt/Papers/applsci-12-07942.pdf)
  2. [Whitepaper: CHERNOVITE's Emerging Malware Targeting Industrial Control Systems](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/StateOfArt/Papers/Dragos_ChernoviteWP_v2b.pdf)
  3. [Stuxnet: Dissecting a Cyberwarfare Weapon](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/StateOfArt/Papers/Stuxnet_Dissecting_a_Cyberwarfare_Weapon.pdf)

## Installation

- Clone project repository locally:

```shell
git clone https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec.git
```

2. Deploy the Project

- The project can be either deployed on Docker or GNS3, although it is recommended to deploy the project on GNS3.

- For deployment based on `docker compose`:

  - [Install basic requirements](./documentation/Requirements/basic-requirements.md).

- For deployment based on `GNS3`:

  > **Note**: For deployment over GNS3, the same previous requirements should be used.

  - [GNS3 server installation](./documentation/Requirements/gns3.md)

## Component, Container and Network Setup

- This section explains how to build and set-up the containers that will be imported in both `docker compose` and `GNS3`.

  1. [OpenPLC container creation](./documentation/Components/OpenPLC.md)

  2. ICS Process containers:

      > **Note:** The following containers will be associated with the industrial processes to be integrated in the project

      1. [WWTP Process container based on Matlab](./documentation/Components/Matlab.md)
      2. [SimLink interface](./documentation/Components/SimLink.md)

  3. Scada-LTS-MySQL:

     1. For `docker-compose` deployment use the container included into the [docker-compose.yml](./network/DockerDeployment/ICSNetwork/docker-compose.yml) file.
     2. For `gns3` use the following [Scada-LTS-MySQL container importation](./documentation/Components/Scada-LTS-GNS3.md)

        > **Note:** Follow this step to set-up the ScadaLTS-MySQL container once it is deployed: [Scada-LTS-MySQL](./documentation/Components/Scada-LTS.md)

  4. [Attacker container creation](./documentation/Components/Attacker.md)

- This section also considers how to build and set-up the network to be deployed.

  1. [Network](./documentation/Components/Network.md)

## Use cases virtualized

  > **Note:** Next it is analyzed how to deploy the different use cases.

1. [Water Heater Experiment](./documentation/UseCases/WaterHeater.md)
2. [Water Waste Tratement Plant (WWTP)](./documentation/UseCases/WWTP.md)


## Cybersecurity Measures

- As referenced by [MITRE](https://attack.mitre.org/software/S1045/) and [Dragos](https://www.dragos.com/blog/industry-news/chernovite-pipedream-malware-targeting-industrial-control-systems/), the so-called INCONTROLLER or PIPEDREAM malware developed by the group CHERNOVITE is capable of targeting multiple ICS systems from different vendors and perfor attack successfully.
- One of the most common attacks is the [Parameter Modification](https://attack.mitre.org/techniques/T0836/), which is the one performed in this [demonstration video](https://youtu.be/W10l6Pk4seo?t=843). This attack consist of changing the actual value of a PLC register into another one chosen by the attacker.
- To try to avoid this kind of attacks, an [alarm script](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/Components/Alarm.md) has been developed and implemented into the project.
- The GNS3 project file containing the alarm container can be found in [network/GNS3Deployment/demo.gns3project](./network/GNS3Deployment/demo.gns3project).
- To run the project with the alarm script, just download it and follow the [GNS3 Project Deployment Guide](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/Components/Deployment/GNS3.md)


## To Do

- [x] Document Project
- [x] Write attack-detection table for each case
- [ ] Deploy whole project on GNS3
  - [ ] Try to fix sporadic errors
  - [ ] Implement pfsense on host
  - [ ] Implement wazhu as GNS3 container
  - [x] Develop paper algorithm
  - [x] implement algorithm on GNS3
- [ ] Fix WWTP-OpenPLC interface deployment problem
  - [ ] [OpenPLC Forum feedback](https://openplc.discussion.community/post/openplc-simulink-interface-problem-12648120)
- [ ] Implement ModTester automatization
- [x] Research for attack behaviour measurements and measurement methods
  - [x] Network based methods: pfsense, firewall, etc.

