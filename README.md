# ActiveP1Splitter
### Description
Firmware for the Fully Programmable Active P1 Splitter on my Tindie shop https://www.tindie.com/products/jeroen88/p1-port-splitter-fully-programmable/

The Fully Programmable Active P1 Splitter is used to split the P1 port on Dutch, Belgian, Luxembourg, Austrian and possibly other countries smart meters that adhere to the DSMR standard, into two ports

<!--
![<img src=https://github.com/Jeroen88/ActiveP1Splitter/blob/main/withoutMCU.jpeg width="33%" alt="P1 Splitter hardware">](https://www.tindie.com/products/jeroen88/p1-port-splitter-fully-programmable/)
-->

[![P1 Splitter hardware](https://github.com/Jeroen88/ActiveP1Splitter/blob/main/withoutMCU.jpeg)](https://www.tindie.com/products/jeroen88/p1-port-splitter-fully-programmable/)

An ESP32-S2 or an ESP32-S3 is used to read from the P1 input port and next to write to the two P1 output ports. Because a microcontroller is used, the input data could be 1) modified if necessary, and / or 2) pushed e.g. into a home automation system like Home Assistant without using an extra dongle. 

<img src=https://github.com/Jeroen88/ActiveP1Splitter/blob/main/with_MCU.jpeg width="33%" alt="P1 Splitter hardware with ESP32-S2 MCU">

Modification of the output can be used to change the behavior of P1 devices connected to the P1 port, e.g. a home battery or a charge point can be 'tricked' by sending higher or lower current or power than is actually measured. Please make sure that you know what you are doing, you do this at your own risk!

For P1 developers, the P1 Splitter could also be used to create test telegrams for the various DSMR (2.2, 4.0, 5.02, etc) standards, to mimic the output of various meter vendors, or to investigate edge cases.

Because both outputs are fully independent, both outputs can duplicate the exact input, one output can be duplicated while the other output is changed, or both outputs can be changed.

The hardware offers galvanic isolated ports using fast optocouplers for the data and normal optocouplers for the RTS pin. The input RTS pin is pulled to +5v. This is all DSMR standard compliant.

<img src=https://github.com/Jeroen88/ActiveP1Splitter/blob/main/05.png width="33%" alt="P1 Splitter hardware rendered from KiCad">

This repository shows a few examples of how to use it.

### Which P1 RJ12 socket is connected to what GPIO's
The central RJ12 socket is connected to the input P1, while facing the sockets up, the left socket is the first output P1 and the right socket is the second output P1.

### Enjoy playing around with it!
