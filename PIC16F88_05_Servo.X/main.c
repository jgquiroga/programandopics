/**
 * MCU:         PIC16F88
 * Frecuencia:  8 MHz, Oscilador interno Sin ClockOut
 * Puerte serie conectado
 * Bootloader:  An1310
 *
 *
 * Título:      Manejo de 4 servos por USART
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "usart.h"

// Project must reserve access bank memory used by the bootloader
// interrupt vector routine for saving W and PCLATH temporarily
// while passing control to application remapped interrupt vector.
//
// Enter menu option: Project->Build Options->Project
// On the Global tab, set RAM ranges to "default,-7E-7F" to reserve 7Eh and 7Fh.
//unsigned char W_TEMP @ 0x7F;
//unsigned char PCLATH_TEMP @ 0x7E;


// Definición de las salidas de cada servo:
#define SERVO1  PORTAbits.RA0
#define SERVO2  PORTAbits.RA1
#define SERVO3  PORTAbits.RA2
#define SERVO4  PORTAbits.RA6
// No disponibles, se utiliza el RA4 como dummy
#define SERVO5  PORTAbits.RA4
#define SERVO6  PORTAbits.RA4
#define SERVO7  PORTAbits.RA4
#define SERVO8  PORTAbits.RA4

#define  Bit_PWM0   SERVO1              //Bit 0 puerto A Salida modulación 0
#define  Bit_PWM1   SERVO2              //Bit 1 puerto A Salida modulación 1
#define  Bit_PWM2   SERVO3              //Bit 2 puerto A Salida modulación 2
#define  Bit_PWM3   SERVO4              //Bit 3 puerto A Salida modulación 6
#define  Bit_PWM4   SERVO5              //Bit 0 puerto A Salida modulación 0
#define  Bit_PWM5   SERVO6              //Bit 1 puerto A Salida modulación 1
#define  Bit_PWM6   SERVO7              //Bit 2 puerto A Salida modulación 2
#define  Bit_PWM7   SERVO8              //Bit 3 puerto A Salida modulación 6

const uint16_t Ticks4Window     = 12500;   // PWM Window for servo = 2.5 ms x 8 = 20 ms
const uint16_t Ticks4Minimum    = 3500;    // PWM High for Minimum Position = 0.7 ms
const uint16_t Ticks4Center     = 7500;    // PWM High for Center Position = 1.5 ms
const uint16_t Ticks4Maximum    = 11500;   // PWM High for Maximum Position = 2.3 ms

/********************** Variables para generación PWM *************************/

uint8_t PWM0=0,PWM1=0,PWM2=0,PWM3=0,PWM4=0,PWM5=0,PWM6=0,PWM7=0; //Valores de las señales PWM
uint8_t control_PWM=0;

/******************************************************************************/
/******************* FUNCIÓN GENERACIÓN MODULACIONES PWM **********************/



uint8_t contador = 1;
uint8_t LAHL = 1; // Permite switchear de alto a bajo el pulso del servo
uint16_t tick; // Guarda los valores para el Timer 1
uint16_t SERVOH, SERVOL; // Guarda los valores para el alto y el bajo del servo
uint8_t flag = 1;   // Flag para el cambio de posición
uint16_t POSICION=90;//Inicializa a 90 grados

unsigned char a=33,b=0,udata;

void pres_menu(void) ;
void generacion_pwm (void);   //genera señales moduladas para control de servos
void processSSC(void) ;
void moveServo(uint8_t servo, uint8_t posicion) ;


// Comando recibido
static volatile char command;
// True si recibió algún valor
static volatile bool recived;


// Array con los valores en High actuales de cada servo
static uint16_t Servo_PWM[8]={7500,7500,7500,7500,7500,7500,7500,7500};
static uint8_t Servo_Idx=0;

// Estas variables indican que servos estarán activos
static bool SERVO1_ON=1;
static bool SERVO2_ON=1;
static bool SERVO3_ON=1;
static bool SERVO4_ON=1;
static bool SERVO5_ON=0;
static bool SERVO6_ON=0;
static bool SERVO7_ON=0;
static bool SERVO8_ON=0;

static bool flag_Phase;

static uint16_t Ticks4NextInterrupt=53036;
/*
 * Vector de interrupciones
 */
static void interrupt isr(void) {
    // Si se recibió al mismo tiempo una interrupción
    // por Serial, setea un flag para que no se lea
    if(RCIF && !TMR1IF && RCIE) {
        command = getch();
        recived = true;
        RCIF = 0;
    }

    // Si ocurrió una interrupción por timer 1
    if(PIR1bits.TMR1IF) {
        // Fase alta
        if(flag_Phase==0) {
            // Activa el servo que esté actualmente en el índice
            if(Servo_Idx==0 && SERVO1_ON) output_high(SERVO1);
            if(Servo_Idx==1 && SERVO2_ON) output_high(SERVO2);
            if(Servo_Idx==2 && SERVO3_ON) output_high(SERVO3);
            if(Servo_Idx==3 && SERVO4_ON) output_high(SERVO4);
            if(Servo_Idx==4 && SERVO5_ON) output_high(SERVO5);
            if(Servo_Idx==5 && SERVO6_ON) output_high(SERVO6);
            if(Servo_Idx==6 && SERVO7_ON) output_high(SERVO7);
            if(Servo_Idx==7 && SERVO8_ON) output_high(SERVO8);

            // Calcula los ticks para la siguiente interrupción (duración del DutyCycle)
            Ticks4NextInterrupt = 65535 - Servo_PWM[Servo_Idx];
            // Setea el timer
            set_timer1(Ticks4NextInterrupt);
        } else {
            if(Servo_Idx==0 && SERVO1_ON) output_low(SERVO1);
            if(Servo_Idx==1 && SERVO2_ON) output_low(SERVO2);
            if(Servo_Idx==2 && SERVO3_ON) output_low(SERVO3);
            if(Servo_Idx==3 && SERVO4_ON) output_low(SERVO4);
            if(Servo_Idx==4 && SERVO5_ON) output_low(SERVO5);
            if(Servo_Idx==5 && SERVO6_ON) output_low(SERVO6);
            if(Servo_Idx==6 && SERVO7_ON) output_low(SERVO7);
            if(Servo_Idx==7 && SERVO8_ON) output_low(SERVO8);

            // Calcula los ticks para la siguiente interrupción (en 0)
            Ticks4NextInterrupt = 65535 - Ticks4Window + Servo_PWM[Servo_Idx];
            set_timer1(Ticks4NextInterrupt);

            // Si llegó al servo 8 debe empezar de nuevo
            if(++Servo_Idx>7) Servo_Idx=0;
        }
        PIR1bits.TMR1IF = 0; // Limpia el valor de la interrupcion por timer

        // cambia entre fase 1 y fase 2
        flag_Phase = !flag_Phase;
    }
}


