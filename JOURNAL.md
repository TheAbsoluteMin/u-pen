---
title: "uPen"
author: "TheAbsoluteMin"
description: "A Wi-Fi-enabled smart pencil that instantly captures and solves math problems."
created_at: "2026-06-21"
---

# uPen Development Log

## Log 1: June 21, 2026 - Schematics - 2 hours
Timelapse <a href="https://lapse.hackclub.com/timelapse/9_8VnrNF68hq">link</a>.

### Inspiration:
The core inspiration behind Insta-Form (now renamed as uPen) was to bridge the gap between traditional handwriting and instant digital problem-solving. While apps like Photomath exist on smartphones, switching back and forth between a screen and scratch paper disrupts the natural flow of learning and checking math work. I wanted to build a seamless quick tool that lets students or engineers keep their pen to paper while getting instant feedback.

Thus, I am excited to share the first log for Insta-Form (uPen), a smart pencil designed to instantly solve math problems using an onboard camera and Wi-Fi. I finished the first version of the hardware schematics, which is controlled by the ESP32-S3-MINI-1 microcontroller. The pencil integrates lithium battery charging via a TP4056, a USB-C interface for power, a dedicated display, and a camera.

<img width="1328" height="848" alt="image" src="https://github.com/user-attachments/assets/a95a4949-009d-441e-9cf4-d9e296283dca" />

### Struggles:
Designing a schematic with a camera, an OLED screen, and a power management system into a pencil-thin form factor came with major routing and hardware hurdles. Selecting the ESP32-S3 module was crucial for its native camera support and compact footprint, but mapping out all the connections for all the components was surprisingly difficult! I had to figure out how to wire the resistors, diodes, and capacitors in order to protect my project from frying!

### Future work:
I will review my schematics again and then, I can begin the complex design and routing of the PCB. I know it will be a challenge to fit everything in such a small board!

---

## Log 2: June 30, 2026 - Schematics Revision - 2 hours

After doing some further research into camera modules, I realized that using a camera for such close distances would not work easily. Furthermore, I would need precise lighting and a way to preview camera snapshots later on. All of these complications pushed me to revise how I would build uPen. I came across this Inertial Measurement Unit (IMU) module, and I realized that I could track and replicate the actual handwriting movements instead of using a camera to capture math problems and send them through an API to retrieve an answer. This means I would redo my entire schematic!!!

<img width="1607" height="759" alt="image" src="https://github.com/user-attachments/assets/98584df1-5e4a-4178-a4fa-d1a8b2547bef" />

However, the IMU module presents a challenge when double integrating the acceleration values to get position coordinates of each handwritten character. It loses accuracy and precision as it continues to integrate over time due to sensor noise, meaning the plotted position points of a handwritten sentence or equation could be easily warped and a recorded position coordinate could be a foot away than the actual position!

With some further research, I found that the Time of Flight sensor could be utilized to detect when the hand and pen is lifted to move and right the next character or sentence.

<img width="1918" height="866" alt="image" src="https://github.com/user-attachments/assets/525e9d03-b845-4461-baa7-ab885c9520b4" />

With this, I would be able to send zero velocity updates (ZUPTs) in the code in order to force the velocity to be zero, which would reset integration drift errors.

I was happy to find out that the SEEED Studio XIAO ESP32S3 integrated both charging and WiFi, which would make my routing simple! Furthermore, since both the OLED, IMU module, and Time of Flight sensor all run on I2C communication, I was able to daisy chain all of these, saving me much time.

I did not use KiCad to draw the schematics this time as A PCB would have been too large to fit into a small form factor pen shape, so I used Canva. Here is what I started with:

<img width="1919" height="813" alt="Screenshot 2026-06-30 3 29 13 PM" src="https://github.com/user-attachments/assets/be8765b2-e58b-4d40-9c90-faf2a183dbeb" />

and this is what I ended with:

<img width="1920" height="1080" alt="uPen Circuit" src="https://github.com/user-attachments/assets/61e249ec-f08d-4588-98d7-cf615d77d310" />

### Future work:
I am hoping to make a tiny PCB for the back of the MCU and central routing next time, and I hope to begin working on designing how everything will fit into a 3D printed case!

---

## Log 3: July 1, 2026 - CAD Attempt - 3.4 hours

Timelapse link: https://lapse.hackclub.com/timelapse/dnVF-_9PWZdE.

Today, I worked on my schematic a bit more, optimizing the wiring and some parts. I went through small revisions.
<img width="1920" height="1080" alt="uPen Circuitv2 1" src="https://github.com/user-attachments/assets/7a0c1c32-152c-4ae3-8d65-43ec82567bf1" />

