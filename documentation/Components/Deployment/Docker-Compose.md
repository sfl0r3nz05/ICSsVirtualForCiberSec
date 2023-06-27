# Build and Set-Up the network to be deployed

## For deployment based on `docker compose`

### Deploy the ICS Network

- Add permissions
  - `cd ~/ICSVirtual/network/ICSNetwork`
  - `sudo chmod +x scripts/*.*`

- Deploy ICSNetwork

  - `cd ~/ICSVirtual/network/ICSNetwork`

  - `make start`

  - `make stop`

  - `make destroy`

### Deploy Attacker

- Single Attacker

  - `cd ~/ICSVirtual/network/attacker`

  - `make start`

  - `make stop`

  - `make destroy`

- ModTester

  - `cd ~/ICSVirtual/network/modtester`

  - `make start`

  - `docker exec -it <modtester-container-id> bash`
    - E.g.: `docker exec -it 91d48b6bdabd bash`
  
  - Inside the container execute:
  
    - `python modTester.py`
  
    - `show modules` / `use module_name`
      - E.g.: `use modbus/dos/floodingAttack`

    - `show options` to see options to complete.
      - E.g.: `set RHOSTS ip`  -->  `set RHOSTS 172.18.0.2`
      - E.g.: `set sIP ip`  -->  `set sIP 172.18.0.3`
  
    - `exploit`

  - `make stop`

  - `make destroy`

### Collect Network Traffic using TCPDump Tool

- To capture the traffic into the ICSNetwork the [TCPDump](https://www.tcpdump.org/) tool is used.
- To deploy as part of the Docker Infrastructure `kaazing/tcpdump` image is [used](https://hub.docker.com/r/kaazing/tcpdump).
- Once the `tcpdump` container is deployed an `*.pcap` file is included as part of the `tcpdump` folder.

  ![tcpdump1](https://user-images.githubusercontent.com/6643905/213816622-83873059-d039-4d0b-a226-e9593bc82cdf.png)

- Once `*.pcap` file is downloaded, it can be opened using Wireshark.
  
  ![tcpdump2](https://user-images.githubusercontent.com/6643905/213816617-e5c4e39c-1cc9-45e2-b303-fa1724036658.png)

  - How to Deploy tcpdump

    - `cd ~/ICSVirtual/network/tcpdump`

    - `make start`

    - `make stop`

    - `make destroy`

