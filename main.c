/*
 * File:   main.c
 * Author: kagandonmez
 *
 * Created on February 15, 2020, 4:28 PM
 */

// PIC16F88 Configuration Bit Settings

// 'C' source line config statements

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB0      // CCP1 Pin Selection bit (CCP1 function on RB0)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// CONFIG2
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode enabled)


#include <xc.h>
#define _XTAL_FREQ 4000000
#include "uart.h"

void delayFun(int x);

void main(){
	OSCCON = 0b01101010;
    OPTION_REGbits.nRBPU=0;
	TRISB0 = 0;
    TRISB1 = 0;
    TRISB4 = 0;
    //INTCONbits.PEIE = 1;
    //INTCONbits.GIE = 1;
    //PIE1bits.RCIE = 1;
    UART_Init(300);
    RB0 = 1;
    RB1 = 1;
    RB4 = 1;
    char mode = 'o';
    short delay = 0;
    while(1){
        if(RCIF){
            char first = UART_Read();
            char second = UART_Read();
            mode = first;
            if(second == '0')
                delay = 0;
            else if(second == '1')
                delay = 1000;
            else if(second == '2')
                delay = 500;
        }
        if(mode == 'r'){
            RB1 = 1;
            RB4 = 1;
            RB0 = 0;
        } else if(mode == 'b'){
            RB1 = 1;
            RB4 = 0;
            RB0 = 1;
        } else if(mode == 'g'){
            RB1 = 0;
            RB4 = 1;
            RB0 = 1;
        }
        if(delay > 0){
            delayFun(delay);
            RB1 = 1;
            RB4 = 1;
            RB0 = 1;
            delayFun(delay);
        }
    }
}

void delayFun(int x){
    for(int i = 0; i < x; i++){
        __delay_ms(1);
    }
}
