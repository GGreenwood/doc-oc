#include "lock_timer.h"

void lock_timer_init(void) {
    // Set up Timer1 to count lock state timings
    TCCR1A = (1 << WGM10) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS12);
    OCR1A = 0;
}

// Prescaler is 256
void lock_timer_enable() {
    //TIMSK1 |= (1 << TIMSK1);
}

void lock_timer_disable() {
    //TIMSK1 &= ~(1 << TIMSK1);
}

void lock_timer_delay(uint16_t x) {
    TCNT1 = 0xFFFF - (F_CPU / 256 / x * 1000);
    //lock_timer_enable();
}

uint16_t check_timer() {
    return TCNT1;
}

/*
ISR(TIMER1_COMPA_vect) {
    lock_timer_disable();
}
*/
