# esp8266-RemoteControlServer

#### Software and Electronics (PCB and schematic) for a esp8266-12e board remote control

This is a project (both software and hardware) for an web controlled IR (infra Read) emitter using an esp8266 microcontroller.

The software in esp8266 is a webserver that serves an single-page web interface (figure 2) with the control buttons for the desired IF device (TV, AC, or other), using html and bootstrap css. The esp8266 webserver also receives GET requests from each specific button. Button pressed requests are done asynchronous using ajax with the help of Jquery mobile library.

The electronic board pcb is composed of the eso8266 model 12-e with the bare minimal components for use, a Infra Read LED emitter and a linear power regulator to enable the use of 5V power supplies. The schematics are available in eagle files in the "pcb" folder and printable pdf files fot pcb etching.

Photos
=========

![alt tag](https://github.com/Atzingen/esp8266-RemoteControlServer/blob/master/fotos/interface.png)
Figure 1 - Interface provided by the esp8266 webserver.

![alt tag](https://github.com/Atzingen/esp8266-RemoteControlServer/blob/master/fotos/placa03.jpg)
Figure 2 - Assembled board. 4.5 to 9V input.

Authors
=========

Gustavo Voltani von Atzingen

References
=========

1- https://github.com/esp8266/Arduino

2- http://bbs.espressif.com/

3- http://www.esp8266.com/

4- https://github.com/markszabo/IRremoteESP8266
