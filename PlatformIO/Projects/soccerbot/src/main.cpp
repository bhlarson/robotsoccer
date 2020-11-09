#include <Arduino.h>
#include <MeShield.h>

MeRGBLed led1(PORT_3, SLOT1, 15);   /* parameter description: port, slot, led number */
MeRGBLed led2(PORT_3, SLOT2, 15);

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

int16_t bri = 0, st = 0;
uint8_t device = 0;
int8_t motorSpeed = 0;
int loopcount = 0;
const byte numChars = 32;
char receivedChars[numChars]; // an array to store the received data

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  led1.setColor(1, 255, 0, 0); // parameter description: led number, red, green, blue
  led1.setColor(2, 0, 255, 0); // parameter description: led number, red, green, blue
  led1.show();

  Serial.begin(9600);
  while (!Serial) continue;
}

bool recvWithEndMarker() {
 static byte ndx = 0;
 char endMarker = '\n';
 char rc;
 boolean newData = false;
 while (Serial.available() > 0 && newData == false) {
  rc = Serial.read();

  if (rc != endMarker) {
    receivedChars[ndx] = rc;
    ndx++;
    if (ndx >= numChars) {
    ndx = numChars - 1;
    }
  }
  else {
    receivedChars[ndx] = '\0'; // terminate the string
    int speed = atoi(receivedChars);
    motor1.run(speed); // value: between -255 and 255.
    motor2.run(speed); // value: between -255 and 255.
    /*if(ndx > 6)
    {
      int8_t speed;
      receivedChars[2] = '\0';
      device = atoi(receivedChars);
      switch(device){
        case 1:
          speed = atoi(&(receivedChars[3]));
          motor1.run(speed); // value: between -255 and 255.
          break;
        case 2:
          speed = atoi(&(receivedChars[3]));
          motor2.run(speed); // value: between -255 and 255.
          break;
      }
    }
    */
    ndx = 0;
    newData = true;
  }
 }
 return newData;
}

void loop() 
{
  loopcount++;
  Serial.println(loopcount);

  if(recvWithEndMarker())
  {

  }

  if (loopcount % 500){
    int passes = loopcount/500;
    if(passes%2)
    {
      led1.setColor(1, 255, 0, 255); // parameter description: led number, red, green, blue
      led1.setColor(2, 255, 255, 0); // parameter description: led number, red, green, blue
      led1.show();
    }
    else
    {
      led1.setColor(1, 0, 255, 255); // parameter description: led number, red, green, blue
      led1.setColor(2, 255, 0, 255); // parameter description: led number, red, green, blue
      led1.show();
    }
  }
}