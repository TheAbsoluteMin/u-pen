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

# Log 13: 10.8.2026 - 10.9.2026 - Finalizing PCB
Timelapse <a href="https://lapse.hackclub.com/timelapse/OxuxDo3WjiVd">link</a>.

I forgot to place 3V3 (VDD_NRF) vias for all the decoupling capacitors of the MCU! This was not an easy fix since I had already packed all the passives and traces too close to each other, leaving almost no room for vias.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/51becf21-b53a-44e2-93c2-e8c795d33501" />

After moving the bottom layer traces up and out of the way, I made enough room for a via!

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/5854b968-22e8-433a-b9aa-153b64bf140b" />

Apparantly, I still did not connect the RXD and TXD traces to the MCU yet, and they were still on the other end of the board, far away from the MCU! I tried my best to stay on the top or bottom layer. 

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/8bd32cf8-3333-49b7-b837-5ba216dcccac" />
<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/b741a9b8-d42a-4c47-a4dc-4e877fa2537e" />

Since I practically ran out of room, I had to switch to the Inner 2 layer to get across the MCU to the correct pins.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/f9d4fec5-9df9-41fe-98fc-285007caac22" />
<img width="1916" height="780" alt="image" src="https://github.com/user-attachments/assets/d6e0afbc-bf70-452f-aaef-3ebfc305a5a0" />

It was especially crowded on the left side of the MCU since the antenna keep out zone was near it. I ran into another space issue because I also needed room for a 3V3 (VDD_NRF) via as well. The problem was that it was near the RXD connection!

<img width="1913" height="792" alt="image" src="https://github.com/user-attachments/assets/56df6108-bd77-486c-88a2-c805ac16c5de" />

Thus, I had to move around the pin connections to places where I had more space.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/12459109-f685-4925-9d25-25492f642160" />

I ended up moving RXD to the top of the MCU chip, where it was less crowded.

<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/0e01b9f6-530c-4c10-bcd4-9eb7edf7e4b9" />

You would never guess what I found on the right side of the MCU chip. Another decoupling capacitor that did not have a 3V3 via yet! No! I had to go back to the schematics to move the data connections up so I had enough room to place the 3V3 via.

<img width="1917" height="783" alt="image" src="https://github.com/user-attachments/assets/9e0a2958-ea7b-4112-a473-6f7d485772b2" />

I sadly got rid of a button in order to do so, but I needed to prioritize the decoupling capacitor connection.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/6fe281d1-03cc-4c79-9c9b-51bfd67cf7bd" />

Now that all the decoupling capacitors had vias for 3V3, I made sure that they all connected to the main 3V3 branch on the Inner 2 plane.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/27272a08-ac5d-48bc-9595-2f6b0571f125" />
<img width="1917" height="795" alt="image" src="https://github.com/user-attachments/assets/e1168982-24fa-456f-879d-0d4c81c96d5e" />
<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/551204d7-4d8f-4b00-9552-fc055664bbca" />
<img width="1917" height="797" alt="image" src="https://github.com/user-attachments/assets/3db79a9b-b7bb-4ae8-ad56-702496e5cc2e" />

Since the SWD flashing pins (SWDCLK and SWDIO) were conveniently near the antenna pin, I practically had no space to route them far out.

<img width="588" height="456" alt="image" src="https://github.com/user-attachments/assets/a0c8210e-f9a0-4f92-9333-ec8f3961aeb6" />

Thus, I utilized exposed vias.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/5657474e-1b08-4f18-851f-1854fdbd0811" />

I had test points on those SWD pins from the schematic (which the vias now replaced), so I hid them by shrinking their size and putting them inside the pad.

<img width="1917" height="798" alt="image" src="https://github.com/user-attachments/assets/165aebe5-56e3-4419-8c77-37ddeec78d56" />

Finally, I finished routing the entire MCU!!! I quickly moved on to the IMU, which was sitting at the tip of the board. With so much extra space, here it was easy to route the connections. Still, I had to be careful to route around the QVAR blocks since they contain exposed copper pads for capacitive sensing (to detect if the smart pen touches paper or not).

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/144f2031-b103-4e89-b964-7e92c3dadae2" />

