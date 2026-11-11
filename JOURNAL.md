---
title: "uPen v2"
author: "TheAbsoluteMin"
description: "A Bluetooth smart pen that transforms handwritten notes into digital text."
created_at: "2026-09-12"
---

# Log 1: 9.12.2026 - 9.13.2026 - Schematics Remake
Timelapse <a href="https://lapse.hackclub.com/timelapse/KwB7Z5Aam9te">link</a>.

Welcome to a new chapter of uPen!

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

I designed the power multiplexer circuit so that my pen could seamlessly switch from battery to USB-C power. I was hoping to isolate the USB-C power from the MCU completely, but then I realized that I would need the MCU to turn on when I am coding.

In earlier projects, I used two diodes to create an OR gate, but I quickly learned that it was inefficient. Thus, I decided to test out an ideal diode design using a P-channel MOSFET.

<img width="1905" height="785" alt="image" src="https://github.com/user-attachments/assets/0e8e787b-5f54-48b2-ba49-7c354b1bc287" />

A key feature of this design was that it prevented the voltage drop across a normal diode for the battery.

Then, I began to incorporate the battery JST plug and a switch in order to turn the pen on and off. I added a voltage divider for ADC sensing, so I could easily monitor battery levels when using the pen.

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

# Log 5: 9.22.2026 - 9.23.2026 - Schematics Cleaning + PCB Start
Timelapse <a href="https://lapse.hackclub.com/timelapse/JFFThNqN29mq">link</a>.

As I was finishing up the schematics, I realized a major problem. Since I connected voltage dividers directly to the VBUS_5V input from the USB-C receptacle, power could accidentally back feed into the MCU pins before the 3V3 lines power up. This is called ghost powering, and it could prevent the MCU from properly powering on. Ideally, the 3V3 lines would power the MCU first so that it can handle the ADC sensing from the voltage dividers. In order to do this, I actually took some inspiration from the example schematic from the OLED datasheet!

Specifically, the OLED required 3V3 logic power before the higher voltage input, which powers the screen. Thus, the OLED datasheet used a high-side load switch in which the gate of the N-channel MOSFET controls whether or not the main power supply goes through the P-channel MOSFET. This would require 3V3 power to turn on before VBAT power can enter the OLED.

<img width="1917" height="793" alt="image" src="https://github.com/user-attachments/assets/dd32552a-b5ed-414a-ac75-c2ec92695be1" />

Similarly, I can use the same circuit to ensure that 3V3 turns on before allowing 5V to enter the system and power the voltage dividers.

<img width="1913" height="790" alt="image" src="https://github.com/user-attachments/assets/50d9c2e1-eb13-4140-ba9f-348607aeaec4" />

Finally, I began to work in the PCB editor. Since I was used to KiCad and it was my first time using EasyEDA Pro, I spent a bit time learning how to use the PCB editor.

<img width="1910" height="792" alt="image" src="https://github.com/user-attachments/assets/0a3c76e7-6fce-4bc5-b82e-057874e92762" />

Trying to keep my pen slim, I set my PCB border to a tiny width of around 10mm. I also did everything I could to pack the components as close to each other as possible.

<img width="1907" height="790" alt="image" src="https://github.com/user-attachments/assets/4df988f1-2a1e-44da-97df-21bfd5dfae6a" />
<img width="1912" height="795" alt="image" src="https://github.com/user-attachments/assets/d7620ba5-6473-49e1-89a0-9476fc73ee3a" />
<img width="1912" height="788" alt="image" src="https://github.com/user-attachments/assets/42a06359-85d8-4b83-aa20-0935e67f9745" />

**Total time spent: 4.15 hours**

---

# Log 6: 9.24.2026 - 9.25.2026 - PCB Placement
Timelapse <a href="https://lapse.hackclub.com/timelapse/i-GNwKqPbwk5">link</a>.

Placing all the parts in a compact layout is much harder than I thought. I had to measure the distances around each part to make sure that each component had enough manufacturing space.

