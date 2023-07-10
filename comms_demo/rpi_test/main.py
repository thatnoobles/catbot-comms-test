from smbus2 import SMBus  # module for I2C comms
import request_data

I2C_ADDR = 0xa  # bus address
bus = SMBus(1)  # indicates /dev/ic2-1

data = request_data.request(bus, I2C_ADDR, 0x01)  # 0x01 in this case represents a request for pot/limit switch/pressure readings

# Print potentiometer data
for i in range(1, 9):  # skip over first byte (header) and get potentiometer readings (next 8 bytes)
    print("Potentiometer #" + str(i) + ":\t" + str(data[i]) + " deg")

# Print limit switch data
limit_switch_status = data[9]
print("Limit switch status:\t", end="")

if limit_switch_status == 0:
    print("Not active")
else:
    print("#" + str(limit_switch_status) + " active")

# Print pressure data
print("Pressure:\t\t" + str(data[10]) + " psi")