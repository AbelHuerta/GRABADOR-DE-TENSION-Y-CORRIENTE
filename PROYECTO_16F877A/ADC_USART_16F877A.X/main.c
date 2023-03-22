/*
 * File:   main.c
 * Author: abelh
 *
 * Created on 8 de diciembre de 2022, 10:28 PM
 */


//CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include <xc.h>
#include <pic16f877a.h>
#define _XTAL_FREQ  20000000UL

#include <stdio.h> // (habilita:"sprintf")
#include <stdint.h> //
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "USART.h"


float tension;
#define ADC_CH3 3

//conversion ADC
void ADC_Convertion(void);

//Lectura ADC
uint16_t ADC_Read(uint8_t CHx);


uint8_t bufferTx[20];
uint16_t bufferLen;	//NUMEROS DE BYTES A TRANSMITIR
uint16_t data;		//CONVERSION ADC

void main(void) {
    
    
    
    UART_Config(HIGH_SPEED,9600);
    ADC_Convertion();
    while(1){
    
        data = ADC_Read(ADC_CH3);
        tension = data*5.0/1024.0 ;
		bufferLen = sprintf(bufferTx,"%.02f\r\n",tension);
		UART_SendData(bufferTx,bufferLen);
		__delay_ms(1200); //1500,
    }
    return;
}

void ADC_Convertion(void){
     
    
    //La conversion no esta en proceso
    ADCON0bits.GO_DONE = 0;
    //Se habilita el ADC
    ADCON0bits.ADON = 1;
    //Definir entradas analogas y Voltaje de referencia
    ADCON1bits.PCFG3 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG0 = 0;
    
    //CANAL DE CONVERSION
    //ADCON0bits.CHS2 = 0;
    //ADCON0bits.CHS1 = 1;
    //ADCON0bits.CHS0 = 1;
    
    //tiempo de conversión A/D ; /64
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 1;
    ADCON1bits.ADCS2 = 1;
    
    //justificacion
    ADCON1bits.ADFM = 1;  
    
    return;
}


uint16_t ADC_Read(uint8_t CHx){
    
    ADCON0 |= 0xC7 | (3<<CHx);
    //Inicia la conversion
    ADCON0bits.GO_DONE = 1;
    //Esperar hasta que la conversion termine
    while(ADCON0bits.GO_DONE) continue;
    __delay_ms(2);
    
    
    return ((ADRESH<<8)+ADRESL);
    
}
