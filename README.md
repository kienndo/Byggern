# Byggern
This repository contains our implementation of the **Byggern (TTK4155)** project: a two-node embedded system for a physical ping‑pong game with UI, motor control, sensors, and CAN bus communication.

## Overview

- **Node 1 (UI/Controller)** — ATmega162: joystick + sliders (ADC), OLED UI, menu system, UART for debug, SPI to **MCP2515** CAN controller, external SRAM.
- **Node 2 (Actuation/Control)** — ATmega2560 (Arduino Mega): DC motor + encoder (PID), servo, IR sensors for ball detection, solenoid via relay, CAN interface to Node 1.

## Firmware Layout

### Node 1 (ATmega162)
- **drivers/**
  - `uart.c/h` – UART init, TX/RX, ring buffer
  - `spi.c/h` – SPI master for MCP2515
  - `adc.c/h` – joystick & sliders with calibration and dead zones
  - `ext_mem.c/h` – external SRAM init/test (address/data bus)
  - `oled.c/h` – OLED 128×64 text & bitmaps
- **can/**
  - `mcp2515.c/h`, `can.c/h` – CAN controller, filters, TX/RX queue
- **app/**
  - `menu.c/h` – hierarchical menu, actions (play, settings, high score)
  - `game.c/h` – game state, score handling, difficulty
  - `fsm.c/h` – simple finite state machine with onEnter/onTick/onExit
- **util/**
  - `timer.c/h`, `eeprom.c/h`, `logging.c/h`

### Node 2 (ATmega2560)
- **drivers/**
  - `motor.c/h` – PWM, direction, enable; `encoder.c/h` – quadrature read
  - `servo.c/h` – 50 Hz PWM
  - `ir.c/h` – IR sensor read + simple filtering
  - `relay.c/h` – solenoid through MOSFET/relay with safety timing
- **control/**
  - `pid.c/h` – configurable PID (Kp/Ki/Kd, anti-windup, output clamp)
  - `reference.c/h` – trajectory/difficulty presets
- **can/**
  - `can.c/h` – CAN command decode & telemetry publish
- **app/**
  - `play.c/h` – game loop, serve/reset logic, scoring
  - `diag.c/h` – UART commands for bring-up (e.g., `motor=80`, `servo=35`)
