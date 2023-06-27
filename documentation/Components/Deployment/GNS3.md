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

## Demonstration Video

[This video](https://www.youtube.com/watch?v=W10l6Pk4seo) in which a demonstration of the project is performed may be helpful to see a full deployment of the project and solve any doubts you may have.

