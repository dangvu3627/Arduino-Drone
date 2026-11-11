// Arduino Uno - The slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>



#define CE_PIN   9
#define CSN_PIN 10
#define SERVO_PIN 6

// Communication pipeline
const byte thisSlaveAddress[5] = {'R','x','A','c','A'};

// Transfer objects
RF24 radio(CE_PIN, CSN_PIN);

struct Package {
  byte potValue;
};

Package package;

// Timer
unsigned long currentMillis;
unsigned long lastMillis;
unsigned long rxThresMillis = 1000;

// Servo
Servo myservo;

//===========

void setup() {

    Serial.begin(9600);

    // Rx config --
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_2MBPS );
    radio.setPALevel(RF24_PA_MIN);
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();

    // Servo config --
    myservo.attach(SERVO_PIN);
}

//=============

void loop() {
    get();

    currentMillis = millis();

    if (currentMillis - lastMillis > rxThresMillis) {
        Serial.println("Transmission failed!");
        package.potValue = 0;
    }

    update();
}

//==============

void get() {
    if (radio.available()) {
        radio.read(&package, sizeof(package) );
        lastMillis = millis();
    }   
}

void update() {
    myservo.write(package.potValue);

} 
