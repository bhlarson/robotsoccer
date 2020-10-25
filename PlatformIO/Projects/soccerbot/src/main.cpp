#include <Arduino.h>
#include <MeShield.h>

MeRGBLed led1(PORT_3, SLOT1, 15);   /* parameter description: port, slot, led number */
MeRGBLed led2(PORT_3, SLOT2, 15);

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);

int16_t bri = 0, st = 0;
uint8_t motorSpeed = 0;

void setup() {
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  led1.setColor(1, 255, 0, 0); // parameter description: led number, red, green, blue
  led1.setColor(2, 0, 255, 0); // parameter description: led number, red, green, blue
  led1.show();

  Serial.begin(9600);
}

void loop() {

  String val;
  while (Serial.available() > 0) {
    val = val + (char)Serial.read(); // read data byte by byte and store it
  }
  Serial.print(val); // send the received data back to raspberry pi


  motor1.run(motorSpeed); // value: between -255 and 255.
  motor2.run(motorSpeed); // value: between -255 and 255.
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(100);

  motor1.run(-motorSpeed); // value: between -255 and 255.
  motor2.run(-motorSpeed); // value: between -255 and 255.

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(100);


/*
  if(bri >= 100)
  {
    st = 1;
  }
  if(bri <= 0)
  {
    st = 0;
  }

  if(st)
  {
    bri--;
  }
  else
  {
    bri++;
  }
  for(int16_t t = 0; t < 15; t++)
  {
    led1.setColorAt(t, bri, bri, bri); // parameter description: led number, red, green, blue, flash mode
    led2.setColorAt(t, bri, bri, bri);
  }
  led1.show();
  led2.show();
  delay(20);
*/
}