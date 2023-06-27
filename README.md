# ICSs Virtualized Lab for Cybersecurity Testing

**Project Status:** `Development`

> Supported by [@sfl0r3nz05](sfigueroa@ceit.es).

## Description 

- The aim of this project is to develop and deploy of an ICS virtualized network on which to perform security tests.

- The specific use case to be implemented is that of a *Waster Water Treatment Plant (WWTP)*. However the project may integrate other use cases such as the [Tennesse-Eastman](http://depts.washington.edu/control/LARRY/TE/download.html).

- This project is related to the [OT-NWbasedOnGNS3](https://github.com/sfl0r3nz05/OT-NWbasedOnGNS3) project, aiming to deploy the use case of this project on a larger ICS network.

- The project consists of four container-based components: [OpenPLC](https://github.com/thiagoralves/OpenPLC_v3), [Scada-LTS](https://github.com/SCADA-LTS/Scada-LTS), [ICS Process]() and [Attacker]().

- These components are deployed in two ways: [Docker compose network]() and [GNS3 network simulation]().

## State of the Art

Compilation of works related to the theme of the project

  1. [Development of an Open-Source Testbed Based on the Modbus Protocol for Cybersecurity Analysis of Nuclear Power Plants](./StateofArt/applsci-12-07942.pdf)

## Requirements

- For deployment based on `docker compose`:

  1. [Install basic requirements](./documentation/Requirements/basic-requirements.md).

- For deployment based on `GNS3`:

  > **Note**: For deployment over GNS3, the same previous requirements should be used.

  1. [GNS3 server installation](./documentation/Requirements/gns3.md)

## Build and set up the component containers and network to be deployed

- This section explains how to build and set-up the containers that will be imported in both the `docker compose` and `GNS3`.

  1. [OpenPLC container creation](./documentation/Components/OpenPLC.md)

  2. ICS Process containers:

      > **Note:** The following containers will be associated with the industrial processes to be integrated in the project

      1. [WWTP Process container based on Matlab](./documentation/Components/Matlab.md)

  3. Scada-LTS:

     1. For `docker-compose` deployment use the container included into the [docker-compose.yml](./network/DockerDeployment/ICSNetwork/docker-compose.yml) file.
     2. For `gns3` use the following [Scada-BR container importation](./documentation/Components/Scada-LTS-GNS3.md)

        > **Note:** Follow this step to set-up the ScadaBR container once it is deployed: [Scada-BR](./documentation/Components/Scada-LTS.md)

  4. [Attacker container creation](./documentation/Components/Attacker.md)

- This section also considers how to build and set-up the network to be deployed.

  1. [Network](./documentation/Components/Network.md)

## Use cases virtualized

  > **Note:** Next it is analyzed how to deploy the different use cases.

1. [Water Heater Experiment](./documentation/UseCases/WaterHeater.md)
2. [Water Waste Tratement Plant (WWTP)](./documentation/UseCases/WWTP.md)


## To Do

1. Migrate [ScadaBR](https://github.com/bitelxux/scadabr) to [ScadaLTS](https://github.com/SCADA-LTS/Scada-LTS)
2. Properly document the use case [Water Heater Experiment](./documentation/UseCases/WaterHeater.md)
3. Properly document the use case [Water Waste Tratement Plant (WWTP)](./documentation/UseCases/WWTP.md)