In order to protect the SDA and SCL lines from interference from the exposed copper pads, I isolated the QVAR blocks with GND traces.

<img width="1916" height="790" alt="image" src="https://github.com/user-attachments/assets/d5c5b9be-fe92-45f9-bc4d-9d8e43b5c0f9" />

Spacing was tight as I also had to separate the QVAR sensing lines from each other as well with another GND trace.

<img width="1917" height="795" alt="image" src="https://github.com/user-attachments/assets/ad117821-36a5-48f1-9b91-ced3ddf7dc0c" />

After I resolved that, I realized that I needed to route the IMU interrupt line to the MCU! Not again! I was not sure how I could get that trace across to the MCU pin. It was also dangerously close to the Bluetooth antenna!

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/a3db1ead-f7c1-4894-9853-dac13ff26044" />

I eventually got it, but I immediately found another problem that needed attention. I did not route the SDA and SCL lines for the OLED yet! To make things more difficult, there was no room for traces!

<img width="1912" height="786" alt="image" src="https://github.com/user-attachments/assets/0c872a4b-4660-4a58-abf1-dd8d1e67909d" />

Even if I managed to break out vias, there was no more room across the MCU (the OLED is placed to the right of the MCU) since I already used all three layers (except the GND plane) for data lines! Thus, I decided that I would break out vias as big as possible and expose them to be soldered with physical wires.

<img width="1912" height="780" alt="image" src="https://github.com/user-attachments/assets/d07a0497-4807-45ff-be37-cbdac079a5e1" />

I fortunately had just enough room for the exposed vias.

<img width="1917" height="795" alt="image" src="https://github.com/user-attachments/assets/fb649c16-2b47-41fe-be8c-cb7f78661426" />

I filled the GND copper plane, and I was surprised that it reached all the GND vias despite all the data vias I used!

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/0593d403-c44e-414c-8831-94396d1c4971" />

I order to prevent bottlenecks, I filled in as much of the Inner Layer 2 with a GND copper pour as well. Of course, the Design Rules Checker was not happy with me.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/9ad087d6-ff0b-41a5-9af4-2d32d8767085" />

With some fixes, I cleared all the errors (besides the missing SDA and SCL connections for the OLED, but that is intentional and will be resolved by soldering the physical wires)!

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/116d12f7-90fb-460c-a84b-a0e2acb4daa3" />

The PCB is practically finished!!!

**Total time spent: 5.2 hours**

---

# Log 14: 10.11.2026 - PCB Order
Timelapse <a href="https://lapse.hackclub.com/timelapse/1KCZ31A6TQS4">link</a>.

Today, I finally began ordering my PCB! All was well until I clicked on the component selector page on the PCBA order page... The main MCU (NRF52840) version (QFN-48) that I had been using this whole time was out of stock!

<img width="1916" height="786" alt="image" src="https://github.com/user-attachments/assets/01c76e4b-761d-425b-bb9a-395c65651ff3" />
<img width="1891" height="961" alt="image" src="https://github.com/user-attachments/assets/ed8688c8-4089-4b9b-8cd6-6a1684ce79d9" />

Fortunately, after some research, I found a drop-in replacement that I could use instead! That meant I did not have to wait for my part to restock!

<img width="1902" height="966" alt="image" src="https://github.com/user-attachments/assets/87f7463e-26f4-4d2a-b5f0-657ab3421701" />

The main battery switch that I used was also out of stock, and it was a little more difficult to find drop-in replacements. I opened up a new project to compare different footprints to see if I needed to change my own PCB.

<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/3edadd9f-df5b-42d4-89b5-aea30315afc7" />
<img width="1917" height="787" alt="image" src="https://github.com/user-attachments/assets/ee3d540f-bb8c-4f2c-a472-ba4984cb7ce8" />

Sadly, the anchor holes and pads were a little off. Thus, I quickly decided to simply replace the entire switch on my PCB since it only required minimal rerouting.

