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

#define BUTTON  PORTBbits.RB4 // El botón se encuentra conectado en RB4
#define posBUTTON   4         // Posición en la que se encuentra el botón

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
    TRISB = ~(1 << posLED) | (1 << posBUTTON);
    // La línea anterior es equivalente a
    // TRISB = 0b11111110;

    // Inicializo el led apagado
    LED = 0;
    uint8_t contadorDeRebotes;      // Cuenta los rebotes de un input
    uint8_t shadowPortB = 0;        // Shadow copy del puerto B

    // Bucle principal
    for(;;) {
        // Espera hasta que el botón esté presionado unos 10 ms como mínimo
        for(contadorDeRebotes = 0 ; contadorDeRebotes < 10 ; contadorDeRebotes++) {
            __delay_ms(1);
            if(BUTTON == 1)
                contadorDeRebotes = 0;
        }

        shadowPortB ^= 1 << posLED; // Hace un XOR entre el valor actual y 1
                                    // sobre el shadow register
        PORTB = shadowPortB;        // Copia el valor del registro al puerto B

        LED ^= 1;   // Hace un XOR entre el valor actual y 1
                    // Con esto obtiene el valor contrario.

        // Espera hasta que el botón esté levantado unos 10 ms como mínimo
        for(contadorDeRebotes = 0 ; contadorDeRebotes < 10 ; contadorDeRebotes++) {
            __delay_ms(1);
            if(BUTTON == 0)
                contadorDeRebotes = 0;
        }
    }

    //  // Código sin shadow registers
    //    for(;;) {
    //        // Espera hasta que el botón esté presionado unos 10 ms como mínimo
    //        for(contadorDeRebotes = 0 ; contadorDeRebotes < 10 ; contadorDeRebotes++) {
    //            __delay_ms(1);
    //            if(BUTTON == 1)
    //                contadorDeRebotes = 0;
    //        }
    //
    //        LED ^= 1;   // Hace un XOR entre el valor actual y 1
    //                    // Con esto obtiene el valor contrario.
    //
    //        // Espera hasta que el botón esté levantado unos 10 ms como mínimo
    //        for(contadorDeRebotes = 0 ; contadorDeRebotes < 10 ; contadorDeRebotes++) {
    //            __delay_ms(1);
    //            if(BUTTON == 0)
    //                contadorDeRebotes = 0;
    //        }
    //    }


    // // Código con problemas de rebote
    //    while(true) {
    //        while(BUTTON == 1) {
    //        }
    //        LED = 1;
    //
    //        while(BUTTON == 0) {
    //        }
    //        LED = 0;
    //    }
}