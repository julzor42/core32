# core32
Core32 is a library for **PIC32MX** 32-bit microcontrollers designed to be small and performant.
It allows to easily control the M4K core and the device's peripherals (SPI, UART, I2C, DMA, ...)

It also includes few drivers for external peripherals (Wii Nunchuk, 23LC1024 SRAM, IL9341 screen controller, ...)

# Tasks
## Introduction
Core32 based applications are composed of one or several Tasks.
Tasks are simple functions that are used as finite state machines.
## Usage
### Initialization
By default, the main() function is automatically handled by Core32, which initializes the processor
with the help of user directives declared in the **core32conf.h** file.
After hardware is configured, a task manager is created and a default user task, called **Program**.
### Task
When a task is created, it first enters the **TASK_START** state, which is meant to be used for initialization.
The task manager then automatically switches the task to the **TASK_IDLE** state and leaves it until the user
requires a new state.
### Internal states
Tasks include some internal states for common behaviours, such as delays, waiting for a value or a mask.
These states are entered using a set of functions that automatically manage them.
#### Delay
#### Wait value
#### Wait mask