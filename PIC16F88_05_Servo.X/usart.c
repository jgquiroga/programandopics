/**
 * Rutina necesarias para poder leer o enviar datos por el cable serial de la
 * computadora.
 * @param data
 */

#include <xc.h>

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

