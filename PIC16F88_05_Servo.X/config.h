/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/
#ifndef CONFIG_H
#define	CONFIG_H

// Se define la frecuncia del oscilador la cual será utilizada
// por las rutinas de delay
#define _XTAL_FREQ 20000000  // Frecuencia del oscilador 20 Mhz


//OSCCONbits.IOFS   = 1;    // Frequency is stable
//OSCCONbits.SCS    = 0b10; // Internal RC is used for system clock (sin esto no anda RA6 y RA6)
//OSCCONbits.OSTS   = 1;    // Device is running from the primary system clock
//OSCCONbits.IRCF   = 0b111;  // IRCF<2:0> = 111 = 8 MHz
//#define DefineInternalClock8Mhz() OSCCON = 0b01110110

#define DisableAnalogicInputs()                 \
    ANSEL = 0x00;   /*Default 7F*/              \
    ADCON0 = 0x00;         /*AD MODULE OFF*/    \
    ADCON1 = 0x00          /* AD MODULE OFF*/

// Setea un bit en alto
#define output_high(BIT) \
    BIT = 1
// Setea un bit en bajo
#define output_low(BIT) \
    BIT = 0

// Seteo del timer 1. TMR1LOAD es equivalente a set_timer1
#define TMR1LOAD(ticks) ((void)(TMR1H=((ticks)>>8),TMR1L=((ticks)&0xFF)))
#define set_timer1(ticks)  ((void)(TMR1H=((ticks)>>8),TMR1L=((ticks)&0xFF)))


#endif	/* CONFIG_H */

