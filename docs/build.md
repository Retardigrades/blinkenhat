---
title: Build your own Blinkenhat
---
## Build your own Blinkenhat

If you want to build your own BlinkenHat board we'll give you all the information you need. First of all you need the PCB. The design files for this can be found in our [github repository](https://github.com/Retardigrades/blinkenhat/tree/master/hardware/blinkenhat). We used the Software [KiCad](http://kicad-pcb.org/). It is opensource and available for many platforms. If your PCB-manufacturer has a direct KiCAD-upload option, you can just drop the _blinkenhat.kicad_pcb_ from the link above there and thats it.

The components can be purchased from various vendors. Depending on your location the best option can differ so we won't give a definite recommendation. The List of the needed components for the board is:

| Name | Part | Package |
|------|------|---------|
| U1 | AMS1117-3.3 | SOT-223 |
| U2 | ESP-8266 module | ESP-12f |
| Q1, Q2 | 2N7002 | SOT-23 |
| D1, D2 | RS1B | DO-214AC/SMA |
| C1,C3 | T491C 100U 10 | 3216-18 |
| C2 | T491B 22U 16 | 6032-28 |
| C4 | KEM Y5V0603 100N | G0603 |
| R1-R6, R8| R 10k | 0603 |
| R7, R9 | R 3.3k | 0603 |
| J1-J3| JST XH3P BU | straight |
| J4 | Standard pin header 2x4 | 2.54mm straight|
| J5 | Micro USB 10103594-0001LF  | |
| J5 | Standard pin header 2x5 | 1.27mm straight |
| SW1 | tactile switch | JTP-1138 |

We recommend to not to solder it by hand but use reflow soldering. You can get reflow paste from various distributors. If you plan to build more than one or two we recommend to request a stencil with your PCB-order. Some manufacturers even provide one for free if you order a certain amount of PCBs.

There is also a (probably outdated) [Shopping List](parts) that we used for the workshop.
