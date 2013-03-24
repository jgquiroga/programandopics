/*
 * File:   usart.h
 * Author: Julián Quiroga
 */
/*******************************************************/
/* USART Function Prototypes                          */
/*******************************************************/
/**
 * Función que debe configurar el Oscilador
 * @param brgh 1 para alta velocidad, 0 para baja velocidad
 * @param sbprg valor elegido de la tabla
 */
void ConfigureUsart(int brgh, int sbprg);

/*
 * Rutina necesaria para que funcione correctamente el printf.
 * Escribe un caracter en el puerto serial.
 */
void putch(unsigned char data);

/**
 * Obtiene un caracter desde el puerto serial.
 * @return
 */
unsigned char getch();

/**
 * Obtiene un caracter desde el puerto serial y lo retransmite.
 * @return
 */
unsigned char getche(void);
