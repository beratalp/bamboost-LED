/*
 * File:   main.c
 * Author: kagandonmez
 *
 * Created on February 15, 2020, 4:28 PM
 */

// PIC16F88 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>  //libraries for the PIC microcontrollers
#define _XTAL_FREQ 8000000  //define the crystal frequency for the xc.h
#include "uart.h"

void red_on(int x);//function declaration
void green_on(int x);
void blue_on(int x); 
void cyan_on(int x); 
void yellow_on(int x); 
void magenta_on(int x); 
void white_on(int x); 
void led_off();
void delay(int x);
void main()
{
	OSCCON=0b01111010;
	TRISB= 0b00001111;
	OPTION_REGbits.nRBPU=0;
    //INTCON=0b10010000;
    INTCONbits.PEIE=1;
    INTCONbits.GIE=1;
    PIE1bits.TXIE=1;
    PIE1bits.RCIE=1;
    for(;;);
}
void red_on(int x)
{
    if(x==0)
    {
        RB7=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB7=0;
            delay(x);
            RB7=1;
            delay(x);
	    } 
    }
}
void green_on(int x)
{
    if(x==0)
    {
        RB6=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB6=0;
            delay(x);
            RB6=1;
            delay(x);
	    } 
    }
}
void blue_on(int x)
{
    if(x==0)
    {
        RB4=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB4=0;
            delay(x);
            RB4=1;
            delay(x);
	    } 
    }
}
void cyan_on(int x)
{
    if(x==0)
    {
        RB4=0;
        RB6=0;
       
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB6=0;
            RB4=0;
            delay(x);
            RB6=1;
            RB4=1;
            delay(x);
	    } 
    }
}
void yellow_on(int x)
{
    if(x==0)
    {
        RB7=0;
        RB6=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB7=0;
            RB6=0;
            delay(x);
            RB7=1;
            RB6=1;
            delay(x);
	    } 
    }	
}
void magenta_on(int x)
{
    if(x==0)
    {
        RB7=0;
        RB4=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB7=0;
            RB4=0;
            delay(x);
            RB7=1;
            RB4=1;
            delay(x);
	    } 
    }	
}
void white_on(int x)
{
    if(x==0)
    {
        RB7=0;
        RB6=0;
        RB4=0;
    }
    else
    {
       for(;;) //int i=0;i<x;i++
	    {
            RB7=0;
            RB6=0;
            RB4=0;
            delay(x);
            RB7=1;
            RB6=1;
            RB4=1;
            delay(x);
	    } 
    }
}

void led_off(void)
{
    RB7=1;
    RB6=1;
    RB4=1;
}
void delay(int x){
    for(int i = 0; i < x; i++){
        __delay_ms(1);
    }
}
void __interrupt() isr()
{
	if (INTCONbits.INTF==1)  
	{
        char first=UART_Read();
        char second=UART_Read();
        if(first=='r'||first=='g'||first=='b')
        {
            if(second=='0'||second=='1'||second=='2')
            {   if(first=='r')
                {
                    if(second=='0')
                    {
                        red_on(0);
                    }
                    if(second=='1')
                    {
                        red_on(1000);
                    }
                    if(second=='2')
                    {
                        red_on(500);
                    }
                }
                if(first=='b')
                {
                    if(second=='0')
                    {
                        blue_on(0);
                    }
                    if(second=='1')
                    {
                        blue_on(1000);
                    }
                    if(second=='2')
                    {
                        blue_on(500); 
                    }
                }
                if(first=='g')
                {
                    if(second=='0')
                    {     
                        green_on(0);
                    }
                    if(second=='1')
                    {
                        green_on(1000);
                    }
                    if(second=='2')
                    {
                        green_on(500);  
                    }
                } 
                else
                {
                    led_off();
                }
            }
            else
            {
                led_off();
            }
        }
    INTCONbits.INTF=0;
}

}
