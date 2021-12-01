# ICS Virtual

## Requirements
1. Install [docker for ubuntu](https://docs.docker.com/engine/install/ubuntu/)
2. [Manage Docker as non-root user](https://docs.docker.com/engine/install/linux-postinstall/)
3. Install [docker-compose for ubuntu](https://docs.docker.com/compose/install/)
4. Install make `sudo apt install make`

## Getting Started

  ### Getting Started OpenPLC
  1. Build openplc image: 
      * cd `~/ICSVirtual/openplc`
      * `docker build -t open-plc .`
  2. Once OpenPLC container is running:
    - Disable DNP3/EtherNET/IP:
    <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc1.png">
    
    - Load the *.st file and start PLC:
    <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/openplc2.png">
  
  ### Getting Started Matlab
  - Run the MATLAB container using this command:
      `docker run -it -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r20XYz -vnc`
      
      * :r20XYz chooses the release version of the MATLAB container.
  
    - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`
  
    - Enable permissions to Matlab folder `sudo matlab`

    - Enable permissions to Matlab folder `sudo chmod +x /opt/matlab/R2021b`
  
    - Update the system: `sudo apt-get update`
  
    - Install neccesary libraries: e.g.: `sudo apt-get install -y gcc g++ gfortran`
  
    - Import the files into the PATH:
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink3.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink4.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink5.png">

    - Install Matlab Simulink:
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink1.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink2.png">

    - [Save changes in container](https://www.mathworks.com/help/cloudcenter/ug/save-changes-in-containers.html)
        - `docker ps`
        - `docker commit <containerID> <repository>:<tag>`
          - E.g.: `docker commit 3d555451f07a mymatlab:r2020a`

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