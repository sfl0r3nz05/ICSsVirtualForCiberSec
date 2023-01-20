### Getting Started Matlab

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