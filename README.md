# Assembly-ADC-DAC

This repository contains our implementation of Analog-to-Digital Conversion (ADC) and Digital-to-Analog Conversion (DAC) using the MSP430 microcontroller for Lab 6 of the "Introduction to Computers" course.

## Repository Contents

### Code Files
- [API Module (api.s43)](./code/api.s43) - Implements high-level ADC/DAC application tasks
- [BSP Header (bsp.h)](./code/bsp.h) - Board Support Package definitions for hardware abstraction
- [BSP Module (bsp.s43)](./code/bsp.s43) - Hardware configuration for ADC, timers, and GPIO
- [HAL Module (hal.s43)](./code/hal.s43) - Hardware Abstraction Layer with LCD and ADC routines
- [Main Program (main.s43)](./code/main.s43) - Main application with finite state machine

### Documentation
- [Pre-lab Assignment](./docs/lab6_pre_assignment.pdf) - Initial preparation for ADC/DAC concepts
- [Preparation Report](./docs/lab6_preparation_report.pdf) - Detailed documentation of lab preparation
- [Final Lab Report](./docs/lab6_final_report.pdf) - Complete analysis and results of the implementation

## System Architecture

The code follows a layered architecture for embedded systems:

1. **BSP (Board Support Package)**: Hardware-specific definitions and configurations
2. **HAL (Hardware Abstraction Layer)**: LCD control, ADC routines, and GPIO handling
3. **API (Application Programming Interface)**: Implementation of ADC/DAC applications
4. **Main Application**: Finite state machine to select different ADC/DAC features

## Key Features

### 1. Analog Measurement Applications

The system implements three analog applications:

#### Find Voltage Extremes (Task 1)
```assembly
FindExtremas    CALL        #LCDClear
                CALL        #LCDCursorTo1   ; Move cursor to 1st square
                CALL        #PrintVmin      
                CALL        #LCDCursorTo17  ; Move cursor to second row
                CALL        #PrintVmax
```
*Continuously samples ADC and displays the minimum and maximum voltage values on the LCD*

#### Calculate Average Voltage (Task 2)
```assembly
CalcAvg         CALL        #LCDClear       
                CALL        #LCDCursorTo1   ; Move cursor to 1st square
                CALL        #PrintVavg
                NOP
```
*Takes 2000 ADC samples, calculates their average, and displays it on the LCD*

#### PWM Frequency Output (Task 3)
```assembly
FreqOut         CALL #ADCconfig
State3Loop      CMP  #3,state
                JNE  ExitFreqOut
                CLR  R10    
                CLR  R11
                CALL #ADC_Start
                ADD  ADC_MEM, R10  ; T0
                CALL #ADC_Start
                ADD  ADC_MEM, R11  ; T1
```
*Generates PWM frequency (1kHz or 3kHz) based on voltage difference between consecutive ADC readings*

### 2. Advanced Mathematics

The code implements binary math routines using assembly:

#### 16-bit Division (DIV16bit Macro)
```assembly
DIV16bit        MACRO   Divided,Divisor
                LOCAL   L1,L2,L3
                mov     #17,R9
                clr     R8                ; Quotient register
                mov.w   Divided,R13       ; Devided registers is R5,R4
                clr     R5
                mov.w   Divisor,R6        ; Divisor registers is R6
                ...
```

#### Multiplication (MULT Macro)
```assembly
MULT            MACRO     Number,Times
                LOCAL     L4
                CLR       R14
                mov       Times, R9
L4              add       Number, R14    
                dec       R9
                JNZ       L4
                ENDM
```

### 3. LCD Interface

The system includes comprehensive LCD control:

- Character and command handling
- Cursor positioning
- Formatted voltage display (with decimal point)
- Custom labels for each measurement type

### 4. ADC Configuration

The code demonstrates proper ADC configuration and usage:

```assembly
ADCconfig    bic.w #ENC,ADC_CTL0          ; Modifiable only when enc=0
             mov.w #ADC_Cycles+ADC_ON+ADC_IE,ADC_CTL0   ; Sample&hold=16 cycles
             mov.w #INCH_3, ADC_CTL1      ; Input channel 3 
             ret
```

## Usage

1. Connect the MSP430 development board to your computer
2. Connect an LCD display according to the pin definitions in bsp.h
3. Connect a variable voltage source to P1.3 (analog input)
4. Build and flash the code using IAR Embedded Workbench
5. The system begins in idle state (State 0)
6. Press the push buttons to activate different functions:
   - PB0 (P1.0): Activate Task 1 - Find voltage extremes (min/max)
   - PB1 (P1.1): Activate Task 2 - Calculate average voltage
   - PB2 (P1.2): Activate Task 3 - Generate PWM frequency based on voltage difference

## Hardware Requirements

- MSP430G2553 microcontroller
- LCD display (HD44780 compatible)
- Push buttons connected to P1.0, P1.1, and P1.2
- Variable voltage source connected to P1.3 (ADC input)
- Oscilloscope to visualize PWM output on P1.2

## Authors

Created by Asaf Kamber and Aviv Primor

## Course Information

- Course: Introduction to Computers
- Lab: Analog to Digital Signals and Digital to Analog Signals (Lab 6)
