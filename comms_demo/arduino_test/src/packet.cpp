#include <Wire.h>
#include "packet.h"

Packet::Packet(uint8_t packet_type, uint8_t packet_length)
{
	type = packet_type;
	length = packet_length;

	data = new uint8_t[length];
	current_position = 0;
}

int Packet::add_byte(uint8_t byte)
{
	// If we are out of space in the packet, don't try to write to it.
	if (current_position == length) return -1;

	data[current_position] = byte;
	return current_position++;
}

int Packet::add_bytes(uint8_t *bytes, int array_length)
{
	// Write bytes to packet either until we run out of space, or until all bytes have been written.
	for (int i = 0; i < array_length; i++)
	{
		if (current_position == length) return -1;

		data[current_position] = bytes[i];
		current_position++;
	}

	// We want the position the last byte was written to, but current_position is currently at the next position - so subtract 1.
	return current_position - 1;
}

void Packet::send()
{
	// Write metadata to first byte, and write the rest after.
	uint8_t full_packet[length + 1];
	
	full_packet[0] = (type << 4) + length;  // first 4 bits are type, last 4 bits are length

	for (int i = 0; i < length; i++)
		full_packet[i + 1] = data[i];

	Wire.write(full_packet, length + 1);
}