// SimpleTx - the master or the transmitter
// Arduino Nano

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R','x','A','c','A'};


RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

struct Package {
  byte potValue;
};

Package package;

//===================
void setup() {

    Serial.begin(9600);

    Serial.println("SimpleTx Starting");

    radio.begin();

    if (radio.begin()) {
        Serial.println("Pipeline success!");
    }

    radio.setDataRate(RF24_2MBPS);   
    radio.setPALevel(RF24_PA_MIN);
    radio.setRetries(3,5); // delay, count
    radio.openWritingPipe(slaveAddress);
}

//====================

void loop() {
    send();
}

//====================

void send() {
    bool rslt;
    package.potValue = map(analogRead(A2), 0, 1024, 0, 180);

    rslt = radio.write(&package, sizeof(package));

    if (!rslt) {
        delay(1000);
        Serial.println("Tx failed!");
    }

    Serial.println("Check your servo");
}

//================
