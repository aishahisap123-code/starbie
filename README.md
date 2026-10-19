# Starcade
Starcade is a motion-controlled handheld arcade pet and retro game console. Inspired by classic handhelds and desktop pets, it brings interactive games, motion sensing, and sound effects together in a custom wing-shaped PCB. Instead of relying solely on traditional buttons, you interact with games, menus, and pet reactions by physically tilting, shaking, and rotating the board.
<img width="1572" height="1010" alt="image" src="https://github.com/user-attachments/assets/d4fed6db-9e43-48d6-8f12-271fad5c3c43" />
<img width="2335" height="1359" alt="image" src="https://github.com/user-attachments/assets/8dd09dbe-11b5-48da-960b-e21ba7642a11" />



# What It Is
Starcade is designed to sit on your desk, display custom animations on a bright OLED screen, and react directly to how you handle it. Tilting, rotating the encoder, pressing action buttons, and listening to sound effects and LED animations are all core to the physical experience.

The board includes an ESP32-C3 microcontroller, 0.96" OLED display, 6-axis MPU6050 motion sensor, DHT11 temperature/humidity sensor, addressable WS2812B RGB LEDs, active buzzer, and a rotary encoder inside a compact wing-shaped PCB design. It is USB-C powered and optimized for easy component assembly and custom firmware hacking.

# Why?
This project was created as a complete, hands-on hardware and embedded software tutorial, taking builders all the way from custom PCB layout and Gerber manufacturing to writing full Arduino firmware from scratch.

# Project Status
The custom PCB layout, ground plane generation, Gerber manufacturing exports, and component DRC checks are complete and verified. Starter Arduino IDE code and pin assignment maps are set up to handle display drivers, motion detection, RGB lighting, and menu navigation.

# Software
Firmware/ contains modular, self-contained Arduino IDE sketches for the Seeed Studio XIAO ESP32-C3. Builders customize pin assignments, motion sensitivity, sound effects, LED lighting modes, and sensor readouts at the top of the sketch. See the Firmware/ README for library setup, board manager links, and flashing instructions.

# Repository Contents
PCB/ — KiCad source files, schematic diagrams, and ready-to-upload Gerber fabrication exports (.zip)

Renders/ — 2D/3D front and back PCB renders with custom silkscreen artwork (STARCADE35, AXISAP, and emblems)

Project Guide.md — Step-by-step assembly, soldering, and manufacturing guide

Firmware/ — Arduino IDE starter sketches for OLED graphics, MPU6050 motion tracking, DHT11 environmental readings, WS2812B LEDs, buzzer audio, and rotary menu navigation

BOM/ Starcade 35 – bill of materials
Note

This parts list is mirrored from Half Life. Editing it here will not change the platform's copy, and the next sync overwrites this file.

Week	Tier	Parts funding
Week 1	Tier 1	$30.00
Part	What it's for	Qty	Unit	Total	Vendor
ESP32 c3 mini	The main brain that runs your software, handles Wi-Fi/Bluetooth, and controls all components.	1	$8.34	$8.34	Aliexpress
MPU-6050 MPU6050 Module	accelerometer and gyro used for tilt-based motion controls in games.	1	$1.73	$1.73	Aliexpress
DHT11	temp sensor	1	$1.40	$1.40	Aliexpress
pcb board	pcb	1	$8.67	$8.67	JLCPCB
0.96 inch OLED	the display	1	$0.93	$0.93	Aliexpress
rotary encoder	navigation	1	$5.20	$5.20	Aliexpress
buzzer	make sound	1	$1.82	$1.82	Aliexpress
buttons	navigation and menu and gameplay	1	$1.61	$1.61	Aliexpress
Parts subtotal	—	—	—	$29.70	—
Tax & shipping	—	—	—	$0.00	—
Total	—	—	—	$29.70	—
$0.30 left of the tier's funding.
