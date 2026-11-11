/* 6 channels receiver */

// Pin sequence:
// GND GND#1
// Vcc 5V
// CE 9
// CSN 10
// MOSI 11
// MISO 12
// SCK 13

// PPM_Out D2
// ESC_BEC Vin
// ESC_GND GND#2

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
////////////////////// CONFIGURATION del PPM//////////////////////////
#define channel_number 6 //we will have 6 channels
#define sigPin 2 //The PPM output will be pin D2
#define PPM_FrLen 27000 //frames per seccond of the PPM (1ms = 1000µs)
#define PPM_PulseLen 400 //pulse width config
//////////////////////////////////////////////////////////////////

int ppm[channel_number];

const byte pipeIn[5] = {'R','x','A','c','A'};
// Same as Tx

RF24 radio(9, 10); //radio(CE, CSN)

//Up to 32 channels
struct MyData {
  byte throttle; 
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
};

MyData data;

void resetData()
{
//We give the start value of each byte

data.throttle = 0;
data.yaw = 127;
data.pitch = 127;
data.roll = 127;
data.AUX1 = 0;
data.AUX2 = 0;

setPPMValuesFromData();//we call this function that will map the values

}

void setPPMValuesFromData()
{
  ppm[0] = map(data.throttle, 0, 255, 1000, 2000);
  ppm[1] = map(data.yaw, 0, 255, 1000, 2000);
  ppm[2] = map(data.pitch, 0, 255, 1000, 2000);
  ppm[3] = map(data.roll, 0, 255, 1000, 2000);
  ppm[4] = map(data.AUX1, 0, 1, 1000, 2000);
  ppm[5] = map(data.AUX2, 0, 1, 1000, 2000);
}

/**************************************************/

void setupPPM() {
pinMode(sigPin, OUTPUT);
digitalWrite(sigPin, 0); //We put the signal pin of the PPM in his "normal" state (off)

cli();
TCCR1A = 0; // We set to 0 the TCCR1 register
TCCR1B = 0;

OCR1A = 100;
TCCR1B |= (1 << WGM12); // We start CTC mode
TCCR1B |= (1 << CS11); // 8 prescale: 0,5 microseconds at 16mhz
TIMSK1 |= (1 << OCIE1A); // Interrupt enable
sei();
}

void setup()
{
  resetData();
  setupPPM();

  // Set up Radio module
  radio.begin();
  //radio.setAutoAck(false);
  radio.setDataRate(RF24_1MBPS);

  radio.openReadingPipe(1,pipeIn);
  radio.startListening();

}

/**************************************************/

unsigned long lastRecvTime = 0;

void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(MyData));
lastRecvTime = millis();
}
}

/**************************************************/

void loop()
{
  recvData();

  unsigned long now = millis();
  if ( now - lastRecvTime > 1000 ) {
  // Signal lost?
  resetData();
  }

  setPPMValuesFromData();
}

/**************************************************/

// #error Make sure that your clockMultiplier is the correct one (below). Delete this line after that
#define clockMultiplier 2 //set this to 2 if you're using a 16MHz arduino, leave it to 1 for a 8MHz arduino

ISR(TIMER1_COMPA_vect){
  static boolean state = true;

  TCNT1 = 0;

  if ( state ) {
    //end pulse
    PORTD = PORTD & ~B00000100; // turn off D2
    OCR1A = PPM_PulseLen * clockMultiplier;
    state = false;
  }
  else {
    //start pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    PORTD = PORTD | B00000100; // turn on D2
    state = true;

    if(cur_chan_numb >= channel_number) {
      cur_chan_numb = 0;
      calc_rest += PPM_PulseLen;
      OCR1A = (PPM_FrLen - calc_rest) * clockMultiplier;
      calc_rest = 0;
    }
    else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * clockMultiplier;
      calc_rest += ppm[cur_chan_numb];
      cur_chan_numb++;
    }
  }
}