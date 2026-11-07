# uPen v2
A Bluetooth smart pen that transforms handwritten notes into digital text.

<img width="1405" height="271" alt="image" src="https://github.com/user-attachments/assets/328ab8d2-5a6b-4a92-91ec-5f541d0c9851" />
<img width="1395" height="257" alt="image" src="https://github.com/user-attachments/assets/66df5f05-50e0-4efb-add2-150b69574e7d" />
<img width="2160" height="211" alt="image" src="https://github.com/user-attachments/assets/05571df4-4f03-4b7f-a87a-0081de979e32" />
<img width="2160" height="191" alt="image" src="https://github.com/user-attachments/assets/900ee21c-0544-4633-91f0-2372945b4017" />

<details>
<summary>
  <h3>Pictures</h3>
</summary>
<img width="1207" height="515" alt="image" src="https://github.com/user-attachments/assets/f1efde63-07a4-457e-8edd-2d1d88103514" />
<img width="1082" height="365" alt="image" src="https://github.com/user-attachments/assets/93155ada-eaa4-4a03-b0a8-46d65cab790e" />
<img width="1358" height="555" alt="image" src="https://github.com/user-attachments/assets/0dd2fa03-133d-4b3a-9e29-cfb734099052" />
</details>

## Introduction
uPen v2 is a complete redesign of v1. Not only were the PCB and CAD updated but the pen's purpose also changed.

With a sensor PCB and a pen ink refill in a slim case, uPen aims to bridge the gap between handwritten notes and digital notes. Especially when taking notes at school (or anywhere) by hand, it can be tedious to back up those notes online or turn them into online study aids (like Quizlet!). By seamlessly capturing, digitizing, and store handwriting strokes that can be synced online via Bluetooth, uPen v2 avoids cameras and keyboards without requiring any more effort when you write.

## How it works
1. You write naturally with uPen v2.
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

## CAD Case
3D model [link](https://cad.onshape.com/documents/3034b127fe9271adab18443b/w/723b7faf19a316a6d53fa867/e/b16e1a12b2835dfae5f24d19?renderMode=0&uiState=6aef887ea209f9e2942180de).

Before, uPen v1's case was 18mm wide (that's a really big pen!), and it was designed with Autodesk Fusion.

<img width="1142" height="259" alt="image" src="https://github.com/user-attachments/assets/e50ebf92-b821-4ab3-bfe5-22d76af1e56c" />

Now, uPen v2's case is a sleek 12.5mm wide, and it was designed with Onshape.

<img width="1417" height="335" alt="image" src="https://github.com/user-attachments/assets/c96bd7e7-12af-4d37-a40e-faa346134e2a" />

## PCB
uPen v2 was designed with EasyEDA Pro and ordered through JLCPCB.

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
- The SDA/SCL lines for the OLED are disconnected by default.
- In order to use OLED, you must solder 30 AWG wires to the respective vias.
- The LiPo battery connection requires a JST SH 1.0mm pitch connector.
- The recommended battery size is 301020 with 80 mAh.
- The NRF52840 MCU must be initially flashed with Nordic's software and bootloader via an SWD programmer before uploading firmware.
