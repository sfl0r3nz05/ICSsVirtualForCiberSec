# ICS Virtual

- [ICS Virtual](#ics-virtual)
  - [Description](#description)
  - [Requirements](#requirements)
  - [Getting Started](#getting-started)
    - [Getting Started OpenPLC](#getting-started-openplc)
      - [Create your own OpenPLC image](#create-your-own-openplc-image)
      - [Use the OpenPLC image created for the project](#use-the-openplc-image-created-for-the-project)
      - [Follow this recommendation [Only for Modbus]](#follow-this-recommendation-only-for-modbus)
    - [Getting Started Matlab](#getting-started-matlab)
      - [Create your own Matlab Simulink image](#create-your-own-matlab-simulink-image)
      - [Use the matlab simulink image created for the project](#use-the-matlab-simulink-image-created-for-the-project)
      - [Troubleshootings Matlab on Docker](#troubleshootings-matlab-on-docker)
      - [Import Project Files into the PATH before start simulation](#import-project-files-into-the-path-before-start-simulation)
      - [Compile all *.c using mex compiler of Matlab](#compile-all-c-using-mex-compiler-of-matlab)
      - [Run Simulink Project](#run-simulink-project)
    - [Getting started Scada-LTS](#getting-started-scada-lts)
      - [Troubleshootings Scada-LTS](#troubleshootings-scada-lts)
    - [Getting Started Attacker](#getting-started-attacker)
      - [Create your own Attacker image](#create-your-own-attacker-image)
      - [Use the attacker image created for the project](#use-the-attacker-image-created-for-the-project)
    - [Getting Started network](#getting-started-network)
      - [ICSNetwork](#icsnetwork)
      - [Attacker](#attacker)
  - [How to use the project](#how-to-use-the-project)
    - [Deploy ICSNetwork](#deploy-icsnetwork)
    - [Deploy attacker](#deploy-attacker)
  - [How to test connection](#how-to-test-connection)
    - [Install/use ping network tool](#installuse-ping-network-tool)

## Description

This project arises as [@jmuguruza](https://github.com/jmuguruza) final degree project and aims to perform security tests on a water treatment plant. For this purpose, the project integrates 3 basic elements: [OpenPLC](https://github.com/thiagoralves/OpenPLC_v3), [Scada-LTS](https://github.com/SCADA-LTS/Scada-LTS) and [Matlab on Docker](https://github.com/mathworks-ref-arch/matlab-dockerfile).

**Project Status:** `in progress`

## Requirements

1. Install [docker for ubuntu](https://docs.docker.com/engine/install/ubuntu/)
2. [Manage Docker as non-root user](https://docs.docker.com/engine/install/linux-postinstall/)
3. Install [docker-compose for ubuntu](https://docs.docker.com/compose/install/)
4. Install make `sudo apt install make`
5. Install g++:
   1. `sudo apt-get update`
   2. `sudo apt-get install -y g++`

## Getting Started

### Getting Started OpenPLC

#### Create your own OpenPLC image  

- Build openplc image:
  - cd `~/ICSVirtual/openplc`
  - `docker build -t open-plc .`
  
#### Use the OpenPLC image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/ICSNetwork`
- Change the image of the `openplc` service by `sflorenz05/open-plc:v0.1`

#### Follow this recommendation [Only for Modbus]

- Once OpenPLC container is running:
  
- Disable DNP3/EtherNET/IP to use only Modbus protocol:

![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc1.png "OpenPLC 1")

- Load the `*.st` file of the project.
  
- Start PLC.

![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc2.png "OpenPLC 2")

### Getting Started Matlab

#### Create your own Matlab Simulink image

- Run the MATLAB container using this command:
      `docker run -it -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r20XYz -vnc`

  - :r20XYz chooses the release version of the MATLAB container.
  
  - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`
  
  - Run Matlab with `root` permissions: `sudo matlab`

  - Install Matlab Simulink as add-on:

      ![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink1.png "Simulink 1")

      ![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink2.png "Simulink 1")

  - Install gcc, g++, foltran:
    - `sudo apt-get update`
    - `sudo apt-get install -y gcc g++ gfortran`
  
  - [Save changes in container](https://www.mathworks.com/help/cloudcenter/ug/save-changes-in-containers.html)
    - `docker ps`
    - `docker commit <containerID> <repository>:<tag>`
      - E.g.: `docker commit 3d555451f07a mymatlab:r2020a`

#### Use the matlab simulink image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/ICSNetwork`
- Change the image of the `matlab` service by `sflorenz05/matlab_simulink:v0.2`
  
#### Troubleshootings Matlab on Docker

- [Matlab from docker-compose #39](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/39)
- [Installing Simulink as a Docker Matlab add-on #40](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/40)

#### Import Project Files into the PATH before start simulation

![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink3.png "Simulink 3")

#### Compile all *.c using mex compiler of Matlab

- The `*.c` version of all of the following folders must be compiled using mex:
  
  ![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink4.png)

- All files has been compiled by default
- E.g.: If we go inside the `ASU Unit` folder (see the PATH in the following image) we only need to compile the `*.c`, using the command `mex ASU_UNIT.c`. **Important:** `*.mexa64` files are generated.
  
  ![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink5.png "Simulink 5")

#### Run Simulink Project

- Once all the code has been compiled, a new window opens with the simulink project, which must be launched. It must be obtained values like the ones shown in highlighted in the following figure.
  
  ![alt text](https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink6.png)

### Getting started Scada-LTS

- Once Scada-LTS container is running:
  - Login with admin/admin
  - Create empty script in "Scripting"
  - Next go to the "SQL" tab
  - Paste content scripts-one-insert.txt file into the text field "SQL"
    - File `scripts-one-insert.txt` is placed into `~/ICSVirtual/scada-lts/scripts`
  - Click "Submit update"
  - If the operation is successful, the information about adding 12 records will be displayed
  - Then import the project (.json file)
  - Add a data source running on port 502 with host:openplc
  - Make the connection with OpenPLC
  - Add the background image at "Graphical views"

#### Troubleshootings Scada-LTS

- [Graphical views Scada-LTS #1961](https://github.com/SCADA-LTS/Scada-LTS/issues/1961)

### Getting Started Attacker

#### Create your own Attacker image

- Go to attacker folder `cd ~/ICSVirtual/attacker`
- Compile `injection_attack.cpp` file `g++ injection_attack.cpp -o injection_attack -pthread`
- Build image: `docker build -t attacker .`

#### Use the attacker image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/attacker`
- Change the image of the `matlab` service by `sflorenz05/attacker:v0.1`

### Getting Started network

#### ICSNetwork

- Add permissions
  - `cd ~/ICSVirtual/network/ICSNetwork`
  - `sudo chmod +x scripts/*.*`

#### Attacker

- Compile attacker code:
  - `cd ~/ICSVirtual/attacker`
  - `g++ injection_attack.cpp -o injection_attack -pthread`
- Add permissions
  - `cd ~/ICSVirtual/network/attacker`
  - `sudo chmod +x scripts/*.*`
- Set enviromental variables:
  - Copy the `.env.example` and paste in the same path.
    - Rename `.env.example` to `.env`.
  - Inspect the PLC container: `docker inspect <containerid>` to recover IP address of this container
    - Set the `IP_PLC` variable.
    - Set the `FREQ` variable.

## How to use the project

### Deploy ICSNetwork

- `cd ~/ICSVirtual/network/ICSNetwork`

- `make start`

- `make stop`

- `make destroy`

### Deploy attacker

- `cd ~/ICSVirtual/network`

- `make start`

- `make stop`

- `make destroy`

## How to test connection

- `docker inspect <containerid>`
  
- `docker exec -it <containerid> bash`
  
### Install/use ping network tool

- `sudo apt-get update`

- `sudo apt-get install iputils-ping`
  
- ping: `e.g.: ping 192.168.144.3`
