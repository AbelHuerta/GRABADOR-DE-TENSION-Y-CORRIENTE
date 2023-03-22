
#include "USART.h"

void UART_Config(uint8_t speed, uint32_t baudios){
    uint8_t baud;
    X_VALUE(9600,speed,baud);
    
    //ASINCRONO
    TXSTAbits.SYNC = 0;
    
    //1.ESTABLECER TAZA DE BAUDIOS
    SPBRG = baud;
    
    //2.BIT TX/RX. SELECIONA LA TRANSMISION Y RECEPCION DE 8 BITS
    TXSTAbits.TX9 = 0;
    RCSTAbits.RX9 = 0;
    RCSTAbits.SPEN = 1;
    
    //3. PARIEDAD . SIN PARIEDAD YA QUE NO SE SELECCIONO TX/RX DE 9 BITS
    
    //4. BIT STOP;
    
    //HABILITAR TX 
    TXSTAbits.TXEN= 1;
    
    return;
}


void UART_Transmit(uint8_t data){
    //Bit de estado del registro de desplazamiento de transmisión
    //TMRT: 1(VACIO)
    while(!TRMT);
    //los datos a enviar se escriben en el registro txreg
    TXREG = data;
}

//transmite n bytes (pData se almacena en size)
void UART_SendData(uint8_t *pData, uint8_t Size){
    while(Size-->0){
		UART_Transmit(*pData);
	 	pData++;
	}
	return;
}
