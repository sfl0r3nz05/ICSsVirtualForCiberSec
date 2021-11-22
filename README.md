# ICS Virtual

## How to deploy
- docker-compose up -d
- docker run -itd --rm --network=scada-lts_ics -e PASSWORD=ILoveMATLAB -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r2021b -vnc

## How to test connection
- docker inspect <containerid>
- docker exec -it <containerid> bash
  ### Install ping network tool
  - sudo apt-get update
  - sudo apt-get install iputils-ping
  - ping: `e.g.: ping 192.168.144.3`