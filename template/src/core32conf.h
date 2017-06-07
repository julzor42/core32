#pragma once
//
// Core32 user configuration file
//
// This file is used to configure the core32 framework features


// Include one of the required board header
//#include <explorer1632/explorer1632.h>
//#include <easypicv7/easypicv7.h>

// Use default configuration bits
#define SYSTEM_DEFAULT_BITS

//
// Frequencies
//
#define SYSTEM_FREQ 	      80000000L     // System clock
#define SYSTEM_PBDIV	      2             // Peripheral clock divider
#define SYSTEM_INT_MULTI                  // Multivectored interrupts

//
// Console
// 
#define UART_CONSOLE        UART_2
#define UART_CONSOLE_SPEED  115200

