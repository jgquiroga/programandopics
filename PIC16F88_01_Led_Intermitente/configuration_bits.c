/**
 * File:        configuration_bits.c
 * PIC:         PIC16F88
 * Author:      Julián Quiroga
 *
 * Descripción: Configura el pic para que utilice
 *              el oscilador interno y el pin 4
 *              como Reset
 */
#include <xc.h>

__CONFIG(MCLRE_ON & CP_OFF & CPD_OFF & LVP_OFF & BOREN_OFF &
         WDTE_OFF & FOSC_INTOSCIO & PWRTE_OFF);
__CONFIG(IESO_OFF & FCMEN_OFF);