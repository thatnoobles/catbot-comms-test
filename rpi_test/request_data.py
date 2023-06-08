from smbus2 import SMBus
MAX_PACKET_LENGTH = 16  # including header byte

def request(bus: SMBus, addr: int, req_type: int) -> list[int]:
	packet = []

	while True:

		try:
			# Request data from the Arduino while also sending a byte representing the request type
			packet = bus.read_i2c_block_data(addr, req_type, MAX_PACKET_LENGTH)

		except Exception as e:
			print("Read error: " + str(e))
			continue

		break

	# Trim down list, since our packet might be shorter than the maximum packet length
	packet_length = (packet[0] & 0x0f) + 1 # 4 least significant bits of the header byte are the data length, then add 1 for the header byte

	packet = packet[0:packet_length]
	return packet