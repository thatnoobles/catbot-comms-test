from smbus2 import SMBus
import threading
import time

I2C_ADDR = 0xa
latest_value = []

def request_loop():
    while True:
        input("Press enter to get latest value")
        print(latest_value)


other_thread = threading.Thread(target=request_loop, args=())
other_thread.start()

while True:
    with SMBus(1) as bus:
        latest_value = bus.read_i2c_block_data(I2C_ADDR, 0x2, 1)  
        time.sleep(0.025)