I had to split up the I2C lines instead of daisy chaining everything. The OLED would have been extremely noisy, messing up the fast data collection of the IMU and Time of Flight modules. I also came up with a plan on how the pen would work. After the pen collects handwriting data from the IMU, it would convert the data into x and y coordinates and plot them into an image. This image of a math equation would be sent over the wifi to a math solver API, which would return a short answer to be displayed on the OLED. In order to do this, without burdening the pen's microcontroller, I thought about sending the data to a Raspberry Pi Pico 2 W, which would handle the heavy communication with an API.

<img width="1920" height="1080" alt="uPen Circuitv2 2" src="https://github.com/user-attachments/assets/788d562b-5ab6-4bb2-bb5b-39b04c1b78c5" />

After that, I began to work on the CAD design for the pen case. I first modeled the sizes for each part and placed them around a real pen footprint as I was hoping to integrate a real pen for writing while the smart pen features solve the equation in real time. However, I came across critical measurement problems.

<img width="1077" height="636" alt="image" src="https://github.com/user-attachments/assets/9f88afcc-cd97-47e9-b35c-f9b3c1cb33b2" />

When I began to cover the parts in a cylinder case, I realized that everything would have to fit in a 38mm diameter tube! I was aiming for a 20mm diameter and clearly, everything would not fit cleanly...

<img width="932" height="493" alt="image" src="https://github.com/user-attachments/assets/21be4078-28a3-42c5-81b3-ce38dbd38ec4" />

### Future work:
I am going to have to replan my materials in order to figure out how to fit everything in a thinner form factor.

---

## Log 4: July 2, 2026 - Intense Planning - 2 hours

With some research, I found an interesting microcontroller board that featured an ESP32-S3 while maintaining a small form factor of 28 by 11mm!

<img width="1543" height="822" alt="image" src="https://github.com/user-attachments/assets/34335e19-94a6-485e-9018-f588addc103a" />

This gave me a lot of hope for making a pen that would fit a 20mm diameter case! The pen also featured a vast storage for holding IMU data and onboard charging.

<img width="1543" height="822" alt="image" src="https://github.com/user-attachments/assets/9a88e302-d6eb-4214-9198-75d56f460f3c" />

Later, I realized that it would be easier to fit a small form factor by routing bare chips. With this, I planned to use the powerful LSM6DSV16X IMU chip with a MAX17048 chip to more accurately measure battery percentage rather than relying on a questionable voltage divider. 

<img width="1337" height="793" alt="image" src="https://github.com/user-attachments/assets/45d92154-9928-4ca4-8a76-f592d0f53212" />

It also took me forever to find a great battery that would handle power hungry Wifi transmissions while still maintaining a small form factor. I ended up with this powerful E-flite 3.7V 150mAh 1S 45C LiPo Battery!

<img width="1853" height="740" alt="image" src="https://github.com/user-attachments/assets/95401158-8e06-4d40-afec-dfdb729f8ccf" />

Since I decided that housing a full pen inside the case would take up so much precious space, I got rid of it. It would pivot my project to a invisible ink or air pen, and this allowed me to drop the Time of Flight module for a SDS001R detector switch that would be placed at the tip.

<img width="1407" height="791" alt="image" src="https://github.com/user-attachments/assets/f4ab6f97-98a6-4806-a9b0-f9e1f92c935b" />

Moreover, I had to rework how the pen would function! Since the user would be writing on paper without seeing the ink mark the paper, I plan to have the OLED screen display each handwritten stroke as a preview of the math equation written. Instead of using standard power hungry Wifi transmissions, I decided to use the fast ESP-NOW function with another ESP32 microcontroller in order to handle data transmission. The other ESP32 would be able to process the data with more power as it is not limited to a small battery.

### Future work:
With this new pen vision, I hope to design a schematic that would house all the pen's components in a super small PCB!

---

## Log 5: July 3, 2026 - Schematics Again! - 2 hours

Timelapse link: https://lapse.hackclub.com/timelapse/iF6mR7ldbXd7.

I honestly cannot believe that I am remaking the schematics for this project for the third time! This project has gone through major design revisions, and I hope that this one will actually work! I had to be careful wiring the connections as I had to handle the an external PCM circuit and a battery safety switch in order to prevent battery drain whenever I do not use the pen for long periods of time. I had some problems finding the exact footprint and symbols for each chip, especially the SDS001R detector switch as it is a niche part. However, with some time I was able to create a rough schematic that will need some more fine tuning.

