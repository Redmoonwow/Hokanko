// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>

int flag;

void interrupt ISR(void){

    GPIObits.GP2 = 1;
    INTCONbits.GIE = 0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 0;
    
    
}



void main(void) {
    
    OSCCON = 0b00000001;
    TRISIO = 0b00100000;
    GPIO = 0x00;
    OPTION_REG = 0b00000101;
    ANSEL = 0b00000000;
    
    for(;;){
        
        if(GPIObits.GP5 == 0 && flag == 0){
        
        TMR0 = 22;
        INTCONbits.GIE = 1;
        INTCONbits.T0IF = 0;
        INTCONbits.T0IE = 1;
        flag = 1;
        }
        
        
        if(GPIObits.GP5 == 1){
        
        INTCONbits.T0IE = 0;
        INTCONbits.T0IF = 0;
        INTCONbits.GIE = 0;
        GPIObits.GP2 = 0;
        flag = 0;
        }
    }
}
