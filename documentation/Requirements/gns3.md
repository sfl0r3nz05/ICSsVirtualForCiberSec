# Deployment of GNS3 server on EC2 instance

- [Deployment of GNS3 server on EC2 instance](#deployment-of-gns3-server-on-ec2-instance)
  - [Deploy GNS3 Server](#deploy-gns3-server)
  - [Connect to GNS3 Server from GNS3 client](#connect-to-gns3-server-from-gns3-client)
  - [How to bypass a network of restrictions by tunneling](#how-to-bypass-a-network-of-restrictions-by-tunneling)
  - [To Do](#to-do)

The purpose of this repository is to deploy a GNS3 server on an EC2 instance of AWS. The following figure shows the basic architecture of the deployment to be implemented:

![image](https://user-images.githubusercontent.com/69375071/210196949-15232346-a583-4ab8-a562-4d7811d152be.png)

## Deploy GNS3 Server

To perform the right deployment follow each of the following steps:

1. We assume that we have an EC2 instance deployed with Ubuntu Server 20.04 as OS:

    ![image](https://user-images.githubusercontent.com/69375071/210196969-a4053982-94d3-4669-beae-49b45a0f73e5.png)

2. The following rules apply for opening incoming connections from:

    | Type        | Port      | Description                                                     |
    |-------------|-----------|-----------------------------------------------------------------|
    | SSH         | 22        | Instance management                                             |
    | Custom TCP  | 3080      | GNS3 client-server connection                                   |
    | Custom TCP  | 5000-5030 | Telnet connection for the device management created within GNS3 |

    - Example of applied rules

    ![image](https://user-images.githubusercontent.com/69375071/210196983-7269b43f-6c0d-40cb-b9bd-cafd5c187720.png)

3. GNS3 server installation:

    ```console
    sudo apt update
    sudo add-apt-repository ppa:gns3/ppa
    sudo apt install gns3-server
    ```

    - It is recommended accept both options as part of the installation process:

    | Users able to run GNS3| Users able to capture packages |
    |-------------|-----------|
    | ![image](https://user-images.githubusercontent.com/69375071/210197009-f2be56b9-9040-4600-87fb-83d1a92e90df.png) | ![image](https://user-images.githubusercontent.com/69375071/210197024-ff5d286f-4ba1-4772-a1c8-7a4051f21a93.png) |

     > **Note:** To install specific versions use for instance: `sudo pip3 install gns3-server==2.2.34`

4. IOU (IOS over Unix) is an internal Cisco tool for simulating the ASICs in Cisco Switches. This enables you to play with Layer 2 switching in the Labs:

    ```console
    sudo dpkg --add-architecture i386
    sudo apt update
    sudo apt install gns3-iou
    ```

5. [Install Docker CE on Ubuntu 22.04|20.04|18.04](https://docs.docker.com/engine/install/ubuntu/).

    - Verify installation by checking Docker version:

        ```console
        docker version
        ```

    - After installing Docker and IOU, add your user to the following groups:

        ```console
        for i in ubridge libvirt kvm docker; do
            sudo usermod -aG $i $USER
        done
        ```

6. Run GNS3 server:

    ```console
    gns3server -q --daemon
    ```

    >Note: `-q` for no console logging, `--daemon` runs gns3server as a daemon service that keeps running when the console exits

   - It is now possible to access the GNS3 service:

    ```console
    http://aws_instance_ip:3080
    ```

   - Verify the service:

![image](https://user-images.githubusercontent.com/69375071/210197180-6d23f0f8-dc3b-4803-b45c-cdf1a0ed3da1.png)

## Connect to GNS3 Server from GNS3 client

1. Now, it is time to connect to the server via the GNS3 client and configure the preferences properly.

    ![image](https://user-images.githubusercontent.com/69375071/210197203-ee05d661-6bae-4cb8-8257-27ff49a66f67.png)

   - Default username/password:

    ```console
    username: gns3
    password: gns3
    ```

2. Verify that the server has connected properly.

    ![image](https://user-images.githubusercontent.com/69375071/210197229-e9904096-9f2e-4f78-80b2-72a93303947a.png)

## How to bypass a network of restrictions by tunneling

If we are under a restrictive network with firewalls blocking the network, the following tunneling is proposed to bypass it.

```console
ssh -N -i key.pem -L localhost:3080:private_ip_ec2:3080 username_ec2@public_ip_ec2
```

For instance:

```console
ssh -N -i .\openstack.pem -L localhost:3080:172.31.88.200:3080 ubuntu@54.89.220.232
```

>**Note:** *For this mechanism to work, at least the access through port 22 must be open.*

- The following figure shows how the client must be configured so that the traffic is redirected through the tunnel:

![image](https://user-images.githubusercontent.com/69375071/210197244-b8121b0f-9b41-4e6b-9eb1-fa5647685811.png)

## To Do

1. Enable secure connection between the client and server via TLS
2. Document how to apply rules on aws to open port
3. Document how to add a new router using binary files
