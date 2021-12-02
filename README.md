# ICS Virtual

## Description
This project arises as [@jmuguruza](https://github.com/jmuguruza) final degree project and aims to perform security tests on a water treatment plant. For this purpose, the project integrates 3 basic elements: [OpenPLC](https://github.com/thiagoralves/OpenPLC_v3), [Scada-LTS](https://github.com/SCADA-LTS/Scada-LTS) and [Matlab on Docker](https://github.com/mathworks-ref-arch/matlab-dockerfile).

**Project Status:** `in progress`

## Requirements
1. Install [docker for ubuntu](https://docs.docker.com/engine/install/ubuntu/)
2. [Manage Docker as non-root user](https://docs.docker.com/engine/install/linux-postinstall/)
3. Install [docker-compose for ubuntu](https://docs.docker.com/compose/install/)
4. Install make `sudo apt install make`

## Getting Started
  ### Getting Started OpenPLC
  #### Create your own OpenPLC image  
  - Build openplc image: 
      * cd `~/ICSVirtual/openplc`
      * `docker build -t open-plc .`
  
  #### Use the OpenPLC image create for the project
  - Open docker-compose file `cd ~/ICSVirtual/network/`
  - Change the image of the `openplc` service by `sflorenz05/open-plc:v0.1`

  #### Follow this recommendation [Only for Modbus]
  - Once OpenPLC container is running:
  - Disable DNP3/EtherNET/IP to use only Modbus protocol:
    <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc1.png">
    
  - Load the `*.st` file of the project.
  - Start PLC.
    <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc2.png">  

  ### Getting Started Matlab
  #### Create your own Matlab Simulink image
  - Run the MATLAB container using this command:
      `docker run -it -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r20XYz -vnc`
      
      * :r20XYz chooses the release version of the MATLAB container.
  
    - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`
  
    - Run Matlab with `root` permissions: `sudo matlab`

    - Install Matlab Simulink as add-on:
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink1.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink2.png">

    - [Save changes in container](https://www.mathworks.com/help/cloudcenter/ug/save-changes-in-containers.html)
        - `docker ps`
        - `docker commit <containerID> <repository>:<tag>`
          - E.g.: `docker commit 3d555451f07a mymatlab:r2020a`

  #### Use the matlab simulink image create for the project
  - Open docker-compose file `cd ~/ICSVirtual/network/`
  - Change the image of the `matlab` service by `sflorenz05/matlab_simulink:v0.1`
  
  #### Troubleshootings
  - [Matlab from docker-compose #39](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/39)
  - [Installing Simulink as a Docker Matlab add-on #40](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/40)

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

    #### Troubleshootings
    - [Graphical views Scada-LTS #1961](https://github.com/SCADA-LTS/Scada-LTS/issues/1961)

## How to use
- `cd ~/ICSVirtual/network`
- `docker-compose up -d`
- `docker-compose down`

## How to test connection
- `docker inspect <containerid>`
- `docker exec -it <containerid> bash`
  
  ### Install/use ping network tool
    - `sudo apt-get update`
    - `sudo apt-get install iputils-ping`
    - ping: `e.g.: ping 192.168.144.3`