#ifndef _PWM_H
#define _PWM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pins.h"

#define PWM_DUTY    .5

#define PWM_FREQ    4000
#define PWM_RAMP_FREQ   8000

#define PWM_TOP     F_CPU / 64 / PWM_FREQ
#define PWM_MATCH   PWM_TOP * PWM_DUTY

#define PWM_RAMP_TOP     F_CPU / 64 / PWM_RAMP_FREQ

void pwm_init(void);
void set_top(uint16_t x);
void set_match(uint16_t x);
void set_pwm_interrupt(uint8_t value);

#endif
