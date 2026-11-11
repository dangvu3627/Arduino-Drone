#include <Servo.h>

Servo myservo;  // Servo object to control the motor
int potpin = A0;  // Where the potentiometer is connected
int val;    // Variable to read the potentiometer value

void setup() {
  // Tell the servo object which pin to use
  Serial.begin(9600);
  myservo.attach(9, 1000, 2000);
}

void loop() {
  // Read the value of the potentiometer (value between 0 and 1023)
  val = analogRead(potpin);            
	
  // Scale it to use it with the servo (value between 0 and 180)
  val = map(val, 0, 1023, 0, 180);     

  // Set the servo position according to the scaled value
  myservo.write(val);
  Serial.println(val);
  
  // Wait for the servo to reach the position
  delay(15);
}