<img width="1917" height="791" alt="image" src="https://github.com/user-attachments/assets/533c8c19-910e-4ee9-a302-c76c40dabfa9" />
<img width="1917" height="790" alt="image" src="https://github.com/user-attachments/assets/8210bed5-a0b2-4c1c-b3a4-51261c141905" />

Finally, I moved on to checking the component placing on the PCB. It took me some time to verify orientations as I had to switch back and forth between my PCB and the order page.

<img width="1917" height="785" alt="image" src="https://github.com/user-attachments/assets/443ceff8-9d21-4cf3-9ab0-441818e94cc6" />
<img width="1917" height="788" alt="image" src="https://github.com/user-attachments/assets/cc8f828e-ba26-4762-af8e-fe1214c912ef" />

I was surprised that there was yet another problem with the MCU! It was upside down, so I flipped it over.

<img width="1917" height="792" alt="image" src="https://github.com/user-attachments/assets/6625a710-0035-443d-9788-a5635b2fd97e" />
<img width="1917" height="733" alt="image" src="https://github.com/user-attachments/assets/95cedcef-7cb6-44ab-aba0-a830580c8f39" />

When I got to the final checkout page, I was shocked at the high price!

<img width="1917" height="796" alt="image" src="https://github.com/user-attachments/assets/e4fdf53d-bde3-428d-81f1-259457964b56" />

I think I will have to lower the PCBA count to 2 to save some money.

**Total time spent: 1.6 hours**

---

# Log 15: 11.6.2026 - Starting CAD Case
Timelapse <a href="https://lapse.hackclub.com/timelapse/9zl_P-fJbSvP">link</a>.

It's been almost a month since I last worked on this project. I had been busy with schoolwork, but I am finally glad to be back to finally finish uPen v2!!! Since the PCB is completed, I began working on the CAD case. In order to do so, I first downloaded the STEP file of the PCB.

<img width="1802" height="1007" alt="image" src="https://github.com/user-attachments/assets/ba972d27-1210-4072-a630-012004dbf87c" />
<img width="1805" height="996" alt="image" src="https://github.com/user-attachments/assets/ad14210a-4026-479e-a75b-f2c7577043c2" />

I imported it into Onshape, and it was mostly successful. I'm guessing some parts did not transfer, like the JST plug connector (JLCPCB seemed to not have a 3D model saved for it).

<img width="1798" height="1006" alt="image" src="https://github.com/user-attachments/assets/d1c9087a-a85e-4899-9327-4d7eef25577a" />

Normally, I would create the CAD case directly in the PCB part file since it I could do it in context. Seeing the PCB helped me to see dimensions and clearances. However, with some research, I learned that my current method was unconventional on Onshape. Thus, I decided to try the assembly feature.

<img width="1808" height="987" alt="image" src="https://github.com/user-attachments/assets/845c03a5-7848-483c-b1c3-3a0ed36a1a04" />

Fortunately, there was an "edit in context" option in the assembly tab, so I was still able to design around the PCB!

<img width="1806" height="987" alt="image" src="https://github.com/user-attachments/assets/7cd00493-b8cc-4aa6-ad50-1e5d9c0002f2" />

Honestly, I liked this feature as it allowed me to change the transparency of the PCB, which helps to look inside the case to see if the PCB overlaps or fits well. I first started with a nice simple rectangular prism.

<img width="1807" height="992" alt="image" src="https://github.com/user-attachments/assets/a2c1ddcd-fdbf-4721-b033-924d5e9c9675" />

Then, I added a fillet on all four corners to create a sleek and comfortable writing grip for the pen.

<img width="1800" height="986" alt="image" src="https://github.com/user-attachments/assets/0fd1ff1e-ccd5-4bf9-8fd0-3874c4bbba49" />

I wanted to make the OLED screen sit flush with the casing, but the best I could do was approximate since the OLED screen may end up sitting a little taller than the 3D model. I would be hand soldering the screen and gluing it down with tape (which may add some thickness). To accommodate this, I added a little buffer by elevating the case a bit.

<img width="1802" height="987" alt="image" src="https://github.com/user-attachments/assets/5692657d-87be-464f-8a75-a0265e94ce4e" />

