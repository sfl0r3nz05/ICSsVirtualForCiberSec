# Build and Set-Up WWTP container based on Matlab

## Create your own Matlab Simulink Docker image

- Run the MATLAB container using this command:
      `docker run -it -p 5901:5901 -p 6080:6080 --shm-size=512M mathworks/matlab:r20XYz -vnc`

  - :r20XYz chooses the release version of the MATLAB container. E.g.: `r2022a`
  
  - Open a bash for the Matlab container: e.g.: `docker exec -it <containerID> bash`.
  
  - Run Matlab with `root` permissions: `sudo matlab`.

  - Install *Industrial Control Communication Toolbox* as add-on:

      ![ics_toolbox](https://user-images.githubusercontent.com/6643905/213808166-d31a740b-544d-47c8-b68f-2e249a3a91e3.png)

  - Install Matlab Simulink as add-on:

      ![simulink1](https://user-images.githubusercontent.com/6643905/213808639-1d368a9f-f751-4ea5-99ad-421876de13a4.png)

      ![simulink2](https://user-images.githubusercontent.com/6643905/213808648-96cb07e3-7f74-4a96-88a5-115b315d28ce.png)

  - Install gcc, g++, foltran:
    - `sudo apt-get update`
    - `sudo apt-get install -y gcc g++ gfortran`

       ![install_gcc](https://user-images.githubusercontent.com/6643905/213813435-2955d1c0-61be-4085-8e2c-e155605f100a.png)
  
  - [Save changes in container](https://www.mathworks.com/help/cloudcenter/ug/save-changes-in-containers.html)
    - `docker ps`
    - `docker commit <containerID> <repository>:<tag>`
      - E.g.: `docker commit 3d555451f07a mymatlab:r2020a`.

## Use the matlab simulink image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/ICSNetwork`.
- Change the image of the `matlab` service by `sflorenz05/matlab_simulink:v0.3`.

## Reference to the Modbus Module used

- [Creating Modbus Object](https://es.mathworks.com/help/icomm/ug/modbus.html).
- [Read Modbus Module](https://es.mathworks.com/help/icomm/ug/modbus.read.html).
- [Write Modbus Module](https://es.mathworks.com/help/icomm/ug/modbus.write.html).

## Build final image

- It has been created a Dockerfile that ADD the source code into the container base image: `sflorenz05/matlab_simulink:v0.3`.
- In this way, the image `sflorenz05/matlab_simulink:v0.4` has been built.

## Troubleshootings Matlab on Docker

- [Matlab from docker-compose #39](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/39).
- [Installing Simulink as a Docker Matlab add-on #40](https://github.com/mathworks-ref-arch/matlab-dockerfile/issues/40).

## Import Project Files into the PATH before start simulation

![simulink3](https://user-images.githubusercontent.com/6643905/213808658-cae49c4f-6987-4971-a4f8-fc4efa0d9797.png)

## Compile all `*.c` using mex compiler of Matlab

- The `*.c` version of all of the following folders must be compiled using mex:
  
  ![simulink4](https://user-images.githubusercontent.com/6643905/213808664-e2214eee-8639-41eb-9108-c6e18a977ebd.png)

- All files has been compiled by default.
  - E.g.: If we go inside the `ASU Unit` folder (see the PATH in the following image) we only need to compile the `*.c`, using the command `mex ASU_UNIT.c`. **Important:** `*.mexa64` files are generated.
  
  ![simulink5](https://user-images.githubusercontent.com/6643905/213808702-ebd91fc5-1a19-4d05-a472-8b9b435fd0a1.png)

## Run Simulink Project

- Once all the code has been successfully compiled the Simulink Project is executed with double clic in the `*.slx`. E.g.: `Remedy_WWTP.slx`.
  
  ![simulink6](https://user-images.githubusercontent.com/6643905/213813772-152b54db-29ab-4261-b2d0-caa857683950.png)

- The values displayed on the displays should be close to the values highlighted in the following figure.
  
  ![simulink7](https://user-images.githubusercontent.com/6643905/213813780-ab571819-1dcb-45b1-8e79-5bfa216d5ea4.png)
