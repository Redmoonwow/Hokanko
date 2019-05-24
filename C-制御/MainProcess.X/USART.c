
#include <xc.h>
#include <stdio.h>
#include <pic18f4553.h>
#include <string.h>

#include "USART.h"

void initUART(){
    
    SPBRG = SPBRG_DATA;
    TXSTA = (BIT_9DATA | BRGH_DATA | 0x20);
    RCSTA = (BIT_9DATA | 0x90);
    
}

void sentsimple(unsigned char byte ){
    
    while(!TXIF);
    TXREG = byte;
    
}

void sent(const char *data,int cnt){ //char
    int i;
    
    for(i =0 ; i < cnt ; i++){
            while(!TXIF);
            TXREG = *data++;
    }
}


unsigned char getsimple(){
    while(!RCIF);
    
    return RCREG;
    
}