In order to make the inside hollow for the PCB to fit inside, I created a similar rounded box on the inside.

<img width="1802" height="986" alt="image" src="https://github.com/user-attachments/assets/82817bfb-5f75-46d6-96db-4431f3032f14" />
<img width="1802" height="988" alt="image" src="https://github.com/user-attachments/assets/1f407a1f-946a-455d-85c7-cd2e2e1e2406" />

With a quick extrusion, the inside was hollowed.

<img width="1808" height="990" alt="image" src="https://github.com/user-attachments/assets/49fd88fe-92c2-4fe0-8156-63f22c80bd36" />

In order to make a snug hole for the USB-C receptacle, I used its outline in order to expand it a little, which would be used as a guide to make a hole in the case.

<img width="1806" height="993" alt="image" src="https://github.com/user-attachments/assets/aee9fadb-bb2c-4607-ba02-8229e734f7be" />
<img width="1805" height="987" alt="image" src="https://github.com/user-attachments/assets/4b802059-0765-4cf6-9014-a8017e855393" />
<img width="1807" height="986" alt="image" src="https://github.com/user-attachments/assets/0889e92a-3153-48be-9e11-d8c79bb68418" />

With a fillet, I rounded the back end of the pen to give it a smooth look.

<img width="1806" height="995" alt="image" src="https://github.com/user-attachments/assets/f347af9f-fbbb-4412-b52e-cffb3c780368" />

I realized that I actually had too much Z height, so I did not actually need a thin PCB nor a small switch. Instead of changing the PCB, I decided to have the case adapt to it. I began working on an extension piece for the switch handle.

<img width="1806" height="987" alt="image" src="https://github.com/user-attachments/assets/86b36954-1f09-4a99-aa9b-abb79b9dd58e" />
<img width="1805" height="992" alt="image" src="https://github.com/user-attachments/assets/b25f98ab-40cf-4d70-a3f2-89a8e79d15af" />

I did not really like that the switch handle always left a huge hole whenever you moved it on or off.

<img width="1802" height="997" alt="image" src="https://github.com/user-attachments/assets/fac07d34-39d4-489c-8296-90b39bc3ff64" />

In order to fix this, I created a cover that would slide with the switch handle underneath the case.

<img width="1810" height="1002" alt="image" src="https://github.com/user-attachments/assets/ed05273d-9e31-4a4d-9920-b520137799e1" />
<img width="1802" height="1000" alt="image" src="https://github.com/user-attachments/assets/f6d64bbb-b278-4a37-a43f-dab37a0ed3fa" />

While it looked clean, I had to create a hole next to the switch handle because there was an LED next to it (the LED shows whether or not the pen is charging).

<img width="1802" height="991" alt="image" src="https://github.com/user-attachments/assets/6fd332c7-e28f-44dd-bce9-8ab309752519" />

The RESET and menu buttons also needed to be extended so that the user can press them easily, so I made a little extension for them.

<img width="1808" height="988" alt="image" src="https://github.com/user-attachments/assets/7d7fb613-b0c1-4e44-a62c-06dd30cdc5a6" />
<img width="1803" height="995" alt="image" src="https://github.com/user-attachments/assets/1e6d54e5-35d0-4a7b-9d02-a7d67c8579b7" />

In order to help me remember when the switch is on or off, I added a little "OFF" sign on the switch.

<img width="1802" height="983" alt="image" src="https://github.com/user-attachments/assets/9a80f090-03a9-4e1d-af16-f6d5a7898194" />
<img width="1802" height="987" alt="image" src="https://github.com/user-attachments/assets/4e55f4b6-bbe6-433b-b38d-bde5081288be" />

I also needed to differentiate between the two buttons, so I added a little circle on the menu button.

<img width="1801" height="977" alt="image" src="https://github.com/user-attachments/assets/9e0bfcd6-a7d0-4f01-bb5a-304a2124a6ff" />

I then tried to use the Loft tool to create a cone for the pen's tip, but it wouldn't work!

<img width="1802" height="992" alt="image" src="https://github.com/user-attachments/assets/1eb9c4cd-55ff-4951-9e99-b7164e046fda" />

