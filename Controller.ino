
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define jY0 A0
#define jX0 A1
#define jY1 A2
#define jX1 A3
#define pot1 A4
#define pot2 A5

RF24 radio(7, 8); // CE, CSN  for nano 
//RF24 radio(9, 10); // CE, CSN for UNO
       
const byte address[6] = "00001";
byte output[25];

void setup() {
  Serial.begin(9600);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}

void loop() 
{
  //Left Joystick Input
  int yVal1 = analogRead(jY0);
  int xVal1 = analogRead(jX0);
  //Right Joystick Input
  int yVal2 = analogRead(jY1);
  int xVal2 = analogRead(jX1);
  //Potentiometer Input
  int p1 = analogRead(pot1);
  //Map Input values to usable pwm duty cycles
  yVal1 = map(yVal1,0,1023,0,255);
  xVal1 = map(xVal1,0,1023,0,255);
  yVal2 = map(yVal2,0,1023,0,255);
  xVal2 = map(xVal2,0,1023,0,255);
  p1 = map(p1,0,1023,255,0);
  //Set values to array to send through pipeline
  output[0] = yVal1;
  output[1] = xVal1;
  output[2] = yVal2;
  output[3] = xVal2;
  output[4] = p1;
  //Hardcoded values for testing
//   output[0] = 0;
//  output[1] = 1;
//  output[2] = 2;
//  output[3] = 3;
//  output[4] = 4;

  Serial.println("Sending text");
  radio.write(&output, sizeof(output));                  //Sending the message to receiver
  delay(100);
  
  //Print Ouptut Values
  Serial.println("X1: " + String(xVal1) + "\tY1: " + String(yVal1));
  Serial.println("X2: " + String(xVal2) + "\tY2: " + String(yVal2));
  Serial.println("Pot1: " + String(p1));
}
