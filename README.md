# uPen v2
A Bluetooth smart pen that transforms handwritten notes into digital text.

<img width="1405" height="271" alt="image" src="https://github.com/user-attachments/assets/328ab8d2-5a6b-4a92-91ec-5f541d0c9851" />
<img width="1395" height="257" alt="image" src="https://github.com/user-attachments/assets/66df5f05-50e0-4efb-add2-150b69574e7d" />
<img width="2160" height="211" alt="image" src="https://github.com/user-attachments/assets/05571df4-4f03-4b7f-a87a-0081de979e32" />
<img width="2160" height="191" alt="image" src="https://github.com/user-attachments/assets/900ee21c-0544-4633-91f0-2372945b4017" />

## Introduction
uPen v2 (the latest version) is a complete redesign of v1. Not only were the PCB and CAD updated but the pen's purpose also changed.

With a sensor PCB and a pen ink refill in a slim case, uPen aims to bridge the gap between handwritten notes and digital notes. Especially when taking notes at school (or anywhere) by hand, it can be tedious to back up those notes online or turn them into online study aids (like Quizlet!). By seamlessly capturing, digitizing, and store handwriting strokes that can be synced online via Bluetooth, uPen v2 avoids cameras and keyboards without requiring any more effort when you write.

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
10. Character recognition

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
** _Please note that the SDA/SCL lines for the OLED are intentionally not connected on the PCB by default_ **
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

## How To Use
1. Ensure uPen's battery is full by charging it with a USB-C cable.
2. Begin writing with uPen v2 as if it's a normal pen.
3. You can view your notes on the screen or sync them online via Bluetooth.

## Firmware Logic: How It Works
1. uPen automatically detects when you start writing.

<img width="1297" height="125" alt="image" src="https://github.com/user-attachments/assets/96611df2-33a6-43b1-bb70-74f2ffebe961" />

2. The LSM6DSV16XTR IMU captures handwriting strokes for each character that you write.

<img width="1312" height="152" alt="image" src="https://github.com/user-attachments/assets/18fb0bfd-8861-4efe-bc51-9656f7b4aa9e" />

3. Each character is separated in the firmware by sensing differences in electrostatic measurements of the QVAR function of the IMU.

<img width="1307" height="328" alt="image" src="https://github.com/user-attachments/assets/7a0c7a0b-c364-4585-b1e0-bab20166de1e" />
<img width="1337" height="240" alt="image" src="https://github.com/user-attachments/assets/2714bce4-4bae-4cca-9c23-d52a6e50be8e" />

4. Characters are translated into text.

<img width="1347" height="147" alt="image" src="https://github.com/user-attachments/assets/ecf4d736-170e-4ad0-b21a-d36079dfdd1b" />
<img width="1332" height="222" alt="image" src="https://github.com/user-attachments/assets/9465c0b8-7fcf-43cc-904e-1dfa398bc67c" />

5. Notes are stored into the flash memory chip for long term memory.

<img width="1295" height="560" alt="image" src="https://github.com/user-attachments/assets/934b4cac-5086-415f-8f66-180c2c540fdc" />

6. Notes can be transfered via Bluetooth.

<img width="1333" height="450" alt="image" src="https://github.com/user-attachments/assets/02de3e22-d732-4db7-a72b-8fd6ecc25ad4" />

### Firmware Setup
1. Flash Nordic's software and bootloader via an SWD programmer onto the NRF52840 MCU. Instructions are found [here](https://www.nordicsemi.com/Products/nRF52840/GetStarted).
2. Upload uPen's main code [here](https://github.com/TheAbsoluteMin/u-pen/blob/main/v2_LATEST/v2_Firmware/src/main.cpp) via USB-C.

## PCB Components BOM