<img width="1407" height="791" alt="image" src="https://github.com/user-attachments/assets/0206196a-50e7-4181-81f5-3e38c06880f2" />

### Future work:
After verifying my schematic with official wiring schematics for each specialized chip, I will work to ensure that my board is ready to route in the PCB editor!

---

##  Log 6: July 4, 2026 - Schematics Clean Up - 1 hour

Timelapse link: https://lapse.hackclub.com/timelapse/JP0mHgVsAJM-.

I spent a good hour organizing the schematics while following datasheet recommendations. The schematic is much more clearer, especially considering where each capacitor goes on the LSM6DSV16X (IMU) and MAX17048 fuel gauge chips! 

I was reading through Macondo Docs and I found this interesting tip:

<img width="1888" height="840" alt="image" src="https://github.com/user-attachments/assets/768cce9c-0a51-4082-b8ef-c00fac6ef103" />

Thus, I decided to follow the tip and use the correct symbols for power and GND flags, having power flags point up while GND flags point down. I have to admit it makes the schematics a lot more cleaner than how I had originally done them in the past.

<img width="1198" height="821" alt="image" src="https://github.com/user-attachments/assets/22023963-b688-4702-a651-d44a4e45394e" />

### Future work:
I hope to finally begin working on the PCB design next time!

---

##  Log 7: July 5, 2026 - Start of PCB - 1.3 hours

Timelapse link: https://lapse.hackclub.com/timelapse/LVc4ahCd2COp.

After calculating where all the components would go, I realized that the NanoS3 microcontroller footprint was bigger than I had expected. With this, I decided to shift all the used pins to one side so that I could maximize space for routing while keeping everything in a 15mm width board.

<img width="807" height="583" alt="image" src="https://github.com/user-attachments/assets/d353d5df-0cfb-44a5-a7a3-fd70f11d2168" />

Honestly, it was difficult to figure out how I would organize each part as I did not want to put the microcontroller at the end as the antenna would make the pen extra long. However, I also did not want to put the microcontroller and antenna near the tip of the pen as that would force the antenna to be near electronics...

<img width="1442" height="702" alt="image" src="https://github.com/user-attachments/assets/a46db40a-9403-4101-9522-9a5837acad5a" />

It took me quite some time to make some compromises with placements, and I am still rethinking them...

### Future work:
Tomorrow, I really hope to actually start working on routing the PCB.

---

##  Log 8: July 6, 2026 - Major PCB Work - 7.5 hours

Timelapse link: https://lapse.hackclub.com/timelapse/swXfEaVnoNOx.

Today, I spent a bit too much time finalizing the entire PCB layout and working on routing all the connections. This was not easy as it was also my first time routing a bare USB-C receptacle, and I quickly found it to be extremely difficult!

I began by adding the ESD USB-C protection chip USBLC6-2SC6 into my schematic.

<img width="632" height="562" alt="image" src="https://github.com/user-attachments/assets/2a2c9f38-843a-4537-9f0b-3d3e2bfbc71e" />

When I began routing using KiCad's differential routing tool, it refused to connect to the ESD chip as the Data lines were reversed in the footprint layout! 

<img width="654" height="724" alt="image" src="https://github.com/user-attachments/assets/a5a14a43-da1d-4b77-a30d-1dff4b94b501" />

I tried numerous ways to connect the lines, and they were all far from equal in length.

<img width="661" height="595" alt="image" src="https://github.com/user-attachments/assets/c56d3157-e025-4118-947e-713ee46c9a1b" />
<img width="695" height="714" alt="image" src="https://github.com/user-attachments/assets/8eafce7c-877f-4f42-9c72-2703d07a4340" />

After many attempts, I settled on a somewhat symmetrical connection style with vias, and I almost got the data lines to be equal in length. Thankfully, wiring all the other components were relatively straightforward. Yet, it was still a time-consuming task.

<img width="1532" height="525" alt="image" src="https://github.com/user-attachments/assets/d1872c6d-7352-4404-b537-5d97cb8beaef" />

Even after all that hard work, KiCad came up with many errors and I realized I did not route the GND pad thats stuck in the middle of the ESD chip with almost no space for more routing!

<img width="1534" height="735" alt="image" src="https://github.com/user-attachments/assets/a99843b0-d7fa-46f9-b184-052386b60b6b" />

### Future work:
After much rest, I must figure out how to optimize this PCB routing and solve all those Design Rules Checker errors...

---

##  Log 9: July 7, 2026 - PCB Version 2! - 4 hours

Timelapse link: https://lapse.hackclub.com/timelapse/U-yj73YHo-n-.