After looking through some videos, I realized the reason why Loft didn't work! Apparently, it did not work well with hollow objects.

<img width="1742" height="976" alt="image" src="https://github.com/user-attachments/assets/7de71bb9-0fb4-4b28-99ea-c02e04d040af" />

I filled in the surfaces, and it finally created a cone that smoothly transitioned from the rounded square to the circle tip.

<img width="1802" height="987" alt="image" src="https://github.com/user-attachments/assets/83904e05-63e9-43a3-b7cc-87efd2741bdd" />

Since I was not sure how the pen ink refill would fit inside the pen case's tip, I decided to make the cone attachable.

<img width="1805" height="980" alt="image" src="https://github.com/user-attachments/assets/0eb6bc37-a1b3-4f6d-a76c-201bbd2b1504" />
<img width="1807" height="986" alt="image" src="https://github.com/user-attachments/assets/6e52d087-33e4-4621-a850-d335d7f0bf1e" />

Now, I would not have to reprint the entire case if the pen ink refill did not fit.

**Total time spent: 4.3 hours**

---

# Log 16: 11.7.2026 - Finishing CAD Case + Update GitHub
Timelapse <a href="https://lapse.hackclub.com/timelapse/MdzBlRJNPXWN">link</a>.

I realized that the buttons and switch were too small to press on a 12.5mm thick pen, so I increased their size.

<img width="1806" height="987" alt="image" src="https://github.com/user-attachments/assets/cbed24fe-0b8e-4906-b149-bf5d9d130ee6" />
<img width="1806" height="997" alt="image" src="https://github.com/user-attachments/assets/3939aa4b-deba-4194-b856-42b7834705c6" />

Now, the user interface was much more user friendly.

<img width="1796" height="987" alt="image" src="https://github.com/user-attachments/assets/350aa1cb-5647-46d9-8d05-e959288dbbcd" />

Now that the pen case was complete, I needed to split it in half so that it can be easily 3D printed. To do this, I first duplicated the case.

<img width="1797" height="992" alt="image" src="https://github.com/user-attachments/assets/25521bdb-24d3-44a3-b810-de5e9dfb51df" />

Then, I cut each one accordingly with extrusions.

<img width="1802" height="991" alt="image" src="https://github.com/user-attachments/assets/5b7ee31e-ab2f-4b4b-9736-01642be8146c" />
<img width="1808" height="992" alt="image" src="https://github.com/user-attachments/assets/a62c134b-903b-42b7-bcdd-a5ae465514bd" />

In order for the two case parts to fit together, I included flaps at the front and end of the pen.

<img width="1803" height="996" alt="image" src="https://github.com/user-attachments/assets/558027fc-8579-41d5-be44-928db6a40ea6" />
<img width="1803" height="997" alt="image" src="https://github.com/user-attachments/assets/7437654b-ad74-4d8f-940d-b980cb84b8c6" />

I added another flap in the middle for extra friction, so the top case would not fall out accidentally.

<img width="1803" height="1000" alt="image" src="https://github.com/user-attachments/assets/cddec3ba-5fc0-4db8-b20f-ad062f9cddb8" />

With some nice coloring, the entire pen case came together.

<img width="1801" height="987" alt="image" src="https://github.com/user-attachments/assets/7f725fc6-34e6-47b2-8cef-14635cb2eabb" />
<img width="1802" height="987" alt="image" src="https://github.com/user-attachments/assets/29fe830f-56c3-46e7-bb7f-e5aa3f13fff4" />

Now that the case was complete, I began exporting the CAD files for my GitHub repository.

<img width="1803" height="988" alt="image" src="https://github.com/user-attachments/assets/9df09692-815b-4bc9-acfa-da09ad36ab16" />

I worked on editing the README.md with the PCB and CAD files.

<img width="1802" height="988" alt="image" src="https://github.com/user-attachments/assets/e891eede-ec9f-40e1-a930-670aecb64b1d" />

It took some time to compile all my screenshots and organize all the information in one place. Eventually, after a lot of typing, I finished.

