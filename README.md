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

## BOM

| Part Name | Quantity | Total Price | Where to Buy |
| :--- | :---: | :---: | :--- |
| uPen PCB | 5 | $69.56 | [JLCPCB](https://jlcpcb.com/) |
| uPen PCBA | 2 | $181.85 | [JLCPCB](https://jlcpcb.com/) |
| OLED Screen | 2 | $3.64 | [LCSC](https://www.lcsc.com/product-detail/C18723015.html?s_z=n_q_C18723015&globalKeyword=C18723015) |
| 30 AWG 0.5MM PCB Flying Jumper Wire | 1 | $7.00 | [AliExpress](https://www.aliexpress.us/item/2255800481153606.html?spm=a2g0o.productlist.main.1.5b8c52c6dqhfpX&algo_pvid=c0db41cf-f68a-49f3-b0cd-bbb869e4a1ec&algo_exp_id=c0db41cf-f68a-49f3-b0cd-bbb869e4a1ec-0&pdp_ext_f=%7B%22order%22%3A%22887%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%217.00%211.09%21%21%217.00%211.09%21%40210327b017942627382282212e0e79%2110000005571941385%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3Aa3d7507d%3Bm03_new_user%3A-29895%3BpisId%3A5000000218165391&curPageLogUid=KjZBONr446qX&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A4000667468358%7C_p_origin_prod%3A) |
| 301020 LiPo Batteries | 1 | $10.11 | [AliExpress](https://www.aliexpress.us/item/2251832810583728.html?spm=a2g0o.productlist.main.9.461bE4UAE4UArO&algo_pvid=3fd1e6d2-fe38-4eb0-b39f-49b563c3360b&algo_exp_id=3fd1e6d2-fe38-4eb0-b39f-49b563c3360b-8&pdp_ext_f=%7B%22order%22%3A%2235%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%2111.90%2110.00%21%21%2111.90%2110.00%21%402101d9ef17894343212786799e0d3e%2112000024080089254%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A748d72d8%3Bm03_new_user%3A-29895&curPageLogUid=2JfzQbrL5XBB&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A32996898480%7C_p_origin_prod%3A) |
| JST SH 1.0mm 2 Pin Cable | 1 | $3.69 | [AliExpress](https://www.aliexpress.us/item/3256809955750969.html?spm=a2g0o.productlist.main.3.62173c93cfTMBm&algo_pvid=2fcf1894-dfaa-4ec2-b01e-256d85639e75&algo_exp_id=2fcf1894-dfaa-4ec2-b01e-256d85639e75-2&pdp_ext_f=%7B%22order%22%3A%221818%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%213.69%211.09%21%21%2124.51%217.27%21%402101e80b17942634635358014e108a%2112000051297274513%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A50adb272%3Bm03_new_user%3A-29895%3BpisId%3A5000000218165389&curPageLogUid=ZEVk2uUcjnsi&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005010142065721%7C_p_origin_prod%3A) |
| OB-ARM Emulator (SWD) Debugger Programmer | 1 | $2.39 | [AliExpress](https://www.aliexpress.us/item/3256804889623613.html?spm=a2g0o.productlist.main.5.42947b73SrJzEG&algo_pvid=e1381424-0565-4f4a-8087-da6705d4fb17&algo_exp_id=e1381424-0565-4f4a-8087-da6705d4fb17-4&pdp_ext_f=%7B%22order%22%3A%22133%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21USD%212.39%212.22%21%21%212.39%212.22%21%402101ca9517942735271525494e0e07%2112000034785341692%21sea%21US%210%21ABX%211%210%21n_tag%3A-29910%3Bd%3A50adb272%3Bm03_new_user%3A-29895%3BpisId%3A5000000220758679&curPageLogUid=V1MZeZdXsAxP&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005005075938365%7C_p_origin_prod%3A) |
| uPen 3D Printed Parts | 1 | $1.00 | [Filament from local 3D printer](https://github.com/TheAbsoluteMin/u-pen/tree/main/v2_LATEST/v2_3D_Models/3D_Printing) |
| Total |  | $279.24 | Without Shipping |

## Credits
Thank you so much for generously funding and supporting the creation of uPen v2:
- Hack Club
- EasyEDA
