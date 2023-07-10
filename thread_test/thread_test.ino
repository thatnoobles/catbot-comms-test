#include <Wire.h>

#define I2C_ADDR (0x0a)

int counter = 0;

void setup()
{
  Wire.begin(I2C_ADDR);
  Wire.onRequest(handleRequest);
}

void handleRequest()
{
  Wire.write(counter);
}

void loop()
{
  counter++; 
  delay(100);
}
