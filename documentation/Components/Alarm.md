# PLC Register Modification Alarm

- This alarm consists of a Python script that notices the system when the PLC values are outside a predefined range of "normal" values. The script must be applied on every register you want to be warned of.
- The script is based on the one presented in [PLC memory attack detection and response in a clean water supply system](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/documentation/StateOfArt/Papers/1-s2.0-S1874548218301641-main.pdf).

![image](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/assets/105321735/c25c6160-6c89-464e-8458-704a8a9ff7a0)

- Sourcecode of the script can be found in [/alarm/alarm.py](https://github.com/sfl0r3nz05/ICSsVirtualForCiberSec/blob/documented/alarm/alarm.py).
