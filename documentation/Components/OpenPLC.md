# Build and Set-Up OpenPLC

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