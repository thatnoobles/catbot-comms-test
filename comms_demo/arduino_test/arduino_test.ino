#include <Wire.h>  // https://reference.arduino.cc/reference/en/language/functions/communication/wire/
#include "src/packet.h"  // custom libraries have to be in a folder called "src" because Arduino IDE is stupid

#define I2C_ADDR (0x0a)  // I2C address we're assigning to this device

uint8_t request_type = 0;

//////////////////////////////////////////
//// TEST DATA (Feel free to change!) ////
//////////////////////////////////////////

// Potentiometer readings (degrees from one rotation bound) : 8 potentiometers; 2 per leg
uint8_t pot_readings[8] =
{ 
    12, 34,
    0, 5, 
    10, 11, 
    20, 23 
};

// Limit switch pressed states (0 is not pressed, 1 is pressed) : 16 limit switches; 2 per potentiometer
uint8_t switch_readings[16] =
{
    0, 0, 0, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0, 
    0, 0, 0, 0 
};

// Pressure sensor reading (psi)
uint8_t pressure_reading = 79;

//////////////////////////////////////////
//////////////////////////////////////////

void setup()
{
  Serial.begin(9600);

  Wire.begin(I2C_ADDR);

  Wire.onReceive(receiveData);  // Call receiveData() when we receive data from the Pi
  Wire.onRequest(handleRequest);  // Call handleRequest() when the Pi tries to read data from this device
}

void receiveData()
{
  // When Pi tries to request data, it'll send a byte representing the request type
  request_type = Wire.read();
}

void handleRequest()
{
  uint8_t packet_data_length = 0;

  if (request_type == 0x01)
  {
    packet_data_length = 10;
    Serial.println("Handling request type 1 : potentiometer, limit switches, pressure");
  }
  else
  {
    Serial.print("Unknown request type : ");
    Serial.println(request_type);
    return;
  }

  // Create a new packet to send to the RPi.
  // This is pretty much just an abstraction of Wire.write
  Packet *packet = new Packet(request_type, 10);

  // Add potentiometer readings
  packet->add_bytes(pot_readings, 8);

  // We can put limit switch data into one byte by writing 0 if none are on, and the switch's number if one is on
  uint8_t switch_status = 0x00;

  for (int i = 0; i < 16; i++)
    if (switch_readings[i])
      switch_status = i + 1;

  packet->add_byte(switch_status);

  // Add pressure reading
  packet->add_byte(pressure_reading);

  // Send the packet to the Pi
  packet->send();
}

void loop()
{
  // loop() doesn't really need to do anything
  delay(100);
}