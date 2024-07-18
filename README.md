# Advanced Traffic Light Control System using 8051 Microcontroller and IR Sensor

## Overview

This project implements a traffic light control system using an 8051 microcontroller, featuring multiple traffic light signals controlled by an IR sensor. The system adjusts traffic signals dynamically based on vehicle detection to manage traffic flow efficiently.

## Components Used

- **Microcontroller:** 8051 series (specific model used in your setup, e.g., AT89C51).
- **IR Sensor:** Used to detect vehicles approaching the intersection.
- **LEDs:** For traffic light signals (Red, Yellow, Green).
- **LCD Display:** Optional for displaying status and messages.

## Project Structure

- **`main.c`:** Contains the main logic and control flow for the traffic light system.
- **`lcd.h` and `lcd.c`:** Header and source files for interfacing with the LCD display (if used).
- **`delay.h` and `delay.c`:** Header and source files containing delay functions.
- **`README.md`:** This file, providing project overview, setup instructions, and usage details.

## Setup and Configuration

1. **Hardware Setup:**
   - Connect LEDs to the microcontroller ports (`P0`, `P1`, `P2` for different traffic lights).
   - Connect the IR sensor to a suitable input pin (`P3^2` for example).

2. **Software Setup:**
   - Use an 8051-compatible IDE like Keil µVision or SDCC Compiler.
   - Include necessary header files (`reg51.h`, if using 8051-specific headers).
   - Configure the development environment to compile and upload the code to your microcontroller.

## How to Use

1. **Compile and Upload:**
   - Compile the code using your preferred IDE or command-line compiler.
   - Upload the compiled binary to the 8051 microcontroller.

2. **Operation:**
   - Upon powering on, the system initializes and starts monitoring the IR sensor.
   - Adjusts traffic light signals based on vehicle detection:
     - **Normal Traffic:** Green lights on active roads, with timed transitions to Yellow and Red.
     - **Heavy Traffic:** Longer delays on Green lights, shorter on Yellow.
       
## Contact

   - Author: [Rushi Kharmate]
   - Email: [rushirajekharmate@gmail.com]
