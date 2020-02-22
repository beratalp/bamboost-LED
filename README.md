# bamboost-LED

An RGB LED controller implementation for PIC16F88, controlled through UART.

## Features
### Color Modes:

|Color|Pin|Serial Command|
|-----|---|--------------|
|Red|RB0|'r'|
|Green|RB1|'g'|
|Blue|RB4|'b'|

### Blinking Modes:

|Mode|Serial Command|
|-----|-------------|
|Static|'0'|
|1000ms on, 1000ms off|'1'|
|500ms on, 500ms off|'2'|

---
The UART Baud Rate is 300.