<img width="1917" height="783" alt="image" src="https://github.com/user-attachments/assets/6ceaeff3-c5be-4354-84c3-a714c347e172" />

After a lot of clicking and dragging and rotating parts, I organized the power regulation blocks into a neat cluster to fill in as much space as possible.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/7db540df-3560-4d21-b4c9-9e1527a69b30" />

I had to place the OLED screen on the back side of the PCB because I ran out of room on the front side. Also, JLCPCB could not assemble that part through SMT assembly.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/2cabeb3f-086f-4815-8b2b-abb017e0312f" />

A neat thing about placing the screen on the back was that I could place its capacitors really close to it with vias.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/3900b2b0-f1e9-47d1-97ed-850ed860fb21" />

After placing more parts, I realized that the parts did not easily fit with each other, which made me a bit unhappy. The switch and JST plug connector really complicated the symmetry I had tried to maintain.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/53e86315-023e-4085-93a8-745d63cca6e1" />

After organizing PCB layout some more, I realized that I had more space than I thought! Thus, I decided to spread the ICs and passives out more to fill in the space.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/e397c85f-8c81-45de-8094-7327b65a6bcc" />

Finally, I started the massive MCU chip.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/3802f8ef-3f62-4b39-a983-29d3cb634867" />

It will be especially difficult to fit everything within a tiny PCB width as I already had trouble fitting the crystal oscillator below.

**Total time spent: 7 hours**

---

# Log 7: 9.26.2026 - Completed PCB Placement
Timelapse <a href="https://lapse.hackclub.com/timelapse/2V1YR9dmkcz1">link</a>.

Since the crystal oscillators would not easily fit on the top and bottom edges, I rotated the MCU, so they could fit on the left and right sides.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/a92fc69e-f789-47bc-863f-c56e5bf4d5cd" />

After quite a lot of work, I got a nice layout, and everything seemed to fit at the bottom, including the DC-DC power loop too.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/16d0a265-c90e-455b-b0b1-60336212aa99" />

On the other hand, the IMU sensor was easier to place as there was a lot of room at the end of the PCB.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/64640748-5589-446a-be96-d8d729798a7e" />

I then placed the buttons, which are going to be used to control the OLED screen menu, near the end of the PCB. I was surprised at how much extra space along the edges I had!

<img width="1911" height="792" alt="image" src="https://github.com/user-attachments/assets/846b1593-cd5f-401b-9f71-325e154d6580" />

**Total time spent: 4.3 hours**

---

# Log 8: 9.27.2026 - Begin Routing PCB
Timelapse <a href="https://lapse.hackclub.com/timelapse/yA78kWwk1_Hi">link</a>.

Today, I finally started to route my PCB! It took me a while to become acquainted to the net classes and design rules in EasyEDA Pro. In the past, when I used KiCad, I initially ignored net classes and rules since they were confusing to use. Whenever I tried to create them in the schematic editor, they would not transfer automatically over into the PCB editor. I ended up using a global clearance for simple PCBs and changing the PCB width whenever I wanted to in the settings.

While that method worked for a while, I would always have a million DRC errors! This time, I wanted to learn to use net classes correctly.

<img width="1910" height="786" alt="image" src="https://github.com/user-attachments/assets/feccdaf3-6b9e-4af1-a009-63c792ca3d8a" />

After some research and clicking around, I got the hang of it.

<img width="1917" height="793" alt="image" src="https://github.com/user-attachments/assets/e150df14-71df-453b-adca-656313e7afe5" />

A neat thing about EasyEDA Pro was that I could actually define each layer's height, which was especially helpful since I wanted a thin PCB for my pen.

<img width="1917" height="782" alt="image" src="https://github.com/user-attachments/assets/b6a83a5d-8dde-4601-bf1e-f92f4f4f52a6" />

I started with the USB-C data lines because those ones needed differential pairing. It took me a few tries to tune the lengths.

