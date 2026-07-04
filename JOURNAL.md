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
