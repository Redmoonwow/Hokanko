/*
 * File:   main.c
 * Author: Owner
 *
 * Created on 2017/11/07, 10:35
 */



#include <xc.h>

#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = OFF        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#define _IDLESTOP_INPUT_ON GPIObits.GP5 == 0  //IDLESTOPボタンを押したとき
#define _IDLESTOP_INPUT_OFF GPIObits.GP5 == 1  //IDLESTOPボタンを離したとき
#define _IDLESTOP_OUTPUT_ON GPIObits.GP2 = 1  //IDLESTOPリレーを入れる
#define _IDLESTOP_OUTPUT_OFF GPIObits.GP2 = 0  //IDLESTOPリレーを切る
#define PTO_ON_ON GPIObits.GP4 == 0 //PTO_ON信号が入っている
#define PTO_ON_OFF GPIObits.GP4 == 1 //PTO_ON信号が入っていない

void SECSTART(int TMR0_CNT);

int PTO__ON;  //PTOが入ったときのステップカウント
int SEC;  //秒カウント
int STEP; //アイドルストップのステップ
int TRG; //1クリックのみにするためのトリガー
int IDLESTOP; //IDLESTOPの状態


void interrupt ISR(void){

    SEC = SEC + 1;           //設定時間になったら秒カウントを１上げる
    INTCONbits.GIE = 0; //全割込み禁止
    INTCONbits.T0IE = 0; //タイマー0割込み禁止
    INTCONbits.T0IF = 0; //タイマー0フラグクリア
    
}

void main(void) {
    
    /******初期化******/
    OSCCON = 0b00000001; //クロック31[kHz],システムクロックはOSCCONのbit5-6で設定
    /*****/
    /*bit5-6の設定*/
    /*
     * 000
     */
    OPTION_REG = 0b10000101;
    ANSEL = 0x00;
    TRISIObits.TRISIO2 = 0;
    TRISIObits.TRISIO4 = 1;
    TRISIObits.TRISIO5 = 1;
    _IDLESTOP_OUTPUT_OFF;
    /********************/
    
    SEC = 4;
    STEP = 0;
    PTO__ON = 0;
    TRG = 0;
    IDLESTOP = 0;
    
    for(;;){
        /*************************PTO監視***************************/
        
        /*************************PTO_ON****************************/
        if(PTO_ON_ON && STEP == 0 && PTO__ON == 0 && SEC == 4){
            _IDLESTOP_OUTPUT_ON;
            SEC = 0;
            PTO__ON = 1;
            SECSTART(232);
        }
        
        if(PTO_ON_OFF && PTO__ON == 1){
            TRG = 1;
        }
        
        if(STEP == 0 && PTO__ON == 1 && SEC == 1){
            _IDLESTOP_OUTPUT_OFF;
            PTO__ON = PTO__ON + 1;
            SECSTART(232);
            if(TRG == 1){
                PTO__ON = PTO__ON + 1;
                TRG = 0;
            }
        }

        /************************************************************/
        
        /***************************PTO_OFF**************************/
        
        if(PTO_ON_OFF && PTO__ON == 2){
            PTO__ON = PTO__ON + 1;;
        }
        
        if(STEP == 0 && PTO__ON == 3 && SEC == 2){
            _IDLESTOP_OUTPUT_ON;
            PTO__ON = PTO__ON + 1;
            SECSTART(232);
        }
         
        if(STEP == 0 && PTO__ON == 4 &&  SEC == 3){
            _IDLESTOP_OUTPUT_OFF;
            PTO__ON = PTO__ON + 1;
            SECSTART(232);
        }
        
        if(PTO_ON_OFF && PTO__ON == 5 && SEC == 4){
            PTO__ON = 0;
        }
        
        /************************************************************/
        
        /****************************IDLESTOP_OFF********************************/
        
        
        if(_IDLESTOP_INPUT_ON && STEP == 0 && SEC == 4 && TRG == 0  && PTO__ON == 0){
            _IDLESTOP_OUTPUT_ON;
            SEC = 0;
            TRG = 1;
            STEP = STEP + 1;
            SECSTART(232);
        }
        
        if(_IDLESTOP_INPUT_OFF && STEP == 1 && PTO__ON == 0){
            STEP = STEP + 1;
        }
        
        if(SEC == 1 && STEP == 2 && PTO__ON == 0){
            _IDLESTOP_OUTPUT_OFF;
            TRG = 0;
            STEP = STEP + 1;
            SECSTART(232);
        }
        
        if(_IDLESTOP_INPUT_OFF && SEC == 2 && STEP == 3 && PTO__ON == 0){
            STEP = STEP + 1;
        }
  
        /******************************************************/
        /*PTO_ON監視*/
        if(PTO_ON_ON && STEP == 4 && PTO__ON == 0){
            PTO__ON = 1;
        }
        
        if(PTO_ON_OFF && STEP == 4 & PTO__ON == 1){
            PTO__ON = 0;
        }
        /***********/
        
        if(_IDLESTOP_INPUT_ON && STEP == 4 && SEC == 2 && PTO__ON == 0){
            _IDLESTOP_OUTPUT_ON;
            STEP = STEP + 1;
            SECSTART(232);
        }
        
        if(_IDLESTOP_INPUT_OFF && STEP == 5 && PTO__ON == 0){
            STEP = STEP + 1;
        }
        
        if(SEC == 3 && STEP == 6 && PTO__ON == 0){
            _IDLESTOP_OUTPUT_OFF;
            STEP = STEP +1;
            SECSTART(232);
        }
        
        if(_IDLESTOP_INPUT_OFF && SEC == 4 && STEP == 7 && PTO__ON == 0){
            STEP = 0;
        }
        
        /*******************************IDLESTOP_ON*****************************/
        
    }
    return;
}

void SECSTART (int TMR0_CNT) {
    TMR0 = TMR0_CNT;
    INTCONbits.GIE = 1;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
}