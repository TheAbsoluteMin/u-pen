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

## Log 2: June 30, 2026 - Schematics Revision - 6 hours

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
