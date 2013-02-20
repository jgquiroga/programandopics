/*
 * File:   system.h
 * Author: Juli�n Quiroga
 */
/*******************************************************/
/* System Level #define Macros                         */
/*******************************************************/
/**
 * Indica que el pic funcionar� a 8MHz.
 * Este macro es necesario para las funciones de delay.
 */
#define _XTAL_FREQ       8000000

/*******************************************************/
/* System Function Prototypes                          */
/*******************************************************/
/**
 * Funci�n que debe configurar el Oscilador
 */
void ConfigureOscillator(void);