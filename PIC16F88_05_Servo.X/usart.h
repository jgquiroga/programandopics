/*
 * File:   usart.h
 * Author: Administrator
 *
 * Created on 11 de septiembre de 2012, 23:59
 */

#ifndef USART_H
#define	USART_H

#ifdef	__cplusplus
extern "C" {
#endif

void putrs1USART(const char *data);
void putrsUSART(const char *data);
void putByteUSART(unsigned char data);

#define EnableUSART()                                       \
    // HAbilitar uart                                       \
    TXSTAbits.TX9 = 0;  //  Selects 8-bit transmission      \
    TXSTAbits.SYNC = 0; // Asynchronous mode                \
    TXSTAbits.BRGH = 1; // Sets to High Speed               \
    RCSTAbits.RX9 = 0;  // Selects 8-bit transmission       \
    RCSTAbits.SPEN = 1; // Serial port enabled              \
    SPBRG = 64;       // (configures RB2/SDO/RX/DT and RB5/SS/TX/CK pins as serial port pins) \
             \
    TXSTAbits.TXEN = 1; // Habilita la transmisión de datos \
    RCSTAbits.CREN = 1; // Habilita la recepción de datos   \
    RCIE = 1;           // Habilita las interrupciones por recibo de datos \
    __delay_ms(80)



  //SPBRG = 0x08;       // sets to 57.6k baud

#ifdef	__cplusplus
}
#endif

#endif	/* USART_H */

