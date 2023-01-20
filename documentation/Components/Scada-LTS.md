# Build and Set-Up Scada-LTS

- Once Scada-LTS container is running:
  - Access to Scada-LTS GUI: [http://localhost:8080/ScadaBR/](http://localhost:8080/Scada-LTS/).
  - Login with `username`: admin `password`: admin.
  - Create empty script in "Scripting".

      ![scada1](https://user-images.githubusercontent.com/6643905/213805504-f13c140d-5d9c-4ff8-90a4-494c00893c47.png)

  - Next go to the "SQL" tab.
  - Paste content scripts-one-insert.txt file into the text field "SQL".
  
  - File `scripts-one-insert.txt` is placed into `~/ICSVirtual/scada-lts/scripts`.
  - Click "Submit update"
  - If the operation is successful, the information about adding 12 records will be displayed.

      ![scada2](https://user-images.githubusercontent.com/6643905/213805526-3ab62586-805e-4fc1-9905-021bc9290cbd.png)
  
  - Then import the project (.json file).
    - E.g.: file `Water Heater 3 Stations.json` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![scada3](https://user-images.githubusercontent.com/6643905/213805636-c5e90c53-c72b-4104-a3b9-15c76074a79d.png)

  - Add a data source running on port 502 with host:openplc.
  - Make the connection with OpenPLC.

        ![scada4](https://user-images.githubusercontent.com/6643905/213805643-020e7678-3582-438b-8772-267038a42282.png)

  - Add the background image at "Graphical views".
    - E.g.: file `background.png` is placed into `~/ICSVirtual/scada-lts/sample/`

        ![scada5](https://user-images.githubusercontent.com/6643905/213805647-30d870e5-e390-45d5-9ba1-b9dfe0c4f8ad.png)

  - Change the name of the file named .env.example in /ICSVirtual/network/ICSNetwork :
  
    `cd ~/ICSVirtual/network/ICSNetwork`

    `mv .env.example .env`

## Troubleshootings Scada-LTS

- [Graphical views Scada-LTS #1961](https://github.com/SCADA-LTS/Scada-LTS/issues/1961)