<img width="1787" height="980" alt="image" src="https://github.com/user-attachments/assets/42f721b3-0c98-40ad-9ded-fb626ebf140b" />

I then organized my folders in the GitHub repository in VSCode in order to separate the version 1 and version 2 files.

<img width="1805" height="977" alt="image" src="https://github.com/user-attachments/assets/51b8be8d-ee80-477b-a672-8c44d2bbe229" />
<img width="1802" height="988" alt="image" src="https://github.com/user-attachments/assets/503b3878-9880-4d9f-a7f0-f14756090dc5" />

My GitHub repository is finally all cleaned up!

<img width="1798" height="997" alt="image" src="https://github.com/user-attachments/assets/3f2e7f83-7aa6-4673-8215-84ba42ca5bdd" />

**Total time spent: 4 hours**

---

# Log 17: 11.11.2026 - Coding!
Coding hours tracked on Hackatime.

Today, I worked on the basic firmware for my pen, so I could test its basic functions when I receive the board. I first needed to install the Hackatime tracker (to track my coding time), but for some reason my extensions marketplace tab was not working! It would not load anything no matter what I did.

<img width="348" height="142" alt="image" src="https://github.com/user-attachments/assets/ea092b49-2ecf-42c5-b2be-82ceeb003668" />

In order to get around this problem, I downloaded the VSIX file from the Open VSX Registry.

<img width="1912" height="1058" alt="image" src="https://github.com/user-attachments/assets/8381ae6e-bb3e-4124-86b8-47f0db5f56d3" />

Now, I could begin writing the firmware... Instead of just writing a single code file, I decided to use the PlatformIO IDE extension so I could later use it to flash firmware on VSCode. Again, the extensions marketplace in VSCode would not load, so I downloaded the VSIX file from GitHub. I also grabbed the C/C++ extension as well, which would help me write my firmware.

<img width="807" height="107" alt="image" src="https://github.com/user-attachments/assets/550982a3-2443-410d-8b84-a91139ed6011" />

Finally, I got the extensions installed!

<img width="425" height="485" alt="image" src="https://github.com/user-attachments/assets/55baa7c1-eaae-4ad8-9cf9-3d2ecef20db3" />

I had been used to Arduino IDE, so it took me some time to get accustomed to how PlatformIO IDE worked. For example, I needed to put the main code file inside a folder called src, and I needed to set up a project file (platformio.ini).

<img width="1150" height="735" alt="image" src="https://github.com/user-attachments/assets/9162b684-a135-443a-afd4-235181441094" />

Now, I could begin coding the logic. I have not used external Flash memory chips before, so I included a little script to make sure that mine works properly.

<img width="823" height="587" alt="image" src="https://github.com/user-attachments/assets/d028b3ab-b35d-4092-8fcf-d2312fc84f9c" />

Then, I drafted the code to save characters into the Flash memory chip.

<img width="972" height="530" alt="image" src="https://github.com/user-attachments/assets/9fdb20a7-df2b-4545-a89b-7f775ca5495a" />

For the core logic, the pen will rely on the QVAR function of the IMU to separate each handwritten stroke and character. Specifically, by using a set threshold, it senses a change in static electricity when the pen touches the paper and lifts up as you write each character.

<img width="1307" height="328" alt="image" src="https://github.com/user-attachments/assets/359dca67-ed3e-4bf7-bc2c-c31c8d9fbcb6" />
<img width="1337" height="240" alt="image" src="https://github.com/user-attachments/assets/89f52d9c-2029-455e-99a3-a74c6ce4afd1" />

As the user writes each character, the pen tracks your handwriting motions.

<img width="1312" height="152" alt="image" src="https://github.com/user-attachments/assets/e1c87d04-6536-4e3e-9d8a-abdacdd42a21" />

In order to reduce reliance on a button to write, I included this short function that will automatically detect when you start writing, which makes using the pen more intuitive.

<img width="923" height="125" alt="image" src="https://github.com/user-attachments/assets/f482305e-07a9-46de-9072-12787124eeec" />

I can't wait to start testing out the code once my PCB arrives!

Until then,
TheAbsoluteMin

**Total time spent: 2.4 hours**

---
