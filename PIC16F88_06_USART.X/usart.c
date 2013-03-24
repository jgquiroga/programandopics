/**
 * Rutina necesarias para poder leer o enviar datos por el cable serial de la
 * computadora.
 * @param data
 */

#include <xc.h>
#include "system.h"
#include "usart.h"
/**
 * Permite configurar el puerto USART
 * @param brgh 1 para alta velocidad, 0 para baja velocidad
 * @param sbprg valor elegido de la tabla
 */
void ConfigureUsart(int brgh, int sbprg) {
    // Habilita la conexión serial
    // HAbilitar uart

    TXSTAbits.TX9 = 0;  //  Transmisión de 8-bit
    TXSTAbits.SYNC = 0; // Modo asincrónico
    TXSTAbits.BRGH = brgh; // BRGH

    RCSTAbits.RX9 = 0;  // Recepción de 8-bit
    RCSTAbits.SPEN = 1; // Puerto serial habilitado
    // (configura RB2/SDO/RX/DT y RB5/SS/TX/CK pins como puerto serial)

    SPBRG = sbprg;       // valor de la tabla de bauds

    TXSTAbits.TXEN = 1; // Habilita la transmisión de datos
    RCSTAbits.CREN = 1; // Habilita la recepción de datos
    RCIE = 1;           // Habilita las interrupciones por recibo de datos


}

/*
 * Rutina necesaria para que funcione correctamente el printf.
 * Escribe un caracter en el puerto serial.
 */
void putch(unsigned char data) {
  /* output one byte */
  while(!TXIF)	/* set when register is empty */
    continue;
  TXREG = data;
}

/**
 * Obtiene un caracter desde el puerto serial.
 * @return
 */
unsigned char getch() {
	/* retrieve one byte */
	while(!RCIF)	/* set when register is not empty */
		continue;
	return RCREG;
}

/**
 * Obtiene un caracter desde el puerto serial y lo retransmite.
 * @return
 */
unsigned char getche(void) {
	unsigned char c;
	putch(c = getch());
	return c;
}

