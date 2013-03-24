/*
 * File:   config.c
 * Author: Administrator
 *
 * Created on 11 de septiembre de 2012, 23:32
 */
/******************************************************************************/
/* Main Files to Include                                                      */
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <string.h>
#include <stdbool.h>

/******************************************************************************/
/* Configuration Bits                                                         */
/*                                                                            */
/* Refer to your Hi-Tech User Manual in the PICC installation directory       */
/* /doc folder for more information on filling in configuration bits.         */
/* In addition, configuration bit mnemonics can be found in your              */
/* PICC\version\include\<processor name>.h file for your device.  For         */
/* additional information about what the hardware configurations mean in      */
/* terms of device operation, refer to the device datasheet.                  */
/*                                                                            */
/******************************************************************************/

// Las configuraciones deben estar separadas en 2 para que no haya problemas
__CONFIG(MCLRE_ON & CP_OFF & CPD_OFF & LVP_OFF & BOREN_OFF & WDTE_OFF & FOSC_HS & PWRTE_OFF);
__CONFIG(IESO_OFF & FCMEN_OFF);