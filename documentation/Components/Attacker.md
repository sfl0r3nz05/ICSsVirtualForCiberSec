# Build and Set-Up Attacker container

- **Attacker** is divided into: *Single Attacker* and *Modtester* tool.

## Single Attacker

### Create your own Attacker Docker image

- Go to attacker folder `cd ~/ICSVirtual/attacker`.
- Compile `injection_attack.cpp` file `g++ injection_attack.cpp -o injection_attack -pthread`.
- Build image: `docker build -t attacker .`.

### Use the attacker image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/attacker`.
- Change the image of the `matlab` service by `sflorenz05/attacker:v0.1`.

### Deploying Attacker

- Compile attacker code:
  - `cd ~/ICSVirtual/attacker`
  - `g++ injection_attack.cpp -o injection_attack -pthread`
- Add permissions:
  - `cd ~/ICSVirtual/network/attacker`
  - `sudo chmod +x scripts/*.*`
- Set enviromental variables:
  - Copy the `.env.example` and paste in the same path.
    - Rename `.env.example` to `.env`.
  - Inspect the PLC container: `docker inspect <containerid>` to recover IP address of this container.
    - Set the `IP_PLC` variable.
    - Set the `FREQ` variable.

## ModTester

### Create your own ModTester Docker image

- Go to modtester folder `cd ~/ICSVirtual/modtester`.
- Build image: `docker build -t modtester .`.

### Use the ModTester image created for the project

- Open docker-compose file `cd ~/ICSVirtual/network/modtester`.
- Change the image of the `matlab` service by `sflorenz05/modtester:v0.2`.

### Deploying ModTester

- Add permissions:
  - `cd ~/ICSVirtual/network/modtester`
  - `sudo chmod +x scripts/*.*`
