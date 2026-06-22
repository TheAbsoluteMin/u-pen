---
title: "Insta-Form"
author: "TheAbsoluteMin"
description: "A Wi-Fi-enabled smart pencil that instantly captures and solves math problems."
created_at: "2026-06-21"
---

# Insta-Form Development Log

## Log 1: June 21, 2026 - Schematics - 2 hours
Timelapse <a href="https://lapse.hackclub.com/timelapse/9_8VnrNF68hq">link</a>.

### Inspiration:
The core inspiration behind Insta-Form was to bridge the gap between traditional handwriting and instant digital problem-solving. While apps like Photomath exist on smartphones, switching back and forth between a screen and scratch paper disrupts the natural flow of learning and checking math work. I wanted to build a seamless quick tool that lets students or engineers keep their pen to paper while getting instant feedback.

Thus, I am excited to share the first log for Insta-Form, a smart pencil designed to instantly solve math problems using an onboard camera and Wi-Fi. I finished the first version of the hardware schematics, which is controlled by the ESP32-S3-MINI-1 microcontroller. The pencil integrates lithium battery charging via a TP4056, a USB-C interface for power, a dedicated display, and a camera.

<img width="1328" height="848" alt="image" src="https://github.com/user-attachments/assets/a95a4949-009d-441e-9cf4-d9e296283dca" />

### Struggles:
Designing a schematic with a camera, an OLED screen, and a power management system into a pencil-thin form factor came with major routing and hardware hurdles. Selecting the ESP32-S3 module was crucial for its native camera support and compact footprint, but mapping out all the connections for all the components was surprisingly difficult! I had to figure out how to wire the resistors, diodes, and capacitors in order to protect my project from frying!

### Future work:
I will review my schematics again and then, I can begin the complex design and routing of the PCB. I know it will be a challenge to fit everything in such a small board!

---
