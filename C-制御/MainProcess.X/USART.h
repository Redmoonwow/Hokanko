/* 
 * File:   USART.h
 * Author: ed12082
 *
 * Created on 2015/11/06, 13:59
 */

#ifndef __USART_H__
#define	__USART_H__

#ifndef	_XTAL_FREQ
#define _XTAL_FREQ 20000000 //20MHZ
#endif

#define BAUNDRATE 9600
#define BIT_9 0 // 0:8bit 1:9bit 
#define BRGH_BIT 1 //?????Low = 0 High = 1

#if BIT_9 == 1
#define BIT_9DATA 0x40
#else
#define BIT_9DATA 0x00
#endif

#if BRGH_BIT == 1
#define BRGH_DATA 0x04
#define SPBRG_DATA ((unsigned char)(((_XTAL_FREQ / 16) / BAUNDRATE) -1))
#else 
#define BRGH_DATA 0x00
#define SPBRG_DATA ((unsigned char)(((_XTAL_FREQ / 64) / BAUNDRATE) -1))
#endif

extern void initUART();
extern void sentsimple(unsigned char byte);
extern unsigned char getsimple();
void sent(const char *data,int cnt);

#endif // __UART_H__