// Se agregó la siguiente configuración al proyecto para que no
// genera nada de código entre las posiciones de memoria E400-FFF
// --ROM=default,-e40-fff
// Esa línea le indica al compilador xc8 que tome toda la memoria
// excluyendo lo que está entre menos.
void main(void)
{
    // Configuración del clock interno de 8MHz
    //DefineInternalClock8Mhz();

    // Esta línea es importante para que las salidas de A se comporten
    // como salidas digitales. Sino se comportan como analógicas
    DisableAnalogicInputs();

    //Timer1 Registers Prescaler= 1 - TMR1 Preset = 65535 - Freq = 2000000.00 Hz - Period = 0.000000 seconds
    //T1CONbits.T1CKPS = 0b00;    // Prescaler 0
    T1CONbits.T1CKPS1 = 0;   // bits 5-4  Prescaler Rate Select bits
    T1CONbits.T1CKPS0 = 0;  // bit 4
    T1CONbits.T1OSCEN = 1; // bit 3 Timer1 Oscillator Enable Control bit 1 = on
    T1CONbits.T1INSYNC = 1;  // bit 2 Timer1 External Clock Input Synchronization Control bit...1 = Do not synchronize external clock input
    T1CONbits.TMR1CS = 0;   // usa el clock interno
    T1CONbits.TMR1ON = 1;   // Enciende el timer1

    TMR1H = 207;             // preset for timer1 MSB register
    TMR1L = 44;             // preset for timer1 LSB register

    // Interrupt Registers
    INTCON = 0;             // clear the interrpt control register
    INTCONbits.TMR0IE = 0;  // bit5 TMR0 Overflow Interrupt Enable bit...0 = Disables the TMR0 interrupt
    PIR1bits.TMR1IF = 0;            // clear timer1 interupt flag TMR1IF
    PIE1bits.TMR1IE  =   1;         // enable Timer1 interrupts
    INTCONbits.TMR0IF = 0;          // bit2 clear timer 0 interrupt flag
    INTCONbits.GIE = 1;     // Interrupciones globales desactivadas
    INTCONbits.PEIE = 1;    // Interrupciones por perifericos desactivada

    // Todo el puerto A es OUTPU excepto RA5 que es MCLR
   TRISA = 0;

   command=0;

    // Habilita la conexión serial
        // HAbilitar uart

    TXSTAbits.TX9 = 0;  //  Selects 8-bit transmission
    TXSTAbits.SYNC = 0; // Asynchronous mode
    TXSTAbits.BRGH = 1; // Sets to High Speed

    RCSTAbits.RX9 = 0;  // Selects 8-bit transmission
    RCSTAbits.SPEN = 1; // Serial port enabled
                        // (configures RB2/SDO/RX/DT and RB5/SS/TX/CK pins as serial port pins)

    SPBRG = 64;       // sets to 19200 baud

    TXSTAbits.TXEN = 1; // Habilita la transmisión de datos
    RCSTAbits.CREN = 1; // Habilita la recepción de datos
    RCIE = 1;           // Habilita las interrupciones por recibo de datos
    __delay_ms(80);

    for(;;) {
        processSSC();
    }
}

/**
 * Método que permite procesar el protocolo SSC de servos enviado
 * por la pc.
 */
void processSSC(void) {
    // Guardar el número de servo a posicionar
    uint8_t servoActual = 0;
    // Guarda la posición
    uint8_t posicionActual = 0;

    // Si se recibió un dato
    if(recived) {
        // Setea el flag de recibido en false para que no pase si es que se
        // envió un valor distinto a 255
        recived = false;
        
        // Si es el comando de sincronización, espera a que llegue el número
        // de servo a mover
        if(command == 255){

            while(!recived) { }
            // Se guarda el número de servo
            servoActual = command;
            // Si se recibió el comando de sincronización volver al principio
            if(servoActual == 255) return;

            // Si se recibió un valor de servo válido, vuelve a quedar a la espera
            // de un valor de posición de servo
            if(servoActual < 8 ) {
                recived = false;

                while(!recived) { }
                // Se guarda la posición actual
                posicionActual = command;

                // Si se recibió el comando de sincronización volver al principio
                if(posicionActual == 255) return;

                // Posiciona el servo actual:
                //Servo_PWM[servoActual]=(posicionActual * 16) + 1600;
                moveServo(servoActual,posicionActual);
            }
        }
    }
}

void moveServo(uint8_t servo, uint8_t posicion) {
    // Posiciona el servo actual:
    // TODO: 16 debe ser una constante al igual que 1600
    Servo_PWM[servo]=(posicion * 39) + 4000 ;
}