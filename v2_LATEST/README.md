# uPen v2
A Bluetooth smart pen that transforms handwritten notes into digital text.

<img width="1405" height="271" alt="image" src="https://github.com/user-attachments/assets/328ab8d2-5a6b-4a92-91ec-5f541d0c9851" />
<img width="1395" height="257" alt="image" src="https://github.com/user-attachments/assets/66df5f05-50e0-4efb-add2-150b69574e7d" />
<img width="2160" height="211" alt="image" src="https://github.com/user-attachments/assets/05571df4-4f03-4b7f-a87a-0081de979e32" />
<img width="2160" height="191" alt="image" src="https://github.com/user-attachments/assets/900ee21c-0544-4633-91f0-2372945b4017" />

## Introduction
uPen v2 (the latest version) is a complete redesign of v1. Not only were the PCB and CAD updated but the pen's purpose also changed.

With a sensor PCB and a pen ink refill in a slim case, uPen aims to bridge the gap between handwritten notes and digital notes. Especially when taking notes at school (or anywhere) by hand, it can be tedious to back up those notes online or turn them into online study aids (like Quizlet!). By seamlessly capturing, digitizing, and store handwriting strokes that can be synced online via Bluetooth, uPen v2 avoids cameras and keyboards without requiring any more effort when you write.

## How it works
1. You write with uPen v2 as if it's a normal pen.
2. The LSM6DSV16XTR IMU captures handwriting strokes for each character written.
3. Each character is separated in the firmware by sensing differences in electrostatic measurements of the QVAR function of the IMU.
4. A lightweight tiny AI translates each character into text, storing it into the flash memory chip for long term memory.
5. You can transfer your notes via the Bluetooth function.

## Features
1. NRF52840 MCU
2. 8 megabyte SPI NOR Flash memory IC
3. Bluetooth data syncing
4. CP2102N USB-C coding
5. OLED display
6. USB-C and QVAR sensing USBLC6-2SC6 ESD protection
7. LSM6DSV16XTR IMU
8. Power timing and regulation between 5V USB-C and 3.7V LiPo battery
9. Built-in charging
10. Tiny AI character recognition

## Schematics
<img width="1153" height="811" alt="image" src="https://github.com/user-attachments/assets/2d6580a7-921b-4876-872e-f577db466077" />
<img width="1920" height="1360" alt="image" src="https://github.com/user-attachments/assets/7ffcd238-2036-4851-9728-4a56f6edc1c0" />
<img width="1920" height="1360" alt="image" src="https://github.com/user-attachments/assets/5e0cf67f-eedf-4524-8d39-824bdc42be01" />


## PCB
uPen v2 was designed with EasyEDA Pro.

<img width="1413" height="122" alt="image" src="https://github.com/user-attachments/assets/88bce8e9-db94-43c6-9272-3156bf29716b" />
<img width="1442" height="127" alt="image" src="https://github.com/user-attachments/assets/6fda33bf-086c-4819-9180-c4cd6accdf61" />

### PCB Layers
Top Layer
<img width="2160" height="230" alt="image" src="https://github.com/user-attachments/assets/8169fce2-0bdc-4865-b8d5-c29dd3fbc6fe" />
Inner Layer 1
<img width="2160" height="230" alt="image" src="https://github.com/user-attachments/assets/3f539a1b-bb43-4e49-90d3-18268c0a36e9" />
Inner Layer 2
<img width="2160" height="230" alt="image" src="https://github.com/user-attachments/assets/b3055de7-44da-4fb1-835d-f6d5e80f45fd" />
Bottom Layer
<img width="2160" height="230" alt="image" src="https://github.com/user-attachments/assets/76ef1a02-b493-46b6-aa62-67ce828dc3c2" />

### PCB Assembly
1. Solder 30 AWG wires for the OLED's SDA/SCL lines to the respective vias as marked on the PCB.
2. Solder on the OLED screen on the back of the PCB.
3. With a JST SH 1.0mm pitch connector, plug in the battery (recommended is 301020 size with 80 mAh).

## CAD Case
3D model [link](https://cad.onshape.com/documents/3034b127fe9271adab18443b/w/723b7faf19a316a6d53fa867/e/b16e1a12b2835dfae5f24d19?renderMode=0&uiState=6aef887ea209f9e2942180de).

Before, uPen v1's case was 18mm wide (that's a really big pen!), and it was designed with Autodesk Fusion.

<img width="1142" height="259" alt="image" src="https://github.com/user-attachments/assets/e50ebf92-b821-4ab3-bfe5-22d76af1e56c" />

Now, uPen v2's case is a sleek 12.5mm wide, and it was designed with Onshape.

<img width="1417" height="335" alt="image" src="https://github.com/user-attachments/assets/c96bd7e7-12af-4d37-a40e-faa346134e2a" />

<details>
<summary>
  <h3>Pictures</h3>
</summary>
<img width="1207" height="515" alt="image" src="https://github.com/user-attachments/assets/f1efde63-07a4-457e-8edd-2d1d88103514" />
<img width="1082" height="365" alt="image" src="https://github.com/user-attachments/assets/93155ada-eaa4-4a03-b0a8-46d65cab790e" />
<img width="1358" height="555" alt="image" src="https://github.com/user-attachments/assets/0dd2fa03-133d-4b3a-9e29-cfb734099052" />
</details>

### CAD Case Assembly
1. Attach the Button and Switch extensions on the PCB.
2. After placing the PCB inside the Bottom Case, snap the Top Case above it.
3. With the pen ink refill inside, press the Nose part onto the case. 

## Firmware
1. The NRF52840 MCU must be initially flashed with Nordic's software and bootloader via an SWD programmer before uploading the pen's main code.

## BOM
//
