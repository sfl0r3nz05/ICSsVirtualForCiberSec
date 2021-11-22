# ICS Virtual

## How to deploy
- docker-compose up -d
- create a volume e.g., `docker volume create remedy`
- create a link virtual between remedy folder and volume folder e.g.: `sudo ln -s remedy /var/lib/docker/volumes/remedy/_data`
- docker run -itd --rm --network=scada-lts_ics -v remedy:/home/matlab/Documents/MATLAB/remedy -e PASSWORD=ILoveMATLAB -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r2021b -vnc
  ### Getting Started Matlab
    - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`
    - Enable permissions to Matlab folder `sudo chmod 777 -R /opt/matlab/R2021b`
    - Update the system: `sudo apt-get update`
    - Install neccesary libraries: e.g.: `sudo apt-get install -y gcc g++ gfortran`
    - Install Matlab Simulink:
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/images/simulink1.png">
      <img src="https://github.com/sfl0r3nz05/ICSVirtual/images/simulink2.png">
  

## How to test connection
- docker inspect <containerid>
- docker exec -it <containerid> bash
  ### Install ping network tool
    - sudo apt-get update
    - sudo apt-get install iputils-ping
    - ping: `e.g.: ping 192.168.144.3`