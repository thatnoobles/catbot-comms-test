#include <inttypes.h>

// Represents a data packet that is sent from the Arduino to the Pi.
// See the README for an explanation of the packet format.
class Packet
{
	public:
	// Creates a new packet. Packet type and length have a maximum of 15.
	Packet(uint8_t packet_type, uint8_t packet_length);

	// Adds a single byte to the end of the packet.
	// Returns -1 if there is no space remaining for this byte; otherwise returns the byte's position in the packet.
	int add_byte(uint8_t byte);

	// Adds an array of bytes to the end of the packet.
	// Returns -1 if there is no space remaining for this byte; otherwise returns the last byte's position in the packet.
	int add_bytes(uint8_t *bytes, int array_length);

	// Sends packet to the master device.
	// Returns the full packet as a byte array.
	void send();

	private:
	uint8_t type;
	uint8_t length;

	uint8_t *data;
	int current_position;
};