#ifndef _bsp_H_
#define _bsp_H_

#include  <msp430G2553.h>       // MSP430x2xx
// #include  <msp430xG46x.h>    // MSP430x4xx

#define   debounceVal      250
#define   delay62_5ms      0xFFFF
#define   VoltRatio        286       // (Vref-Vmin)/(2^n-1), Vref=3.5v
#define   MaxADC           0x03FF   //max val in 10bit
#define   NumberOfSamples  2000

//ADC abstraction
#define ADC_VECTOR         ADC10_VECTOR
#define ADC_CTL0           &ADC10CTL0
#define ADC_CTL1           &ADC10CTL1
#define ADC_Cycles         ADC10SHT_2 // A0~A7 are 16 ADC10CYCLES
#define ADC_ON             ADC10ON
#define ADC_IE             ADC10IE
#define ADC_SC             ADC10SC
#define ADC_MEM            &ADC10MEM

// VECTOR abstraction
#define Timer_A_Interrupt  &TA0IV

//Timers abstraction
#define Timer_A_CTL        &TA0CTL
#define Timer_A_CC0_CTL    &TACCTL0
#define Timer_A_CC0_Reg    &TACCR0
#define Timer_A1_CTL       &TA1CTL
#define Timer_A1_CC2_CTL   &TA1CCTL2
#define Timer_A1_CC2_Reg   &TA1CCR2
#define Timer_A1_flag      &TA1IV
#define TBCLK_Port         0x10
#define TBCLK_Port_LAB     0x08

// LCD abstraction
#define LCDDataDIR         &P2DIR
#define LCDDataSEL         &P2SEL
#define LCDDataPort        &P2OUT
#define LCDCMDDIR          &P1DIR
#define LCDCMDSEL          &P1SEL
#define LCDCMDPort         &P1OUT
#define LCDRS              0x20
#define LCDRW              0x40
#define LCDE               0x80
#define LEDsArrPortSel     &P1SEL

// Switches abstraction
#define SWsArrPort         &P2IN
#define SWsArrPortDir      &P2DIR
#define SWsArrPortSel      &P2SEL
#define SWmask             0x0F


;----- PWM -----------
#define   PWMPort     &P1OUT

// PushButtons abstraction
#define PBsArrPort	   &P1IN 
#define PBsArrIntPend	   &P1IFG 
#define PBsArrIntEn	   &P1IE
#define PBsArrIntEdgeSel   &P1IES
#define PBsArrPortSel      &P1SEL 
#define PBsArrPortDir      &P1DIR 
#define PB0                0x01
#define PB1                0x02
#define PB2                0x10
//#define PB3              0x80
#define gotoStates         0xC2AC

#endif



