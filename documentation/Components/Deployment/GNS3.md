# GNS3 Deployment

- Once GNS3 server is installed and running (as explained in [GNS3 Server Installation](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/Requirements/gns3.md)), it's time to import and deploy the containers of the project.

## Project Importation

1. Download the GNS3 project named `ICSVirtual.gns3project` from [/network/GNS3Deployment](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/tree/main/network/GNS3Deployment)
2. In GNS3 Desktop, go to `File -> Import portable project` and select the previously downloaded project.

![image](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/assets/105321735/03bd0c86-d499-41fe-913a-5f27d56648ca)

- All the container images and project appliances(the network layout) should be imported. Your project should look something like this:

![image](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/assets/105321735/d1db1367-ee75-45c9-b388-5986bb5029e0)

- To run all the containers at once you can press the big green Start button at the top. If you want to run any of the containers separately, you can run them manually by right-clicking on them and pressing `Start`.
- You can configure any container settings, such as start commands or environment variables, by right-clicking on a container and selecting `Configure`.
- Network settings of each container can be edited by right-clicking and selecting `Edit Config`

## Service Setup

- Once all the services' containers are up and running, we must configure each of the services to work properly.

### 1. OpenPLC

- First of all, we must access the OpenPLC web interface. To do so, right-click the OpenPLC interface and select `Console`. You should be redirected to the OpenPLC webserver login page on your browser. The default credentails are `user: openplc` `password: openplc`.

![image](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/assets/105321735/fdda264b-29f2-434e-88b1-e8556f305361)


- Once logged in OpenPLC, select `Programs` on the left sidebar and `Upload Program`. You can find the program used in the project at [/openplc/watertreatment.st](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/openplc/watertreatment.st).
- Once the program is compiled, go to `Hardware` and select `Simulink`. This is very important, as otherwise the SimLink interface won't be able to communicate with OpenPLC.

![image](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/assets/105321735/06f26abc-793d-46c5-850b-97075bf547ee)

- Now you can press `Start PLC` on the left sidebar to start the PLC program that has just been loaded. Go to `Monitoring` to see the values of the variables defined in the program.

### 2. Simulink

- In GNS3, open the Simulink container's console. You should be redirected to a VNC session in your browser.
- Click `Connect` and start Matlab by double-clicking on the desktop icon. You must log in with your Mathworks account.
- Once Matlab is running, right-click on the `simulink` folder at the left sidebar and select `Add folders and subfolders to path`.
- Now double-click the file named `implementacion_simplified_2022a.slx` inside the simulink folder at the left sidebar. This will open the project Simulink model.
- Finally, run the Simulink model by clicking the green play button at the top of the screen.
- If you go back to the OpenPLC webserver, you should see that the variable values have changed and they now have the values of the Simulink model. This means that the communication between the model and OpenPLC is working correctly.

### 3. ScadaLTS

- Once OpenPLC is reading the model's values correctly, we can configure ScadaLTS.
- To access ScadaLTS, open the container's terminal in GNS. You should be redirected to a ScadaLTS login page in your browser. The default credentials are `user:admin` `password:admin`.
- To configure the datapoints and graphics view in ScadaLTS, you can follow the steps explained in the [home scenario](https://github.com/SCADA-LTS/Scada-LTS/tree/examples/doc/examples/home) of the ScadaLTS Wiki. Be sure to select Modbus TCP/IP as the protocol.

### 4. Attacker

- To use the [ModTester](https://github.com/sfl0r3nz05/ModTester/tree/86f601464e3e40c5fd284bc61abe8d270ecb3308) tool to perform attacks on the network, open the kali linux attacker's console from GNS3. Clone the ModTester repository if it is not done already.

## Demonstration Video

[This video](https://www.youtube.com/watch?v=W10l6Pk4seo) in which a demonstration of the project is performed may be helpful to see a full deployment of the project and solve any doubts you may have.