<img width="1912" height="792" alt="image" src="https://github.com/user-attachments/assets/6e34b7fb-50ca-45c9-ac15-013fbf36645a" />

Since I did not have enough room on the top layer (it's packed with SMD parts) to bring the data lines all the way to the CP2102N and then the MCU, I had to route on the bottom side of the PCB. I tried to create a GND copper pour on the inner layer to protect the data lines.

<img width="1916" height="792" alt="image" src="https://github.com/user-attachments/assets/0506ae00-cf89-414b-8f34-db44e8d8d34f" />

Then, I started routing the power lines.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/29fd7de2-b9c9-4e6d-a300-e83fd6458ba0" />

I am so grateful I spent so much time carefully planning where to place each part since there were a lot of connections for the power lines!

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/982d1e22-21eb-460b-b8ca-9c43bd4df29a" />

I had tried to pack all the resistors together in a neat pile, but I realized that I may have placed them too close to each other. I was running out of room for traces, and I needed a lot of vias!

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/a6821eef-6303-4873-8c14-3e127fce2250" />

It eventually became too difficult to route the resistors like that, so I decided to spread them out apart. I had a lot of space to use anyways.

<img width="1917" height="783" alt="image" src="https://github.com/user-attachments/assets/ff43a6f5-43d9-4cde-b395-af8f7df07bde" />

**Total time spent: 5.9 hours**

---

# Log 9: 9.28.2026 - 9.29.2026 - Power Routing
Timelapse <a href="https://lapse.hackclub.com/timelapse/BeiKYa8MbMa2">link</a>.

I did not realize how much of my PCB the power lines too up! I had to branch out a lot of different power lines from the main input capacitors. There was not much room since I stacked all the parts near each other!

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/469a8816-fee4-43cb-9b17-e2f870f749a4" />

Outside of the dense power maze of decoupling capacitors and MOSFETs were the big switch and JST plug connector. Fortunately, since I could not fit much around those big parts, there was a lot of breathing room for traces.

<img width="1917" height="788" alt="image" src="https://github.com/user-attachments/assets/f9fcbb0f-1b05-4fb1-a628-80742479224a" />

While I was routing the power lines, I unrouted the USB-C data lines so I could clearly see each connection. However, I somewhat regretted that since after checking my work, I realized that one of my bottom side traces was in the way of where the USB data lines were supposed to go.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/a29482e7-d25c-4e4e-bac1-6e70288a7dbf" />

I needed to adjust the bottom side traces so that there was enough room for the USB data lines.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/4155ee81-2ab0-4ff4-8488-b433fc0abe7a" />

Then, I rerouted the data lines.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/ee12c25e-b71d-45e9-8204-d86456e2c14e" />

It got a bit difficult as I finished up the final remaining connections for the power lines. According to my clearance rules, I practically ran out of room for vias!

<img width="1917" height="795" alt="image" src="https://github.com/user-attachments/assets/95ed82cb-d730-4b2c-b3aa-a4a299631dbd" />

After a lot of pushing traces and vias around to fit everything, I began working on the battery charging circuit.

<img width="1917" height="797" alt="image" src="https://github.com/user-attachments/assets/3a0df747-4e6c-4b2f-bb63-44eeb7f9398a" />
<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/b3e212b6-4824-4797-a042-cc4d9c39fb88" />
<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/2e9e2845-3818-413b-a3b6-22ed403dde6f" />

Then, I quickly routed the passives for the CP2102N.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/c76336df-bf7c-479e-9146-103ada1abdb6" />
<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/fcf43535-c319-4e16-840b-2514188d1436" />

There was not much room, so I had to rely on vias to get to the right places.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/0e92545d-7c34-4a37-b9a7-873034599839" />

Finally, I needed connect the 3V3 lines. Since I wanted to use a double inner GND plane (full GND plane on Inner 1 and mostly GND plane on Inner 2) for the signals on the top and bottom layers, I decided to just loop 3V3 around with a large trace. Moreover, I was already managing many different power lines from 3V3 to 4.2V to 5V (don't forget the additional 4.2V and 5V lines delayed by MOSFETs, which ensure correct power-on timing), so I did not use a copper pour.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/ae000bf4-bb7d-4a59-8e0a-1bb570130e36" />
<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/f618d9eb-e7da-43a3-b86a-1afed9b0390b" />
<img width="1917" height="796" alt="image" src="https://github.com/user-attachments/assets/f1ab19c7-c3f9-4cf5-8248-61b1eb25e318" />

**Total time spent: 7.2 hours**

---

# Log 10: 9.30.2026 - 10.1.2026 - Finishing Half the Board!
Timelapse <a href="https://lapse.hackclub.com/timelapse/qV2l_s-JlYOf">link</a>.

I realized that the OLED datasheet did not specify a decoupling capacitor for its VBAT (battery) input (pin 5), so I decided to quickly add one.

<img width="1917" height="796" alt="image" src="https://github.com/user-attachments/assets/df8a5e89-13dc-4055-b083-d97f82ddbd20" />
<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/91e44ae6-4c02-43ef-85d6-0a608235cafd" />

I took a few tries to route it since I did not have a lot of room with all those vias near the OLED.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/9abb21a4-498e-4f9d-87c2-8b8cf5edf1c8" />

Clearly that last attempt was a bit strange since the top layer curved around just to switch to the bottom layer, so I decided to put the capacitor and via on the other side. It was much smoother now.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/7213709a-d2e2-44dd-b6d9-5b2356c86de9" />

Fortunately, the local routing for the OLED was much simpler. I was able to use short traces for its passives, like the OLED charge pump capacitors at the bottom of the OLED pins.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/a0382a70-a271-469b-bbba-7f2ad7221744" />

Looking for any other missing connections, I realized that I needed to connect the ADC voltage dividers. I wished I had placed them closer to the MCU rather than in conveniently far places just to fill in dead space.

<img width="1917" height="793" alt="image" src="https://github.com/user-attachments/assets/87760b6d-5e1f-4445-9cce-dffd70ba6612" />

Especially this CHRG ADC line (it signals whether or not the battery is charging) barely fit between other traces!

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/b988de95-fe5d-4b4a-8f4c-ad58d2a6bf37" />

The USB_DETECT ADC line (it checks whether or not USB-C power is plugged in) also took some tries in order to fit while keeping appropriate clearances from the USB-C data lines.

<img width="1916" height="788" alt="image" src="https://github.com/user-attachments/assets/f8a52156-917f-4899-be32-e38724856a9d" />

I also realized that I placed the OLED MOSFET control (it turns the OLED VBAT power for the screen on and off) so far away from the MCU (which sends the on and off signals to the MOSFET), so I needed to use quite a long trace.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/de1ca24c-12d8-40ec-882c-da89ea85df43" />
<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/52cd2f7c-8e00-4725-80c8-830ad81335a1" />
<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/f202ce22-c536-4a66-9e26-73882da4ca1f" />

Moving on to the MCU, I decided to route its crystals. The first one was symmetrical and simple to route, thankfully.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/0df4b362-de93-4580-97b8-f71e6b6212db" />

I then decided to attempt the MCU's power regulation circuits (DCC pin 47 and DEC4 pin 46).

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/1a7f03a1-689d-4067-86b0-9c39ab5857f4" />

I needed to reorganize them so that the traces had enough clearances from the component pads.

<img width="1917" height="797" alt="image" src="https://github.com/user-attachments/assets/983d30e8-f046-4ca8-b49b-d5ff5adfc8d1" />

The connections seem relatively simple, but the overall length was a bit too long. Next time, I will try to optimize that.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/3fbc6ea1-5173-46cf-b890-3b2f06c0a7ef" />

**Total time spent: 5 hours**

---

# Log 11: 10.2.2026 - Routing MCU Attempt 2
Timelapse <a href="https://lapse.hackclub.com/timelapse/O_HBjuYZbKp0">link</a>.

Seeing that I was space constrained at the bottom, I decided to undo all my routing in order to rotate the MCU.

<img width="1917" height="782" alt="image" src="https://github.com/user-attachments/assets/43bbd911-44ef-44c9-8e8d-8d0876f67836" />
<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/fefcc29e-5be5-4bcd-ae85-72e70678c71b" />

With the chip rotated, the crystal oscillators would be on the bottom while MCU power regulation parts could be on the sides, where I would have have enough room to route tighter loops.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/1b72e2a0-034d-48e7-a33c-bf08d10bfc43" />

To save even more room, I tried to aggressively pack the decoupling capacitors next to the MCU's edge. I was amazed at how close I could place it.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/01c67a28-660e-4be4-a01e-3aa30c1884d3" />
<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/75a89ccb-7419-4666-aa0e-4558755a161e" />

With the MCU's current orientation, I realized that the Bluetooth antenna pins were on the right side of the MCU chip. This was not ideal since I wanted the antenna to be far away from all the noisy lines and main power regulation blocks (which were on the right half of the PCB). Thus, I decided to rotate the entire MCU chip again so that the antenna could be on the left side of the PCB, where it is much quieter.

Here you can see that the antenna is on pin 31 of the MCU.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/b75e22a7-70de-4ed2-8a3b-13ac3c4b42d6" />

My current orientation had pin 31 on the top, but to the left of the pin was a decoupling capacitor, which blocked the way for an antenna trace to the left.

<img width="1917" height="795" alt="image" src="https://github.com/user-attachments/assets/411d0faf-b2b2-46bc-8e91-cafb085f83c7" />

Now that I rotated it, the antenna trace can easily go to the left and along the edge.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/313fbe22-722e-475e-aff8-633f77e1da88" />

**Total time spent: 1.2 hours**

---

# Log 12: 10.5.2026 - 10.7.2026 - MCU Optimization
Timelapse <a href="https://lapse.hackclub.com/timelapse/rNpn5BO1Xkc2">link</a>.

Now that the antenna was on the bottom and could loop left (there were no obstructing passive parts in the way), I could place the antenna passives themselves.

<img width="1918" height="790" alt="image" src="https://github.com/user-attachments/assets/f94d26b5-fef6-40e2-b517-eb89d31072e9" />

Fortunately, the big crystal oscillator fit on the right side along the bottom of the MCU.

<img width="1919" height="788" alt="image" src="https://github.com/user-attachments/assets/f6a6cb87-71de-4cb0-9455-61d44348120b" />

I realized that I needed to connect a capacitor to each of the oscillator lines, so I had to make some room for them. For the first connection, I could easily route a trace to the oscillator pin 3 and then another short one to the capacitor outside the oscillator chip. However, I did not have enough space to do the same for the oscillator pin 1, so I used an inwards loop, which I have to admit was a bit unnatural.

<img width="1919" height="786" alt="image" src="https://github.com/user-attachments/assets/94c06139-76e8-4301-b223-ad24860cf371" />

Tuning the trace lengths was a bit hard since EasyEDA calculates the total lengths of the traces, even when parts of them are inside the pads. Thus, I had to try my best to estimate how much distance there actually was between each pad.

<img width="1919" height="795" alt="image" src="https://github.com/user-attachments/assets/e59a2e50-a283-4984-8233-5fd06c0f96ca" />

Unfortunately, I had overlooked the decoupling 3V3 capacitor that was above the oscillator, and I realized that I had barely any room to complete the trace according to my clearance rules.

<img width="1917" height="789" alt="image" src="https://github.com/user-attachments/assets/311355b6-b32d-4d03-a041-ec06c3a350c4" />
<img width="1919" height="794" alt="image" src="https://github.com/user-attachments/assets/3b43ed3b-f7df-4d1f-a501-a1a980055cc8" />

To solve that, I simply made the trace width smaller for a bit.

<img width="1917" height="796" alt="image" src="https://github.com/user-attachments/assets/eb2b019d-095d-4822-8ace-96c1ddc711cb" />

Fortunately, since I now had a lot of room to route the MCU's power regulation blocks, I could tighten the inductor loops.

<img width="1919" height="795" alt="image" src="https://github.com/user-attachments/assets/7dc29f63-bc8e-4d25-92c5-49c51c952cfd" />
<img width="1919" height="794" alt="image" src="https://github.com/user-attachments/assets/1dfab72a-93ce-460b-b72c-b50f0e842c8b" />

After moving the inductors and capacitors around, I ended up with a neat, short loop.

<img width="1919" height="797" alt="image" src="https://github.com/user-attachments/assets/c8a32e8f-4f53-4f6d-85e3-e820b0758171" />

Then, I began to place the GND escape vias, but I realized I that many of them did not fit.

<img width="1918" height="794" alt="image" src="https://github.com/user-attachments/assets/29d844f4-5abd-4e9c-81e9-faf0d9989c73" />

As a result, I spent some more time pushing traces around until there was enough room for the GND vias.

<img width="1918" height="787" alt="image" src="https://github.com/user-attachments/assets/16f5e377-4e3f-45cc-8e52-e0f83d39fc09" />
<img width="1907" height="786" alt="image" src="https://github.com/user-attachments/assets/c4140530-dfd0-41bf-8336-f3bec79b0cb0" />

In order to keep the routing as clean as possible for the antenna, I orientated the capacitors to stand vertically while keeping the 50 ohms single-ended impedance Bluetooth trace along the bottom edge of the PCB.

<img width="1912" height="797" alt="image" src="https://github.com/user-attachments/assets/835b1e50-f503-4a04-873e-267e5e241298" />

While routing the 50 ohms line, I had to shorten the width for a tiny bit in order to satisfy my clearance rules.

<img width="1918" height="789" alt="image" src="https://github.com/user-attachments/assets/c58c8675-647d-4ed3-b4fb-ee62accb81df" />

It was my first time using curved traces, so it was cool. I had only seen 45 or 90 degree traces!

<img width="1918" height="796" alt="image" src="https://github.com/user-attachments/assets/62b971fb-3e1e-47eb-97dc-5c1abbb390f8" />

Working on the FLASH memory chip was not too difficult since I switched to standard SPI instead of QSPI since I did not need fast read and write times.

<img width="1918" height="787" alt="image" src="https://github.com/user-attachments/assets/a1e3f4ce-5bd6-4529-ad8e-6954ef065d90" />
<img width="1917" height="793" alt="image" src="https://github.com/user-attachments/assets/baa6cda8-6fb3-4c8b-819c-4612be678b79" />

Another reason I switched was to free up some more pins on the MCU.

<img width="1919" height="786" alt="image" src="https://github.com/user-attachments/assets/447361ed-77f3-4a68-ba17-667eadd80f1e" />

Since I did not have much room to route on the top layer, I had to use the bottom layer to cut underneath the MCU's big GND pad. Fortunately, I still had a solid GND plane on Inner 1 layer, and I will indeed add vias.

<img width="1914" height="796" alt="image" src="https://github.com/user-attachments/assets/6ff0cd7b-5c47-4a0d-b7a7-e12f67d6ba51" />

I was still amazed at how much space the 4 SPI lines of the FLASH chip took up underneath the MCU given the clearance rules.

<img width="1919" height="790" alt="image" src="https://github.com/user-attachments/assets/91f26161-a0d5-44b1-acf2-266a7f58fae8" />

I decided to place the analog ADC voltage dividers closer to the MCU so that I could reduce noise. Space was sparse, so the closest I could place them were behind the FLASH memory chip.

<img width="1914" height="790" alt="image" src="https://github.com/user-attachments/assets/25ef7fa0-0697-4877-a101-b3161adce869" />
<img width="1919" height="790" alt="image" src="https://github.com/user-attachments/assets/d256b6d1-6949-422f-af2c-0745e67eaa71" />

**Total time spent: 6.4 hours**

---
