/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> 

//ETIQUETAS
#define F_OSC   20000000UL
#define HIGH_SPEED BRGH
#define LOW_SPEED    0

#define X_VALUE(BAUD,Brgh,X) {if(Brgh == BRGH){\
                                X = (uint8_t)((F_OSC/(16UL*BAUD))-1UL);\
                                TXSTAbits.BRGH = 1;}                    \
                              else{\
                                X = (uint8_t)((F_OSC/(64UL*BAUD))-1UL);\
                                TXSTAbits.BRGH = 0;}}                  \

/*****************************************************************************/
/*                          PROTOTIPO DE FUNCIONES                           */
/*****************************************************************************/

/*CONFIGURACION DEL UART*/
/*
 speed: division entre 8 o 16
 bauidos: tasa de baudios deseada
*/
void UART_Config(uint8_t speed, uint32_t baudios);

/*TRANSMITE UN BYTE POR EL PIN TX*/
/*
 Data: a transmitir
*/
void UART_Transmit(uint8_t data);


/*TRANSMITE N BYTES*/

void UART_SendData(uint8_t *pData, uint8_t Size);

#endif	/* XC_HEADER_TEMPLATE_H */

