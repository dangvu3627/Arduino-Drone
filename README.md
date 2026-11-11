# Arduino Drone 

*This repo only contains firmware of this project*

This project was built and inspired by:
- 3-part drone [tutorial](https://youtu.be/S8TSkGQ2EWY?si=e3Gy7zZqBOBkJV40) from Electronoobs.
- Radio controller [tutorial](https://youtu.be/Sa6EslOHsI0?si=YmZvxvT938MjAr4-) by Max Imagination.
***

**Footages:**
 - Early development:
<img src="Test%20Footage/Early%20Stage%20Drone%20+%20Controller.jpeg" alt="Early Development" width="300">
- Final Result:
<img src="Test%20Footage/drone-test.jpg" alt="Final Result" width="300">
[https://github.com/user-attachments/assets/6bf99c5c-de32-47fb-9de3-ee1bcf440013](https://github.com/dangvu3627/Arduino-Drone/issues/2)

**Core Component & Firmware:**
- MultiWii_2_4: Open-source legacy firmware for Arduino-based drone.
- MPU6050: Accelerometer.
- nRF24L01: Radio Transceiver Module.
- Arduino Nano: Main MCU on the drone and the radio controller.

## Directory structure

```
Arduino Drone/
├── On-drone/
│   ├── MultiWii_2_4/                    (MultiWii/ and MultiWiiConf/ skipped)
│   │   └── change.txt
│   ├── RF24_config/
│   │   ├── RF24_receiver/
│   │   │   └── RF24_receiver.ino
│   │   ├── Rf24_Transmitter/
│   │   │   └── Rf24_Transmitter.ino
│   │   └── RF24L01_verification/
│   │       └── RF24L01_verification.ino
│   └── RF24_receiver_final/
│       └── RF24_receiver_final.ino
│
├── Radio Controller/
│   ├── ELECTRONOOBS_Drone_transmitter_6CH/
│   │   └── ELECTRONOOBS_Drone_transmitter_6CH.ino
│   └── NRF24_6CH_Radio_Controller_Code/
│       └── NRF24_6CH_Radio_Controller_Code.ino
│
└── Test for nRF and Servo control/
    ├── ELECTRONOOBS_Receiver_test_6CH/
    │   ├── ELECTRONOOBS_Receiver_test_6CH.ino
    │   └── NRF24_6CH_Radio_Controller_Code.ino
    ├── servo_control_w_pot/
    │   └── servo_control_w_pot.ino
    └── servo_control_w_RF24/
        ├── servo_control_w_RF24_Rx/
        │   └── servo_control_w_RF24_Rx.ino
        └── servo_control_w_RF24_Tx/
            └── servo_control_w_RF24_Tx.ino
```
