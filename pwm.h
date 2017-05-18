#ifndef _PWM_H
#define _PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pins.h"

void pwm_init(void);
void pwm_enable(void);
void pwm_disable(void);
void set_top(uint8_t x);
//void set_match(uint16_t x);
void set_frequency(uint16_t x);
void reset_clock(void);
//void set_pwm_interrupt(uint8_t value);

#endif