I was not expecting to redo the entire PCB routing again from scratch... However, after some thinking and looking at the messy routing I had done, I was set on fixing it all. Instead of simply routing wires on four different layers wherever I wanted, I decided to come up with a plan on how I would handle routing on each layer. 

I decided to place all power and data lines on the first and fourth layer while the second and third layers would be ground planes. Since most of the SMD parts needed to be on the top layer of the PCB, I needed a ground plane directly underneath them, especially for the USB-C receptacle. However, since I had many data lines, including two sets of I2C lines, I wanted to have a ground plane to separate the data lines on different layers to prevent crosstalk. With this, I set a global clearance rule of 0.25mm from all vias and routing, which helped me to freely route while letting KiCad handle the spacing.

I honestly found this PCB much easier to route than before, but I realized that I may have made too many holes in the ground plane...

<img width="1015" height="732" alt="image" src="https://github.com/user-attachments/assets/b66595fa-eaec-4281-889d-da709247f6a5" />
<img width="1015" height="436" alt="image" src="https://github.com/user-attachments/assets/8303cdc3-3137-4598-a3d2-3446bd42cfbe" />

A key difficulty that limited how I could wire was that since the NanoS3 had exposed vias on its bottom layer, I wanted to avoid routing anything inside the microcontroller footprint. This meant I had to squeeze in vias for each pin.

<img width="1008" height="392" alt="image" src="https://github.com/user-attachments/assets/9d737693-00e8-415e-92a9-279e10bf9d0a" />

Anyhow, this is what the entire PCB looks like as of right now:

<img width="1012" height="337" alt="image" src="https://github.com/user-attachments/assets/ec567e60-9a58-400e-bb4e-3a009d9cf518" />

### Future work:
Next time, I look forward to checking over the PCB with Design Rules Checker again and starting the CAD for the pen case design!

---

##  Log 10: July 8, 2026 - CAD Attempt 2 - 1.3 hours

Timelapse link: https://lapse.hackclub.com/timelapse/-Hel6EKzSH4P.

I did not think I could have so many errors to solve!

<img width="704" height="601" alt="image" src="https://github.com/user-attachments/assets/81a47899-9450-4659-b48f-f9c555de0d1c" />

I went through each of them and found out that most of them were flagging the clearances of the footprint pads of the SMD parts. Apparently, I had set the default clearance to 0.25mm which was too big for the SMD parts...

As I began working on the CAD design, I chose a rounded square prism shape for the case because I wanted to do somthing different than a generic cylinder. Also, the OLED screen would look much more natural with the rounded square prism.

<img width="704" height="601" alt="image" src="https://github.com/user-attachments/assets/5576c6e9-4b53-4bf4-b1c0-7e815c058cc0" />

While it was great to reference the STEP file of my PCB, I quickly found that the switch part was too wide, meaning I would have to later extend the pen tip...

<img width="916" height="270" alt="image" src="https://github.com/user-attachments/assets/63fc5769-2baf-48cc-83ce-58e3d4f60fb7" />
<img width="807" height="546" alt="image" src="https://github.com/user-attachments/assets/3f1f078f-8f83-4ea9-8b34-425d9d4f6d0f" />

### Future work:
I will make some adjustments to the CAD design and work on creating holes and supports for the components on the PCB board.

---

##  Log 11: July 9, 2026 - Heavy CAD Work - 3.5 hours

Timelapse link: https://lapse.hackclub.com/timelapse/df8S33CcSg0K.

Upon realizing that the USB-C receptacle was supposed to stick outside the PCB a bit so it would naturally fit in the CAD case, I had to adjust move its footprint in the PCB.

<img width="1623" height="315" alt="image" src="https://github.com/user-attachments/assets/22fbe23e-4759-4990-ae4b-98b3554ec41f" />

I spent a lot of time figuring out how to create supports for the floating PCB in the hollow case, and I initially wanted to use the rib function in Autodesk Fusion. With some time, I realized it would be easier to do so with the combine, extrude, and cut functions by using the case and PCB to carve out supports.

<img width="529" height="508" alt="image" src="https://github.com/user-attachments/assets/51d01cd1-e496-4b15-a8fc-716141e1df0c" />
<img width="740" height="568" alt="image" src="https://github.com/user-attachments/assets/9dfa8c5f-0719-42af-a071-ae76543a352a" />
<img width="740" height="568" alt="image" src="https://github.com/user-attachments/assets/88957d15-b29d-4988-bfde-a2f62f842369" />

### Future work:
I am hoping to finish the CAD case design tomorrow!

---
