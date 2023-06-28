# Simulink-OpenPLC Interface
- To communicate the WWTP Simulink model with OpenPLC, the [SimLink Interface](https://github.com/thiagoralves/OpenPLC_Simulink-Interface) is used.
- This interface is developed by [thiagoralves](https://github.com/thiagoralves), the creator and main supporter of OpenPLC.

## Build SimLink Docker Image

- Copy the files in [wwtp/interface_simLink](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/tree/documented/wwtp/interface_simLink). Remember that for GNS3 deployment files must be copied to the system where the GNS3 server is running.
- Build the docker image. You can replace SimLink-interface to whichever name you like.
```shell
docker build -t SimLink-interface .
```
