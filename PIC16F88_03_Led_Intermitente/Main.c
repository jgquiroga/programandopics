/*
 * File:        main.c
 * PIC:         PIC16F88
 * Author:      Julián Quiroga
 *
 * Descripción: Programa que enciende y apaga un LED de forma
 *              intermitente en RB0 Cargado desde Bootloader AN1310.
 */
#include <xc.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "system.h"

// Project must reserve access bank memory used by the bootloader
// interrupt vector routine for saving W and PCLATH temporarily
// while passing control to application remapped interrupt vector.
//
// Enter menu option: Project->Build Options->Project
// On the Global tab, set RAM ranges to "default,-7E-7F" to reserve 7Eh and 7Fh.
//unsigned char W_TEMP @ 0x7F;
//unsigned char PCLATH_TEMP @ 0x7E;

#define LED     PORTBbits.RB0 // El Led se encuentra conectado en RB0
#define posLED  0             // Posición en la que se encuentra el Led


// Se agregó la siguiente configuración al proyecto para que no
// genera nada de código entre las posiciones de memoria E400-FFF
// --ROM=default,-e40-fff
// Esa línea le indica al compilador xc8 que tome toda la memoria
// excluyendo lo que está entre menos.
void main(void)
{
    // Configura el oscilador
    ConfigureOscillator();

    // Configura un 0 en la posición que le corresponde al LED
    // y un 1 a todas las demás.
    // 0 = Salida, 1 = entrada
    TRISB = ~(1 << posLED);
    // La línea anterior es equivalente a
    // TRISB = 0b11111110;

    // Bucle principal
    while(true) {

        LED = 1;    // Setea en estado alto (High) el LED

        __delay_ms(500); // Se queda esperando 500 milisegundos
        //__delay_us(500);
        LED = 0;    // Setea en estado bajo (Low) el LED

        __delay_ms(500);
        //__delay_us(500);

    }
}