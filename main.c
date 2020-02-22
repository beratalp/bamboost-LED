/*
 * File:   main.c
 * Author: beratalp
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

void variableDelay(int x);

void main(){
	OSCCON = 0b01101010; //set the internal oscillator to 4MHz
    OPTION_REGbits.nRBPU=0; //enable internal pull-up resistors
    //mark LED connections as digital outputs
	TRISB0 = 0; 
    TRISB1 = 0;
    TRISB4 = 0;
    UART_Init(300); //enable the UART port, the baud rate is 300
    //shut of the LED by pulling the ports up.
    RB0 = 1;
    RB1 = 1;
    RB4 = 1;
    //declare mode variables
    char mode = 'o';
    short delay = 0;
    //enter the main loop
    while(1){
        if(RCIF){ //check for the UART receive buffer
            char first = UART_Read(); //read the first character
            char second = UART_Read(); //read the second character
            mode = first; //set the color mode as the first char
            if(second == '0') //set the blink mode through the delay
                delay = 0;
            else if(second == '1')
                delay = 1000;
            else if(second == '2')
                delay = 500;
        }
        if(mode == 'r'){ //red
            RB1 = 1;
            RB4 = 1;
            RB0 = 0;
        } else if(mode == 'b'){ //blue
            RB1 = 1;
            RB4 = 0;
            RB0 = 1;
        } else if(mode == 'g'){ //green
            RB1 = 0;
            RB4 = 1;
            RB0 = 1;
        } else if(mode == 'o'){ //off
            RB1 = 1;
            RB4 = 1;
            RB0 = 1;
        } else { //if an invalid char is sent, send an error '00' string, and turn the LED off
            UART_Write_Text("00"); 
            mode = 'o';
        }
        if(delay > 0){ //if there should be a blink, enable it
            variableDelay(delay);
            RB1 = 1;
            RB4 = 1;
            RB0 = 1;
            variableDelay(delay);
        }
    }
}

/**
 * This function implements a variable delay function, since Microchip's implementation
 * of __delay_ms and __delay_us only supports constant parameters.
 * The function is not as exact as the __delay_ms(), since it requires additional clock cycles to run.
 * @param x delay (in milliseconds)
 */
void variableDelay(int x){
    for(int i = 0; i < x; i++){
        __delay_ms(1);
    }
}
