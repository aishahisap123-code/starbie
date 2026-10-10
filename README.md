# Starcade
Starcade is a motion-controlled handheld arcade pet and retro game console. Inspired by classic handhelds and desktop pets, it brings interactive games, motion sensing, and sound effects together in a custom wing-shaped PCB. Instead of relying solely on traditional buttons, you interact with games, menus, and pet reactions by physically tilting, shaking, and rotating the board.

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
