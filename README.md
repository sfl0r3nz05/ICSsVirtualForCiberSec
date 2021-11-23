# ICS Virtual

## How to deploy
- `docker-compose up -d`
  
  ### Getting Started Matlab
    - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`
    - Enable permissions to Matlab folder `sudo chmod 777 -R /opt/matlab/R2021b`
    - Update the system: `sudo apt-get update`
    - Install neccesary libraries: e.g.: `sudo apt-get install -y gcc g++ gfortran`
    - asdas
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink3.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink4.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink5.png">
    - Install Matlab Simulink:
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink1.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/blob/main/images/simulink2.png">
  
## How to test connection
- `docker inspect <containerid>`
- `docker exec -it <containerid> bash`
  
  ### Install ping network tool
    - `sudo apt-get update`
    - `sudo apt-get install iputils-ping`
    - ping: `e.g.: ping 192.168.144.3`