| Part Name | Mfr. | Description | LCSC# | Min Order Qty. | Order Qty. | Unit Price (USD) | Ext.Price (USD) | Product Link |
| :--- | :--- | :--- | :--- | :---: | :---: | :---: | :---: | :--- |
| LQP03TG2N2B02D | muRata | 450mA 2.2nH 250mΩ Thick Film Inductor 0201 Fixed Inductors RoHS | C86107 | 100 | 100 | 0.0014 | 0.14 | [Link](https://www.lcsc.com/product-detail/C86107.html?spm=wm.mxq.bom.0.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| X201632MKB4SI | YXC Crystal Oscillators | Crystal 32MHz ±10ppm 8pF SMD2016-4P | C718072 | 5 | 5 | 0.0887 | 0.44 | [Link](https://www.lcsc.com/product-detail/C718072.html?spm=wm.mxq.bom.1.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| X1A0000610008 | EPSON | Crystal 32.768kHz ±20ppm 9pF 90kΩ SMD2012-2P | C96341 | 5 | 5 | 0.1908 | 0.95 | [Link](https://www.lcsc.com/product-detail/C96341.html?spm=wm.mxq.bom.2.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| NRF52840-QFAA-F-R7 | NORDIC | IC RF TXRX 802.15.4 Bluetooth QFN-48(6x6) | C3606653 | 1 | 1 | 4.8639 | 4.86 | [Link](https://www.lcsc.com/product-detail/C3606653.html?spm=wm.mxq.bom.3.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| LQP03TN4N7H02D | muRata | 350mA 4.7nH ±3% 400mΩ 0201 Fixed Inductors RoHS | C86126 | 50 | 50 | 0.0044 | 0.22 | [Link](https://www.lcsc.com/product-detail/C86126.html?spm=wm.mxq.bom.4.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| LQG15HS15NJ02D | muRata | 450mA 15nH ±5% 320mΩ 0402 Fixed Inductors RoHS | C86059 | 20 | 20 | 0.0136 | 0.27 | [Link](https://www.lcsc.com/product-detail/C86059.html?spm=wm.mxq.bom.5.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0201FRNPO9BN120 | YAGEO | 12pF ±1% 50V Ceramic Capacitor NP0 0201 | C526929 | 100 | 100 | 0.0020 | 0.20 | [Link](https://www.lcsc.com/product-detail/C526929.html?spm=wm.mxq.bom.6.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0201BRNPO9BN1R0 | YAGEO | 1pF 50V Ceramic Capacitor NP0 0201 | C281747 | 100 | 100 | 0.0014 | 0.14 | [Link](https://www.lcsc.com/product-detail/C281747.html?spm=wm.mxq.bom.7.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0201BRNPO9BN1R2 | YAGEO | 1.2pF 50V Ceramic Capacitor NP0 0201 | C326704 | 100 | 100 | 0.0013 | 0.13 | [Link](https://www.lcsc.com/product-detail/C326704.html?spm=wm.mxq.bom.8.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CL03A104KP3NNNC | Samsung Electro-Mechanics | 100nF ±10% 10V Ceramic Capacitor X5R 0201 | C49062 | 100 | 100 | 0.0012 | 0.12 | [Link](https://www.lcsc.com/product-detail/C49062.html?spm=wm.mxq.bom.9.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0201GRNPO9BN101 | YAGEO | 100pF ±2% 50V Ceramic Capacitor NP0 0201 | C541242 | 100 | 100 | 0.0017 | 0.17 | [Link](https://www.lcsc.com/product-detail/C541242.html?spm=wm.mxq.bom.10.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| GRM155R61A105KE15D | muRata | 1uF ±10% 10V Ceramic Capacitor X5R 0402 | C76999 | 50 | 50 | 0.0029 | 0.15 | [Link](https://www.lcsc.com/product-detail/C76999.html?spm=wm.mxq.bom.11.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0201KRX5R7BB473 | YAGEO | 47nF ±10% 16V Ceramic Capacitor X5R 0201 | C505465 | 100 | 100 | 0.0021 | 0.21 | [Link](https://www.lcsc.com/product-detail/C505465.html?spm=wm.mxq.bom.12.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| AF0201FR-0710KL | YAGEO | 50mW 10kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C143978 | 100 | 100 | 0.0019 | 0.19 | [Link](https://www.lcsc.com/product-detail/C143978.html?spm=wm.mxq.bom.13.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| GD25Q64CWIGR | GigaDevice Semicon Beijing | 64Mbit 2.7V~3.6V 120MHz SPI WSON-8-EP(5x6) Memory RoHS | C395511 | 1 | 1 | 1.0200 | 1.02 | [Link](https://www.lcsc.com/product-detail/C395511.html?spm=wm.mxq.bom.14.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| WR02X4702FAL | Walsin | 47kΩ ±1% 50mW 0201 Thick Film Resistor | C171928 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C171928.html?spm=wm.mxq.bom.15.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| LQM18DN100M70L | muRata | 300mA 10uH ±20% 100mA 1.365Ω 0603 Fixed Inductors RoHS | C713281 | 5 | 5 | 0.0850 | 0.43 | [Link](https://www.lcsc.com/product-detail/C713281.html?spm=wm.mxq.bom.16.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| EVQP2P02W | PANASONIC | Tactile Switch SPST 1N 2.5mm J-Lead 4.7mm x 3.5mm Surface Mount | C512395 | 1 | 2 | 0.3696 | 0.74 | [Link](https://www.lcsc.com/product-detail/C512395.html?spm=wm.mxq.bom.17.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| AMCA31-2R450G-S1F-T3 | ABRACON | Surface Mount WLAN / Bluetooth Chip Antenna | C3283994 | 5 | 5 | 0.2603 | 1.30 | [Link](https://www.lcsc.com/product-detail/C3283994.html?spm=wm.mxq.bom.19.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0402CRNPO9BN1R5 | YAGEO | 1.5pF 50V Ceramic Capacitor NP0 0402 | C189471 | 100 | 100 | 0.0010 | 0.10 | [Link](https://www.lcsc.com/product-detail/C189471.html?spm=wm.mxq.bom.20.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| MLG1005S3N9BT000 | TDK | 700mA 3.9nH 110mΩ Multilayer inductor 0402 Fixed Inductors RoHS | C76775 | 10 | 10 | 0.0065 | 0.07 | [Link](https://www.lcsc.com/product-detail/C76775.html?spm=wm.mxq.bom.21.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CP2102N-A02-GQFN20R | SILICON LABS | USB to UART 3Mbps QFN-20-EP(3x3) Controllers RoHS | C969913 | 1 | 1 | 1.4298 | 1.43 | [Link](https://www.lcsc.com/product-detail/C969913.html?spm=wm.mxq.bom.22.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| TYPE-C16PIN | SHOU HAN | USB-C (USB TYPE-C) Receptacle Connector 16 Position Surface Mount, Right Angle | C393939 | 10 | 10 | 0.0595 | 0.60 | [Link](https://www.lcsc.com/product-detail/C393939.html?spm=wm.mxq.bom.23.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| XC6206P332MR-G | TOREX | 3.3V Positive Fixed SOT-23-3L Voltage Regulators - Linear, Low Drop Out (LDO) Regulators RoHS | C5446 | 5 | 5 | 0.1342 | 0.67 | [Link](https://www.lcsc.com/product-detail/C5446.html?spm=wm.mxq.bom.24.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| AF0201FR-075K1L | YAGEO | 50mW 5.1kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C143995 | 100 | 100 | 0.0019 | 0.19 | [Link](https://www.lcsc.com/product-detail/C143995.html?spm=wm.mxq.bom.25.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CGA0402X5R475K160GT | HRE | 4.7uF X5R ±10% 16V 0402 Ceramic Capacitors | C52037851 | 20 | 20 | 0.0144 | 0.29 | [Link](https://www.lcsc.com/product-detail/C52037851.html?spm=wm.mxq.bom.26.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| USBLC6-2SC6 | ST | 17VC Clamp 5A Ipp ESD DIODE SOT-23-6L | C7519 | 5 | 5 | 0.1391 | 0.70 | [Link](https://www.lcsc.com/product-detail/C7519.html?spm=wm.mxq.bom.27.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-0722K1L | YAGEO | 50mW 22.1kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C142019 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C142019.html?spm=wm.mxq.bom.28.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| 0201WMF4752TEE | UNI-ROYAL | 47.5kΩ ±1% 50mW 0201 Thick Film Resistor | C473579 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C473579.html?spm=wm.mxq.bom.29.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-0727KL | YAGEO | 27kΩ 50mW 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C273283 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C273283.html?spm=wm.mxq.bom.30.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201JR-071KL | YAGEO | 50mW 1kΩ 25V Thick Film Resistor ±5% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C131396 | 100 | 100 | 0.0004 | 0.04 | [Link](https://www.lcsc.com/product-detail/C131396.html?spm=wm.mxq.bom.31.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-07100KL | YAGEO | 50mW 100kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C106224 | 100 | 100 | 0.0006 | 0.06 | [Link](https://www.lcsc.com/product-detail/C106224.html?spm=wm.mxq.bom.32.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| SH1.0mm-2P-WT | LXWCONN | Surface Mount, Right Angle 1mm 1A SH 50V -25°C~+85°C Tin 2P 2 1 1x2P SMD,P=1mm,Surface Mount,Right Angle Headers, Male Pins | C53055318 | 20 | 20 | 0.0225 | 0.45 | [Link](https://www.lcsc.com/product-detail/C53055318.html?spm=wm.mxq.bom.33.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| MCP73831T-2ATI/OT | MICROCHIP | 3.75V~6V 1 Lithium Battery 550mA SOT-23-5 Battery Chargers RoHS | C14879 | 1 | 1 | 0.8160 | 0.82 | [Link](https://www.lcsc.com/product-detail/C14879.html?spm=wm.mxq.bom.34.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| TPS2116DRLR | TI | 2 Channel 2.5A SOT-583 | C3235557 | 1 | 1 | 0.3234 | 0.32 | [Link](https://www.lcsc.com/product-detail/C3235557.html?spm=wm.mxq.bom.35.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-07620RL | YAGEO | 620Ω 50mW 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C295811 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C295811.html?spm=wm.mxq.bom.36.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| KT-0603YG | Hubei KENTO Elec | Yellow Green LED Indication - Discrete 2V~2.2V 0603 | C2289 | 50 | 50 | 0.0066 | 0.33 | [Link](https://www.lcsc.com/product-detail/C2289.html?spm=wm.mxq.bom.37.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| HX MSS12C02-BB2.0 | hanxia | Slide Switch SPDT 100mA @ 12V Surface Mount Rectangular Columnar 6.65mm | C25168817 | 5 | 5 | 0.0853 | 0.43 | [Link](https://www.lcsc.com/product-detail/C25168817.html?spm=wm.mxq.bom.38.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| LSM6DSV16XTR | ST | LGA-14(2.5x3) IMUs (Inertial Measurement Units) RoHS | C5267406 | 1 | 1 | 2.4405 | 2.44 | [Link](https://www.lcsc.com/product-detail/C5267406.html?spm=wm.mxq.bom.39.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-072K2L | YAGEO | 50mW 2.2kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C142018 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C142018.html?spm=wm.mxq.bom.40.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| X087-2832TSWIG02-H14 | Wisevision | 0.87 128x32 SSD1312 chip I2C LCD, OLED, Graphic RoHS | C18723015 | 1 | 1 | 1.4902 | 1.49 | [Link](https://www.lcsc.com/product-detail/C18723015.html?spm=wm.mxq.bom.41.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0603KRX7R7BB225 | YAGEO | 2.2uF ±10% 16V Ceramic Capacitor X7R 0603 | C914769 | 10 | 10 | 0.0381 | 0.38 | [Link](https://www.lcsc.com/product-detail/C914769.html?spm=wm.mxq.bom.42.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CGA0603X7R475K160JT | HRE | 4.7uF ±10% 16V Ceramic Capacitor X7R 0603 | C22399629 | 20 | 20 | 0.0174 | 0.35 | [Link](https://www.lcsc.com/product-detail/C22399629.html?spm=wm.mxq.bom.43.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| TCC0201X7R104K160ZT | CCTC | 100nF ±10% 16V Ceramic Capacitor X7R 0201 | C18164586 | 50 | 50 | 0.0017 | 0.09 | [Link](https://www.lcsc.com/product-detail/C18164586.html?spm=wm.mxq.bom.44.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| CC0603KRX7R7BB105 | YAGEO | 1uF ±10% 16V Ceramic Capacitor X7R 0603 | C106248 | 50 | 50 | 0.0039 | 0.20 | [Link](https://www.lcsc.com/product-detail/C106248.html?spm=wm.mxq.bom.45.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-07560KL | YAGEO | 50mW 560kΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C295807 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C295807.html?spm=wm.mxq.bom.46.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| FDN338P | onsemi | P-Channel 20V 1.6A 0.5W Surface Mount SOT-23 | C24855 | 5 | 5 | 0.1807 | 0.90 | [Link](https://www.lcsc.com/product-detail/C24855.html?spm=wm.mxq.bom.47.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| FDN335N | onsemi | N-Channel 20V 1.7A 0.5W Surface Mount SOT-23-3 | C241804 | 5 | 5 | 0.1477 | 0.74 | [Link](https://www.lcsc.com/product-detail/C241804.html?spm=wm.mxq.bom.48.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| RC0201FR-071ML | YAGEO | 50mW 1MΩ 25V Thick Film Resistor ±1% ±200ppm/°C 0201 Chip Resistor - Surface Mount RoHS | C295786 | 100 | 100 | 0.0005 | 0.05 | [Link](https://www.lcsc.com/product-detail/C295786.html?spm=wm.mxq.bom.49.xh___wm.bjg.btn.cre&lcsc_vid=EwQKVldeTwdaXlNURANeBldeElULUwdSQ1UIXlAFQAcxVlNfQ1deVFBVTlZWUzsOAxUeFF5JWA4dDxMKFgNABAsLWA%3D%3D) |
| Total | | Total is included in uPen PCBA | | | | (USD) | $25.17 | Without Shipping |

## Full BOM

| Part Name | Quantity | Total Price | Where to Buy |
| :--- | :---: | :---: | :--- |
| uPen PCB | 5 | 69.56 | [JLCPCB](https://jlcpcb.com/) |
| uPen PCBA | 2 | 181.85 | [JLCPCB](https://jlcpcb.com/) |
| OLED Screen | 2 | 3.64 | [LCSC](https://www.lcsc.com/product-detail/C18723015.html?s_z=n_q_C18723015&globalKeyword=C18723015) |
| 30 AWG 0.5MM PCB Flying Jumper Wire | 1 | 7.00 | [AliExpress](https://www.aliexpress.us/item/2255800481153606.html?spm=a2g0o.productlist.main.1.5b8c52c6dqhfpX&algo_pvid=c0db41cf-f68a-49f3-b0cd-bbb869e4a1ec&algo_exp_id=c0db41cf-f68a-49f3-b0cd-bbb869e4a1ec-0&pdp_ext_f=%7B%22order%22%3A%22887%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%217.00%211.09%21%21%217.00%211.09%21%40210327b017942627382282212e0e79%2110000005571941385%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Aa3d7507d%3Bm03_new_user%3A-29895%3BpisId%3A5000000218165391&curPageLogUid=KjZBONr446qX&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A4000667468358%7C_p_origin_prod%3A) |
| 301020 LiPo Batteries | 1 | 10.11 | [AliExpress](https://www.aliexpress.us/item/2251832810583728.html?spm=a2g0o.productlist.main.9.461bE4UAE4UArO&algo_pvid=3fd1e6d2-fe38-4eb0-b39f-49b563c3360b&algo_exp_id=3fd1e6d2-fe38-4eb0-b39f-49b563c3360b-8&pdp_ext_f=%7B%22order%22%3A%2235%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.90%2110.00%21%21%2111.90%2110.00%21%402101d9ef17894343212786799e0d3e%2112000024080089254%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A748d72d8%3Bm03_new_user%3A-29895&curPageLogUid=2JfzQbrL5XBB&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A32996898480%7C_p_origin_prod%3A) |
| JST SH 1.0mm 2 Pin Cable | 1 | 3.69 | [AliExpress](https://www.aliexpress.us/item/3256809955750969.html?spm=a2g0o.productlist.main.3.62173c93cfTMBm&algo_pvid=2fcf1894-dfaa-4ec2-b01e-256d85639e75&algo_exp_id=2fcf1894-dfaa-4ec2-b01e-256d85639e75-2&pdp_ext_f=%7B%22order%22%3A%221818%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.69%211.09%21%21%2124.51%217.27%21%402101e80b17942634635358014e108a%2112000051297274513%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A50adb272%3Bm03_new_user%3A-29895%3BpisId%3A5000000218165389&curPageLogUid=ZEVk2uUcjnsi&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010142065721%7C_p_origin_prod%3A) |
| OB-ARM Emulator (SWD) Debugger Programmer | 1 | 2.39 | [AliExpress](https://www.aliexpress.us/item/3256804889623613.html?spm=a2g0o.productlist.main.5.42947b73SrJzEG&algo_pvid=e1381424-0565-4f4a-8087-da6705d4fb17&algo_exp_id=e1381424-0565-4f4a-8087-da6705d4fb17-4&pdp_ext_f=%7B%22order%22%3A%22133%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.39%212.22%21%21%212.39%212.22%21%402101ca9517942735271525494e0e07%2112000034785341692%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A50adb272%3Bm03_new_user%3A-29895%3BpisId%3A5000000220758679&curPageLogUid=V1MZeZdXsAxP&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005075938365%7C_p_origin_prod%3A) |
| uPen 3D Printed Parts | 1 | 1.00 | [Filament from local 3D printer](https://github.com/TheAbsoluteMin/u-pen/tree/main/v2_LATEST/v2_3D_Models/3D_Printing) |
| Total | (USD) | $279.24 | Without Shipping |

## Credits
Thank you so much for generously funding and supporting the creation of uPen v2:
- Hack Club
- EasyEDA
