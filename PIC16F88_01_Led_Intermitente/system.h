/*
 * File:   system.h
 * Author: Julián Quiroga
 */
/*******************************************************/
/* System Level #define Macros                         */
/*******************************************************/
/**
 * Indica que el pic funcionará a 8MHz.
 * Este macro es necesario para las funciones de delay.
 */
#define _XTAL_FREQ       8000000

/*******************************************************/
/* System Function Prototypes                          */
/*******************************************************/
/**
 * Función que debe configurar el Oscilador
 */
void ConfigureOscillator(void);