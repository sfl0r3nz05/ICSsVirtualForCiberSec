from pymodbus.client import ModbusTcpClient
from pymodbus.exceptions import ConnectionException
import time

# Modbus TCP connection settings
HOST = '127.0.0.1'  # Replace with the IP address of your Modbus device
PORT = 502          # Replace with the Modbus TCP port of your device

# Register addresses to read
REGISTER_ADDRESSES = [0, 1, 2]  # Replace with the addresses of the registers you want to read

# Lower and upper limits for each register
LIMITS = {
    0 : {'lower': 50, 'upper': 175},
    1 : {'lower': 15000, 'upper': 75000},
    2 : {'lower': 600, 'upper': 1200}
}


# Connect to the Modbus device
client = ModbusTcpClient(HOST, port=PORT)

while True:
    try:
        # Read the register values
        response = client.read_holding_registers(REGISTER_ADDRESSES[0], len(REGISTER_ADDRESSES), unit=1)
        if response.isError():
            print("Failed to read the registers:", response)
        else:
            values = response.registers
            print("Current values:", values)

            # Check each register value against its limits
            for i, value in enumerate(values):
                register_address = REGISTER_ADDRESSES[i]
                limits = LIMITS[register_address]

                # Check if the value is outside the acceptable range
                if value < limits['lower'] or value > limits['upper']:
                    print("Value of register {} outside acceptable range!Alarm triggered!".format(register_address))


    except ConnectionException as e:
        print("Connection error:", e)

    # Wait for some time before reading the registers again
    # Adjust the interval based on your requirements
    time.sleep(1)

# Close the Modbus connection
client.close()
