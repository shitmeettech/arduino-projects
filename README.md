# Arduino Study Timer

## Project Overview
A simple study timer built using Arduino Uno and simulated in Wokwi. It provides visual and sound feedback when a study session finishes.

## Components
- Arduino Uno
- SSD1306 OLED display
- Joystick module
- Green LED and 220 Ω resistor
- Red LED and 220 Ω resistor
- Buzzer
- Servo motor

## Pin Connections
| Component | Arduino pin |
|---|---|
| OLED SDA | A4 |
| OLED SCL | A5 |
| Joystick VERT | A0 |
| Joystick HORZ | A1 |
| Joystick SEL | D2 |
| Green LED | D7 |
| Red LED | D8 |
| Buzzer | D9 |
| Servo signal | D10 |

## How It Works
The joystick button starts the timer. The OLED displays the countdown. When the session ends, the red LED lights, the buzzer sounds, and the servo moves to indicate completion.

## Simulation
Built and tested using Wokwi.

## Learning Goals
- Understand Arduino digital outputs and inputs
- Learn basic microcontroller programming
- Interface an OLED display and joystick
- Control a buzzer, LEDs, and servo motor
- 
