#ifndef _LOCK_TIMER_H
#define _LOCK_TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "pins.h"

void lock_timer_init(void);
void lock_timer_enable();
void lock_timer_disable();
void lock_timer_delay(uint16_t x);
uint16_t check_timer();

#endif
