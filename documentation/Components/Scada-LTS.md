# Build and Set-Up Scada-LTS

- Once Scada-LTS container is running:
  - Access to Scada-LTS GUI: [http://localhost:8080/Scada-LTS/](http://localhost:8080/Scada-LTS/).
  - Login with `username`: admin `password`: admin.
  - Create empty script in "Scripting".

      ![alt text](./images/scada1.png)

  - Next go to the "SQL" tab.
  - Paste content scripts-one-insert.txt file into the text field "SQL".
  
  - File `scripts-one-insert.txt` is placed into `~/ICSVirtual/scada-lts/scripts`.
  - Click "Submit update"
  - If the operation is successful, the information about adding 12 records will be displayed.

      ![alt text](./images/scada2.png)
  
  - Then import the project (.json file).
    - E.g.: file `Water Heater 3 Stations.json` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![alt text](./images/scada3.png)

  - Add a data source running on port 502 with host:openplc.
  - Make the connection with OpenPLC.

      ![alt text](./images/scada4.png)

  - Add the background image at "Graphical views".
    - E.g.: file `background.png` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![alt text](./images/scada5.png)
  - Change the name of the file named .env.example in /ICSVirtual/network/ICSNetwork :
  
    `cd ~/ICSVirtual/network/ICSNetwork`

    `mv .env.example .env`

#### Troubleshootings Scada-LTS

- [Graphical views Scada-LTS #1961](https://github.com/SCADA-LTS/Scada-LTS/issues/1961)
