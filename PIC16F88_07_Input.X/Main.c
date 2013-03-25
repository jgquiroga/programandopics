/*
 * File:        main.c
 * PIC:         PIC16F88
 * Author:      Juli�n Quiroga
 *
 * Descripci�n: Programa que enciende y apaga un LED de forma
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
#define posLED  0             // Posici�n en la que se encuentra el Led

#define BUTTON  PORTBbits.RB4 // El bot�n se encuentra conectado en RB4
#define posBUTTON   4         // Posici�n en la que se encuentra el bot�n

// Se agreg� la siguiente configuraci�n al proyecto para que no
// genera nada de c�digo entre las posiciones de memoria E400-FFF
// --ROM=default,-e40-fff
// Esa l�nea le indica al compilador xc8 que tome toda la memoria
// excluyendo lo que est� entre menos.
void main(void)
{
    // Configura el oscilador
    ConfigureOscillator();

    // Configura un 0 en la posici�n que le corresponde al LED
    // y un 1 a todas las dem�s.
    // 0 = Salida, 1 = entrada
    TRISB = ~(1 << posLED) | (1 << posBUTTON);
    // La l�nea anterior es equivalente a
    // TRISB = 0b11111110;

    // Inicializo el led apagado
    LED = 0;

    // Bucle principal
    while(true) {
        // Enciende el led s�lo si est� presionado el bot�n
        LED = BUTTON ? 0 : 1;
    }
}