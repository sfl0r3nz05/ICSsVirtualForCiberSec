# WWTP-based virtualized ICS lab for cyber security testing

## Description

- This project is currently under development and is supported by [@sfl0r3nz05](sfigueroa@ceit.es). The aim of this project is to develop the deployment of an ICS network on which to perform security tests. 

- The specific use case to be implemented is that of a *Waster Water Treatment Plant (WWTP)*. However the project may integrate other use cases such as the [Tennesse-Eastman](http://depts.washington.edu/control/LARRY/TE/download.html).

- This project is related to the [OT-NWbasedOnGNS3](https://github.com/sfl0r3nz05/OT-NWbasedOnGNS3) project, aiming to deploy the use case of this project on a larger ICS network.

- The project has four components:
  1. [OpenPLC](https://github.com/thiagoralves/OpenPLC_v3)
  2. [Scada-LTS](https://github.com/SCADA-LTS/Scada-LTS)
  3. [WWTP]()
  4. [Attacker]()

- These components are deployed in two ways:
  1. [Docker compose network]()
  2. [GNS3 network simulation]()

**Project Status:** `in progress`

## Requirements

1. Install [docker for ubuntu](https://docs.docker.com/engine/install/ubuntu/).
2. [Manage Docker as non-root user](https://docs.docker.com/engine/install/linux-postinstall/).
   1. If it does not work try running `sudo chmod o+rw /var/run/docker.sock` after adding a new user
3. Install [docker-compose for ubuntu](https://docs.docker.com/compose/install/).
4. Install make `sudo apt install make`.
5. Install g++:
   1. `sudo apt-get update`
   2. `sudo apt-get install -y g++`

## Getting Started

### Getting Started OpenPLC

<details>

<summary>Open to see details</summary>

#### Create your own OpenPLC image  

- Build openplc image:
  - cd `~/ICSVirtual/openplc`
  - `docker build -t open-plc .`
  
#### Use the OpenPLC image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/ICSNetwork`.
- Change the image of the `openplc` service by `sflorenz05/open-plc:v0.1`.

#### Follow this recommendation [Only for Modbus]

- Once OpenPLC container is running:
  
- Disable DNP3/EtherNET/IP to use only Modbus protocol:

![alt text](./images/openplc1.png "OpenPLC 1")

- Load the `*.st` file of the project.
  - E.g.: file `water_heater.st` is placed into `~/ICSVirtual/openplc/sample/`.
  
- Start PLC.

![alt text](./images/openplc2.png "OpenPLC 2")

</details>

### Getting Started Matlab

<details>

<summary>Open to see details</summary>

#### Create your own Matlab Simulink Docker image

- Run the MATLAB container using this command:
      `docker run -it -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r20XYz -vnc`

  - :r20XYz chooses the release version of the MATLAB container. E.g.: `r2022a`
  
  - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`.
  
  - Run Matlab with `root` permissions: `sudo matlab`.

  - Install *Industrial Control Communication Toolbox* as add-on:

      ![alt text](./images/ics_toolbox.png "ics1")

  - Install Matlab Simulink as add-on:

      ![alt text](./images/simulink1.png "Simulink 1")

      ![alt text](./images/simulink2.png "Simulink 1")

  - Install gcc, g++, foltran:
    - `sudo apt-get update`
    - `sudo apt-get install -y gcc g++ gfortran`
        
      ![alt text](./images/install_gcc.png "Install gcc 1")
  
  - [Save changes in container](https://www.mathworks.com/help/cloudcenter/ug/save-changes-in-containers.html)
    - `docker ps`
    - `docker commit <containerID> <repository>:<tag>`
      - E.g.: `docker commit 3d555451f07a mymatlab:r2020a`.

#### Use the matlab simulink image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/ICSNetwork`.
- Change the image of the `matlab` service by `sflorenz05/matlab_simulink:v0.3`.

#### Reference to the Modbus Module used

- [Creating Modbus Object](https://es.mathworks.com/help/icomm/ug/modbus.html).
- [Read Modbus Module](https://es.mathworks.com/help/icomm/ug/modbus.read.html).
- [Write Modbus Module](https://es.mathworks.com/help/icomm/ug/modbus.write.html).

#### Build final image

- It has been created a Dockerfile that ADD the source code into the container base image: `sflorenz05/matlab_simulink:v0.3`.
- In this way, the image `sflorenz05/matlab_simulink:v0.4` has been built.

#### Troubleshootings Matlab on Docker

- [Matlab from docker-compose #39](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/39).
- [Installing Simulink as a Docker Matlab add-on #40](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/40).

#### Import Project Files into the PATH before start simulation

![alt text](./images/simulink3.png "Simulink 3")

#### Compile all `*.c` using mex compiler of Matlab

- The `*.c` version of all of the following folders must be compiled using mex:
  
  ![alt text](./images/simulink4.png)

- All files has been compiled by default.
  - E.g.: If we go inside the `ASU Unit` folder (see the PATH in the following image) we only need to compile the `*.c`, using the command `mex ASU_UNIT.c`. **Important:** `*.mexa64` files are generated.
  
  ![alt text](./images/simulink5.png "Simulink 5")

#### Run Simulink Project

- Once all the code has been successfully compiled the Simulink Project is executed with double clic in the `*.slx`. E.g.: `Remedy_WWTP.slx`.
  
  ![alt text](./images/simulink6.png)

- The values displayed on the displays should be close to the values highlighted in the following figure.
  
  ![alt text](./images/simulink7.png)

</details>

### Getting started Scada-LTS

<details>

<summary>Open to see details</summary>

- Once Scada-LTS container is running:
  - Access to Scada-LTS GUI: [http://localhost:8080/Scada-LTS/](http://localhost:8080/Scada-LTS/).
  - Login with `username`: admin `password`: admin.
  - Create empty script in "Scripting".

      ![alt text](./images/scada1.png)

  - Next go to the "SQL" tab.
  - Paste content scripts-one-insert.txt file into the text field "SQL".
  
  - File `scripts-one-insert.txt` is placed into `~/ICSVirtual/scada-lts/scripts`.
  - Click "Submit update"
  - If the operation is successful, the information about adding 12 records will be displayed.

      ![alt text](./images/scada2.png)
  
  - Then import the project (.json file).
    - E.g.: file `Water Heater 3 Stations.json` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![alt text](./images/scada3.png)

  - Add a data source running on port 502 with host:openplc.
  - Make the connection with OpenPLC.

      ![alt text](./images/scada4.png)

  - Add the background image at "Graphical views".
    - E.g.: file `background.png` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![alt text](./images/scada5.png)
  - Change the name of the file named .env.example in /ICSVirtual/network/ICSNetwork :
  
    `cd ~/ICSVirtual/network/ICSNetwork`
    
    `mv .env.example .env`

#### Troubleshootings Scada-LTS

- [Graphical views Scada-LTS #1961](https://github.com/SCADA-LTS/Scada-LTS/issues/1961)

</details>

### Getting Started network ICSNetwork

<details>

<summary>Open to see details</summary>

- Add permissions
  - `cd ~/ICSVirtual/network/ICSNetwork`
  - `sudo chmod +x scripts/*.*`

</details>

### Getting Started Attacker

<details>

<summary>Open to see details</summary>

- **Attacker** is divided into: *Single Attacker* and *Modtester* tool.

#### Single Attacker

##### Create your own Attacker Docker image

- Go to attacker folder `cd ~/ICSVirtual/attacker`.
- Compile `injection_attack.cpp` file `g++ injection_attack.cpp -o injection_attack -pthread`.
- Build image: `docker build -t attacker .`.

##### Use the attacker image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/attacker`.
- Change the image of the `matlab` service by `sflorenz05/attacker:v0.1`.

##### Deploying Attacker

- Compile attacker code:
  - `cd ~/ICSVirtual/attacker`
  - `g++ injection_attack.cpp -o injection_attack -pthread`
- Add permissions:
  - `cd ~/ICSVirtual/network/attacker`
  - `sudo chmod +x scripts/*.*`
- Set enviromental variables:
  - Copy the `.env.example` and paste in the same path.
    - Rename `.env.example` to `.env`.
  - Inspect the PLC container: `docker inspect <containerid>` to recover IP address of this container.
    - Set the `IP_PLC` variable.
    - Set the `FREQ` variable.

#### ModTester

##### Create your own ModTester Docker image

- Go to modtester folder `cd ~/ICSVirtual/modtester`.
- Build image: `docker build -t modtester .`.

##### Use the modtester image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/modtester`.
- Change the image of the `matlab` service by `sflorenz05/modtester:v0.2`.

##### Deploying ModTester

- Add permissions:
  - `cd ~/ICSVirtual/network/modtester`
  - `sudo chmod +x scripts/*.*`

</details>

### Getting Started TCPDump

<details>

<summary>Open to see details</summary>

- To capture the traffic into the ICSNetwork the [TCPDump](https://www.tcpdump.org/) tool is used.
- To deploy as part of the Docker Infrastructure `kaazing/tcpdump` image is [used](https://hub.docker.com/r/kaazing/tcpdump).
- Once the `tcpdump` container is deployed an `*.pcap` file is included as part of the `tcpdump` folder.

  ![alt text](./images/tcpdump1.png)

- Once `*.pcap` file is downloaded, it can be opened using Wireshark.
  
  ![alt text](./images/tcpdump2.png)
  
</details>

## How to use the project

### Deploy ICSNetwork

- `cd ~/ICSVirtual/network/ICSNetwork`

- `make start`

- `make stop`

- `make destroy`

### Deploy tcpdump

- `cd ~/ICSVirtual/network/tcpdump`

- `make start`

- `make stop`

- `make destroy`

### Deploy Attacker

#### Single Attacker

- `cd ~/ICSVirtual/network/attacker`

- `make start`

- `make stop`

- `make destroy`

#### ModTester

- `cd ~/ICSVirtual/network/modtester`

- `make start`

- `docker exec -it <modtester-container-id> bash`
  - E.g.: `docker exec -it 91d48b6bdabd bash`
  
- Inside the container execute:
  
  - `python modTester.py`
  
  - `show modules` / `use module_name`
    - E.g.: `use modbus/dos/floodingAttack`

  - `show options` to see options to complete.
    - E.g.: `set RHOSTS ip`  -->  `set RHOSTS 172.18.0.2`
    - E.g.: `set sIP ip`  -->  `set sIP 172.18.0.3`
  
  - `exploit`

- `make stop`

- `make destroy`

## How to test connection

- `docker inspect <containerid>`
  
- `docker exec -it <containerid> bash`
  
### Install/use ping network tool

- `sudo apt-get update`

- `sudo apt-get install iputils-ping`
  
- e.g.: `ping 192.168.144.3`
