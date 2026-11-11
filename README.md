# Arduino Drone

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
