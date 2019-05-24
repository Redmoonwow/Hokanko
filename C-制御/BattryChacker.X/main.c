/*
 * File:   main.c
 * Author: Owner
 *
 * Created on 2017/12/01, 9:20
 */


// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select bit (MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Detect (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)

#include <xc.h>

#define Y_LED_ON GPIObits.GP5=1//温度注意ランプオン
#define Y_LED_OFF GPIObits.GP5=0//温度注意ランプオフ
#define R_LED_ON GPIObits.GP4=1//電圧注意ランプオン
#define R_LED_OFF GPIObits.GP4=0//電圧注意ランプオフ
#define V_ON GPIObits.GP2==0//+Vつながっている
#define V_OFF GPIObits.GP2==1//+Vきれている

int SEC;//タイマー定数
int GL_CH;//ADコンバータチャンネルのグローバル定数
int STEP;//温度監視ステップ
int RED_STEP;//+V監視ステップ
int ADC_STEP;//ADコンバータステップ
int R_ERROR;//赤LED点灯中
int Y_ERROR;//黄色LED点灯中
int REF_DATA;//基準値データ
int SENSOR_DATA;//センサー値データ
int TMR0_NOW;//タイマー
int Y_DANGER;//温度1秒待ちステータス
int R_DANGER;//+V1秒監視中ステータス

void interrupt ISR(void){
    SEC = SEC + 1;           //設定時間になったら秒カウントを１上げる
    INTCONbits.GIE = 0; //全割込み禁止
    INTCONbits.T0IE = 0; //タイマー0割込み禁止
    INTCONbits.T0IF = 0; //タイマー0フラグクリア
    TMR0_NOW = 0;//タイマー0使用中クリア
    
}

void SECSTART_64(int TMR0_CNT);
void ADCONV(int CH);
void CHECKTEMP();
void FINALCHECKTEMP();

void main(void) {
    
    /*************INIT************/
    OSCCON = 0b00000001;
    OPTION_REG = 0b00000101;
    ADCON0 = 0b10000000;
    ANSEL = 0b00110011;
    INTCONbits.GIE =0;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE =0;
    INTCONbits.PEIE = 0;
    PIE1bits.ADIE =0;
    PIR1bits.ADIF = 0;
    TRISIO = 0b00000111;
    /************定数クリア************/
    SEC = 0;
    STEP = 0;
    RED_STEP = 0;
    ADC_STEP = 0;
    REF_DATA = 0;
    SENSOR_DATA = 0;
    TMR0_NOW = 0;
    Y_LED_OFF;
    R_LED_OFF;
    Y_ERROR = 0;
    R_ERROR = 0;
    
    for(;;){
        
        /**********************************TEMP_******************************************/
        if(STEP == 0 && ADC_STEP == 0 && Y_ERROR == 0 && TMR0_NOW == 0 && R_DANGER == 0){//基準値取得
            STEP = STEP + 1;
            ADCONV(1);
        }
        
        if(STEP == 1 && ADC_STEP == 0 && TMR0_NOW == 0 && R_DANGER == 0){//センサー値取得
            STEP = STEP + 1;
            ADCONV(0);
        }
        
        if(STEP == 2 && ADC_STEP == 0 && TMR0_NOW == 0 && R_DANGER == 0){//基準値,センサー値比較
            CHECKTEMP();
        }
        
        if(STEP == 3 && ADC_STEP == 0 && SEC == 1 && TMR0_NOW == 0 && R_DANGER == 0){//温度超えている時の
            SEC = 0;
            STEP = STEP + 1;
            ADCONV(1);
        }
        
        if(STEP == 4 && ADC_STEP == 0 && TMR0_NOW == 0 && R_DANGER == 0){
            STEP = STEP + 1;
            ADCONV(0);
        }
        
        if(STEP == 5 && ADC_STEP == 0 && R_DANGER == 0){
            FINALCHECKTEMP();
        }
        
        /*********************************************************************************/
        
        /*************************************VOLTAGE*************************************/
        
        if(V_OFF && R_ERROR == 0 && RED_STEP == 0 && TMR0_NOW == 0 && Y_DANGER == 0){
            R_DANGER = 1;
            RED_STEP = RED_STEP + 1;
            SECSTART_64(134);
        }
        
        if(RED_STEP == 1 && SEC == 1 && V_OFF){
            R_LED_ON;
            RED_STEP = 0;
            SEC = 0;
            R_ERROR = 1;
            R_DANGER = 0;
        }
        
        if(RED_STEP == 1 && SEC == 1 && V_ON){
            RED_STEP = 0;
            SEC = 0;
            R_DANGER = 0;
        }
        
        /**********************************************************************************/
        
      /*************ADC_PROCESS***************/
        if(ADC_STEP == 1 && R_DANGER == 0){
            ADC_STEP = ADC_STEP + 1;
            ADCON0bits.GO = 1;
        }
        
        if(ADC_STEP == 2 && ADCON0bits.GO == 0 && R_DANGER == 0){//AD変換値をレジスタにセット
            if(GL_CH == 1){ //基準値
                REF_DATA = ADRESL+(ADRESH*256);
                
            }
            
            if(GL_CH == 0){//センサー値
                SENSOR_DATA = ADRESL+(ADRESH*256);
            }   
                
            ADCON0bits.ADON = 0;
            ADC_STEP = 0;
            SEC = 0;
            
        }
        
        /******************************************/
    }
    
    return;
}

void ADCONV(int CH){ //AD変換開始
    
    ADC_STEP = ADC_STEP + 1;
    
    if(CH == 0){//センサー値切り替え
        GL_CH = 0;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 0;
    }
    
    if(CH == 1){//基準値切り替え
        GL_CH = 1;
        ADCON0bits.CHS1 = 0;
        ADCON0bits.CHS0 = 1;
    }
    
    ADCON0bits.ADON = 1;
    ;
}

void CHECKTEMP(){
    if(SENSOR_DATA >= REF_DATA){
        STEP = 0;
    }
                
    if(SENSOR_DATA <= REF_DATA){
        Y_DANGER = 1;
        STEP = STEP + 1;
        SECSTART_64(134);
    }
}

void FINALCHECKTEMP(){
    if(SENSOR_DATA >= REF_DATA){
        STEP = 0;
        Y_DANGER = 0;
    }
                
    if(SENSOR_DATA <= REF_DATA){
        Y_LED_ON;
        Y_ERROR = 1;
        Y_DANGER = 0;
    }
}

void SECSTART_64 (int TMR0_CNT) {
    TMR0_NOW = 1;
    OPTION_REG = 0b10000101;
    TMR0 = TMR0_CNT;
    INTCONbits.GIE = 1;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
}
