#ifndef _PINS_H
#define _PINS_H

#include <avr/io.h>

#define GET_BIT(TGT, PIN)    ((TGT) & (1 << (PIN))) 
#define SET_BIT(TGT, PIN)    do { TGT |=  (1 << (PIN)); } while(0)
#define CLEAR_BIT(TGT, PIN)  do { TGT &= ~(1 << (PIN)); } while(0)
#define TOGGLE_BIT(TGT, PIN) do { TGT ^=  (1 << (PIN)); } while(0)

#define PORT_DEBUG  PORTB
#define PIN_DEBUG   PINB
#define DDR_DEBUG   DDRB
#define BIT_DEBUG   PB0

#define PORT_LED  PORTB
#define PIN_LED   PINB
#define DDR_LED   DDRB
#define BIT_LED   PB5

#define PORT_PWM_1  PORTB
#define PIN_PWM_1   PINB
#define DDR_PWM_1   DDRB
#define BIT_PWM_1   PB1

#define PORT_SWITCH_1  PORTB
#define PIN_SWITCH_1   PINB
#define DDR_SWITCH_1   DDRB
#define BIT_SWITCH_1   PB4

#endif
