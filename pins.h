#ifndef _PINS_H
#define _PINS_H

#include <avr/io.h>

#define GET_BIT(TGT, PIN)    ((TGT) & (1 << (PIN))) 
#define SET_BIT(TGT, PIN)    do { TGT |=  (1 << (PIN)); } while(0)
#define CLEAR_BIT(TGT, PIN)  do { TGT &= ~(1 << (PIN)); } while(0)
#define TOGGLE_BIT(TGT, PIN) do { TGT ^=  (1 << (PIN)); } while(0)

#define PORT_PWM  PORTD
#define PIN_PWM   PIND
#define DDR_PWM   DDRD
#define BIT_PWM   PD6

#define PORT_MOTOR_ENABLE  PORTB
#define PIN_MOTOR_ENABLE   PINB
#define DDR_MOTOR_ENABLE   DDRB
#define BIT_MOTOR_ENABLE   PB2

#define PORT_DIRECTION  PORTB
#define PIN_DIRECTION   PINB
#define DDR_DIRECTION   DDRB
#define BIT_DIRECTION   PB3

#define PORT_RELAY  PORTB
#define PIN_RELAY   PINB
#define DDR_RELAY   DDRB
#define BIT_RELAY   PB4

#define PORT_LED  PORTB
#define PIN_LED   PINB
#define DDR_LED   DDRB
#define BIT_LED   PB5

#define PORT_UP  PORTC
#define PIN_UP   PINC
#define DDR_UP   DDRC
#define BIT_UP   PC0

#define PORT_DOWN  PORTC
#define PIN_DOWN   PINC
#define DDR_DOWN   DDRC
#define BIT_DOWN   PC1

#define PORT_SAFETY  PORTC
#define PIN_SAFETY   PINC
#define DDR_SAFETY   DDRC
#define BIT_SAFETY   PC2

#endif
