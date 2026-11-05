---
title: "uPen v2"
author: "TheAbsoluteMin"
description: "A Bluetooth smart pen that transforms handwritten notes into digital text."
created_at: "2026-09-12"
---

# Log 1: 9.12.2026 - 9.13.2026 - Schematics Remake
Timelapse <a href="https://lapse.hackclub.com/timelapse/KwB7Z5Aam9te">link</a>.

Today was a big day!

After a lot of thought, I decided that my original concept of uPen seemed impractical, and its PCB itself had some routing and layout issues. Moreover, the CAD case of the pen was unnaturally enormous compared to a normal pen. Thus, I took upon the challenge to redesign the uPen's PCB using ICs instead of devboards.

Ultimately, the most important change was uPen's purpose. During school, I always preferred taking online notes, but some of my teachers started to require that I write handwritten notes. This made me unhappy because I was used to using online studying platforms like Quizlet, and I did not want to manually copy my notes online. This is where uPen comes in. With the LSM6DSV16XTR IMU, it will record and translate handwritten notes to digital text in real time!

Unfortunately, I had to return the laptop I borrowed during the summer. I could not run KiCad on my Chromebook, so I switched to EasyEDA Pro. With that, I began working on wiring the MCU.

<img width="1882" height="788" alt="image" src="https://github.com/user-attachments/assets/d047efeb-8d54-4b70-80d0-a3d0d6c1f9ee" />

Instead of the battery-hungry ESP32-S3, I wanted to make my pen thinner with a smaller battery, so I used the Nordic nRF52840 MCU.

<img width="1907" height="772" alt="image" src="https://github.com/user-attachments/assets/aa4c9f68-8172-4752-894f-ea83865260e6" />

It was a bit difficult as I had not wired crystal oscillators before.

**Total time spent: 1.5 hours**

---

# Log 2: 9.14.2026 - 9.15.2026 - Power Schematics Remake
Timelapse <a href="https://lapse.hackclub.com/timelapse/QheCo4zIfCTF">link</a>.

I began to work on the power blocks for the pen, starting with the USB-C receptacle and ESD protection.

<img width="1907" height="782" alt="image" src="https://github.com/user-attachments/assets/db10d63e-b0cd-425b-92ab-498e74798171" />

With some research and a lot of scrolling through datasheets, I realized that the Nordic nRF52840 MCU QFN-48 version I was using did not break out data lines for the USB-C receptacle! This meant that I needed to use a chip like the CP2102N in order to translate the data lines into RX/TX lines that the MCU can understand.

<img width="1905" height="786" alt="image" src="https://github.com/user-attachments/assets/25f776d7-ee76-4ebe-b79e-004d5864de4a" />

In order for my pen to charge its battery, I included the TP4054 charger IC.

<img width="1902" height="788" alt="image" src="https://github.com/user-attachments/assets/eabe85f1-439b-4db0-9228-fdba8c4b0a5f" />

**Total time spent: 3.5 hours**

---

# Log 3: 9.16.2026 - 9.17.2026 - Power Regulation Blocks
Timelapse <a href="https://lapse.hackclub.com/timelapse/qfui5H7x2q5h">link</a>.

Today, I designed the power multiplexer circuit so that my pen could seamlessly switch from battery to USB-C power. I was hoping to isolate the USB-C power from the MCU completely, but then I realized that I would need the MCU to turn on when I am coding.

In earlier projects, I used two diodes to create an OR gate, but I quickly learned that it was inefficient. Thus, I decided to test out an ideal diode design using a P-channel MOSFET.

<img width="1905" height="785" alt="image" src="https://github.com/user-attachments/assets/0e8e787b-5f54-48b2-ba49-7c354b1bc287" />

A key feature of this design was that it prevented the voltage drop across a normal diode for the battery.

Then, I began to incorporate the battery JST plug and a switch in order to turn the pen on and off. I added a voltage divider, so I could easily monitor battery levels when using the pen.

<img width="1905" height="782" alt="image" src="https://github.com/user-attachments/assets/adac0ad8-c676-4f57-bb19-677cb2fa6f6c" />

Realizing that I may need to store a lot of notes on my pen in the future, I included a FLASH storage chip.

<img width="1907" height="787" alt="image" src="https://github.com/user-attachments/assets/a6bae7fd-b60b-46e9-99d5-b0f4b1477089" />

After some thought, I realized that my ideal diode was a somewhat messy solution to handle both power inputs as the USB-C input still passed through a diode anyway. Thus, I swapped my power circuit with the TPS2116DRLR. This IC cleanly prioritizes USB-C power over battery power, and it automatically switches to battery power when USB-C power is not present.

<img width="1907" height="792" alt="image" src="https://github.com/user-attachments/assets/9359e802-7bf0-4952-aa95-63d89ff97910" />

**Total time spent: 4.25 hours**

---

# Log 4: 9.18.2026 - 9.20.2026 - Schematics Refining
Timelapse <a href="https://lapse.hackclub.com/timelapse/4GGD8A-lRWrq">link</a>.

I began designing the schematics for the IMU sensor, which was relatively straightforward since I had already worked with this specific IC before.

<img width="1905" height="785" alt="image" src="https://github.com/user-attachments/assets/ca8fdb16-9a61-4282-88e4-2315f5a06b8a" />

After looking through the datasheet for the IMU, I found an interesting function that I had overlooked earlier. It featured QVAR technology, which enabled me to sense electrostatic changes. I realized that this could be serve as a solid state replacement for a tip switch by sensing the electrostatic changes when the pen is near paper and in the air.

<img width="1911" height="783" alt="image" src="https://github.com/user-attachments/assets/a3b35e93-35b1-463a-ac22-85e3b502d6bf" />

I needed a small UI for the user, but hobby OLEDs were too big. However, I found bare OLED panels on JLCPCB that were extremely thin!

<img width="1895" height="816" alt="image" src="https://github.com/user-attachments/assets/0793389f-ab6f-4383-81a9-31f926ff64f1" />

It took some time figuring out what the datasheet meant, but I eventually pieced together the OLED circuit.

<img width="1908" height="787" alt="image" src="https://github.com/user-attachments/assets/6354984c-d725-4b8a-892f-af10c8daf29a" />
<img width="1903" height="787" alt="image" src="https://github.com/user-attachments/assets/5b5fe10c-1cb1-451e-a7d0-6347f5546116" />

Finally, I began to check that my wire nets aligned on the different schematic sheets and that they were on the correct MCU pin.

<img width="1902" height="777" alt="image" src="https://github.com/user-attachments/assets/4ced57be-64e8-48a6-a6f6-4c18a309f63a" />

**Total time spent: 5 hours**

---
