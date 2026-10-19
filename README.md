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
| Week | Tier | Parts funding |
| --- | --- | --- |
| Week 1 | Tier 1 | $30.00 |

| Part | What it's for | Qty | Unit | Total | Vendor |
| --- | --- | --- | --- | --- | --- |
| [ESP32 c3 mini](https://www.aliexpress.com/item/1005008791937363.html?spm=a2g0o.cart.0.0.3c4d38daD6macX&mp=1&pdp_npi=6%40dis%21GBP%21GBP+7.09%21GBP+7.09%21%21GBP+5.97%21%21%21%402103973d17915527209206815e14b1%2112000052930246748%21ct%21UK%213165619755%21%211%210%21) | The main brain that runs your software, handles Wi-Fi/Bluetooth, and controls all components. | 1 | $8.34 | $8.34 | [Aliexpress](https://www.aliexpress.com/item/1005008791937363.html?spm=a2g0o.cart.0.0.3c4d38daD6macX&mp=1&pdp_npi=6%40dis%21GBP%21GBP+7.09%21GBP+7.09%21%21GBP+5.97%21%21%21%402103973d17915527209206815e14b1%2112000052930246748%21ct%21UK%213165619755%21%211%210%21) |
| [MPU-6050 MPU6050 Module](https://www.aliexpress.com/item/1005009668682906.html?spm=a2g0o.cart.0.0.3c4d38daD6macX&mp=1&pdp_npi=6%40dis%21GBP%21GBP+2.09%21GBP+2.09%21%21GBP+1.76%21%21%21%402103973d17915527209206815e14b1%2112000049816725556%21ct%21UK%213165619755%21%211%210%21) | accelerometer and gyro used for tilt-based motion controls in games. | 1 | $1.73 | $1.73 | [Aliexpress](https://www.aliexpress.com/item/1005009668682906.html?spm=a2g0o.cart.0.0.3c4d38daD6macX&mp=1&pdp_npi=6%40dis%21GBP%21GBP+2.09%21GBP+2.09%21%21GBP+1.76%21%21%21%402103973d17915527209206815e14b1%2112000049816725556%21ct%21UK%213165619755%21%211%210%21) |
| [DHT11](https://www.aliexpress.com/item/1005008953430940.html?spm=a2g0o.cart.0.0.511138da3StELt&mp=1&pdp_npi=6%40dis%21GBP%21GBP+1.06%21GBP+1.06%21%21GBP+0.88%21%21%21%400b884a9917915535706416768e0d2b%2112000047346503744%21ct%21UK%213165619755%21%211%210%21) | temp sensor | 1 | $1.40 | $1.40 | [Aliexpress](https://www.aliexpress.com/item/1005008953430940.html?spm=a2g0o.cart.0.0.511138da3StELt&mp=1&pdp_npi=6%40dis%21GBP%21GBP+1.06%21GBP+1.06%21%21GBP+0.88%21%21%21%400b884a9917915535706416768e0d2b%2112000047346503744%21ct%21UK%213165619755%21%211%210%21) |
| [pcb board](https://cart.jlcpcb.com/shopcart/cart) | pcb | 1 | $8.67 | $8.67 | [JLCPCB](https://cart.jlcpcb.com/shopcart/cart) |
| [0.96  inch OLED](https://www.aliexpress.com/item/1005006141235306.html?spm=a2g0o.cart.0.0.578f38dab9qQyl&mp=1&pdp_npi=6%40dis%21GBP%21GBP+2.26%21GBP+0.70%21%21GBP+0.33%21%21%21%4021613be817915538824665149e0ef0%2112000035944225408%21ct%21UK%213165619755%21%211%210%21) | the display | 1 | $0.93 | $0.93 | [Aliexpress](https://www.aliexpress.com/item/1005006141235306.html?spm=a2g0o.cart.0.0.578f38dab9qQyl&mp=1&pdp_npi=6%40dis%21GBP%21GBP+2.26%21GBP+0.70%21%21GBP+0.33%21%21%21%4021613be817915538824665149e0ef0%2112000035944225408%21ct%21UK%213165619755%21%211%210%21) |
| [rotary encoder](https://www.aliexpress.com/item/1005008583446552.html?spm=a2g0o.productlist.main.2.322d6a57Omemmf&algo_pvid=290e5376-c6e0-4d74-8f15-2345f59ad43f&algo_exp_id=290e5376-c6e0-4d74-8f15-2345f59ad43f-1&pdp_ext_f=%7B%22order%22%3A%221189%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21GBP%213.93%213.15%21%21%215.05%214.05%21%40210393bd17915540235537215e0cdb%2112000045835073058%21sea%21UK%213165619755%21X%211%210%21n_tag%3A-29919%3Bd%3Ae4ba77da%3Bm03_new_user%3A-29895%3BpisId%3A5000000218189468&curPageLogUid=ELZrBR1cT0gn&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008583446552%7C_p_origin_prod%3A) | navigation | 1 | $5.20 | $5.20 | [Aliexpress](https://www.aliexpress.com/item/1005008583446552.html?spm=a2g0o.productlist.main.2.322d6a57Omemmf&algo_pvid=290e5376-c6e0-4d74-8f15-2345f59ad43f&algo_exp_id=290e5376-c6e0-4d74-8f15-2345f59ad43f-1&pdp_ext_f=%7B%22order%22%3A%221189%22%2C%22spu_best_type%22%3A%22price%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21GBP%213.93%213.15%21%21%215.05%214.05%21%40210393bd17915540235537215e0cdb%2112000045835073058%21sea%21UK%213165619755%21X%211%210%21n_tag%3A-29919%3Bd%3Ae4ba77da%3Bm03_new_user%3A-29895%3BpisId%3A5000000218189468&curPageLogUid=ELZrBR1cT0gn&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005008583446552%7C_p_origin_prod%3A) |
| [buzzer](https://www.aliexpress.com/item/1005008789575850.html?spm=a2g0o.cart.0.0.175238daobE0Ld&mp=1&pdp_npi=6%40dis%21GBP%21GBP+1.38%21GBP+1.38%21%21GBP+1.34%21%21%21%400b0fed2b17915543499984784e1024%2112000046671331943%21ct%21UK%213165619755%21%211%210%21) | make sound | 1 | $1.82 | $1.82 | [Aliexpress](https://www.aliexpress.com/item/1005008789575850.html?spm=a2g0o.cart.0.0.175238daobE0Ld&mp=1&pdp_npi=6%40dis%21GBP%21GBP+1.38%21GBP+1.38%21%21GBP+1.34%21%21%21%400b0fed2b17915543499984784e1024%2112000046671331943%21ct%21UK%213165619755%21%211%210%21) |
| [buttons](https://www.aliexpress.com/item/1005001629177989.html?spm=a2g0o.productlist.main.2.2b7a4c01fzW9qP&algo_pvid=2075475e-6f89-4258-8f3a-6f83f7748477&algo_exp_id=2075475e-6f89-4258-8f3a-6f83f7748477-1&pdp_ext_f=%7B%22order%22%3A%223471%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21GBP%211.13%210.35%21%21%219.71%212.99%21%400b1585c117915547239767987e0cff%2112000028585601895%21sea%21UK%213165619755%21X%211%210%21n_tag%3A-29919%3Bd%3Ae4ba77da%3Bm03_new_user%3A-29895%3BpisId%3A5000000218189468&curPageLogUid=qgexuiVhkgyf&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005001629177989%7C_p_origin_prod%3A) | navigation and menu and gameplay | 1 | $1.61 | $1.61 | [Aliexpress](https://www.aliexpress.com/item/1005001629177989.html?spm=a2g0o.productlist.main.2.2b7a4c01fzW9qP&algo_pvid=2075475e-6f89-4258-8f3a-6f83f7748477&algo_exp_id=2075475e-6f89-4258-8f3a-6f83f7748477-1&pdp_ext_f=%7B%22order%22%3A%223471%22%2C%22eval%22%3A%221%22%2C%22fromPage%22%3A%22search%22%7D&pdp_npi=6%40dis%21GBP%211.13%210.35%21%21%219.71%212.99%21%400b1585c117915547239767987e0cff%2112000028585601895%21sea%21UK%213165619755%21X%211%210%21n_tag%3A-29919%3Bd%3Ae4ba77da%3Bm03_new_user%3A-29895%3BpisId%3A5000000218189468&curPageLogUid=qgexuiVhkgyf&utparam-url=scene%3Asearch%7Cquery_from%3A%7Cx_object_id%3A1005001629177989%7C_p_origin_prod%3A) |
| **Parts subtotal** | — | — | — | **$29.70** | — |
| **Tax & shipping** | — | — | — | **$0.00** | — |
| **Total** | — | — | — | **$29.70** | — |

$0.30 left of the tier's funding.
