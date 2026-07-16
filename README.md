# uPen

<img width="1365" height="194" alt="image" src="https://github.com/user-attachments/assets/effb1129-49eb-436a-9e02-7a62cf8a8dd5" />
<img width="1339" height="238" alt="image" src="https://github.com/user-attachments/assets/204f2168-7dc2-484f-8eee-a35b3672bda1" />

uPen is a WiFi-enabled smart pen that records handwritten math equations and solves them.

## Inspiration

Initially, uPen was named Insta-Form, and it would have served as an alternative for Photomath. With its own camera, it would have captured images of math problems during engineering work and then solve them instantly in order to provide a seamless experience when working with mathematical models, physics, or measurement calculations. Before, I would personally spend a lot of time writing out equations and models by hand or on a calculator. Now, uPen seeks to increase productivity and efficiency by bypassing the precious time required to find answers manually. As I have worked extensively on uPen's design and creation, I have changed its physical hardware for it to be more intuitive to use. Instead of taking pictures with a camera, users can write naturally with uPen, and it will still be able to carry out its original and intended purpose of delivering quick math answers at users' convenience!

## How it works

<img width="1545" height="1999" alt="pageONE" src="https://github.com/user-attachments/assets/7a5ac4a3-aae8-4548-a74a-1550319c133e" />
<img width="1545" height="2000" alt="2" src="https://github.com/user-attachments/assets/38632e2b-2be6-420e-ae29-980187f510e8" />
<img width="1545" height="1999" alt="3" src="https://github.com/user-attachments/assets/3cb5a8e6-4893-4b0e-94de-0ae367360f2d" />
* ZUPT  stands for Zero Velocity Update, which is an algorithm that forces the velocity to zero in order to reduce accumulating errors in IMU modules.

## Features

* Uses compact yet powerful dual core ESP32 in the NanoS3 board
* LSM6DSV16X IMU 6-axis sensor fusion
* SDS001R tip switch for fast detection of writing state
* Small but powerful E-Flite 1S 3.7V 150mAh 45C LiPo battery
* External Li-ion BMS battery protection board
* Strong dipole 2.4GHz RX antenna
* Smart power states
* USB-C port for charging and coding
* USBLC6-2SC6 ESD protection
* Low battery alert at 15% battery
* Lightweight wireless data streaming to a base station ESP32 via ESP-NOW
* Dual I2C buses for fast data processing

## Credits

* Thank you to Hack Club for the opportunity and (hopefully) funding of uPen's creation!
