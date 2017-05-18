#include "pwm.h"

void pwm_init(void) {
    // Set PWM pin as output
    SET_BIT(DDR_PWM, BIT_PWM);

    // Set up PWM output on DDR_PWM=PD6=OC0A
    // CTC mode
    // Prescaler is set to 16, or 250kHz(4us) per count
    TCCR0A = (1 << COM0A0) | (1 << WGM01);
    TCCR0B = (1 << CS01);// | (1 << CS00);

    // Set initial PWM constants
    set_frequency(4000);

    reset_clock();
}

void pwm_enable(void) {
    TCCR0B = (1 << CS01);// | (1 << CS00);
}
void pwm_disable(void) {
    TCCR0B = 0;
}

void set_top(uint8_t x) {
    OCR0A = x;
}

/*
void set_match(uint8_t x) {
    OCR0A = x;
}
*/

void set_frequency(uint16_t x) {
    set_top(F_CPU / x / 8 / 2);
    //set_match(ICR1 / 2);
}

void reset_clock(void) {
    TCNT0 = 0;
}
/*
static int8_t pwm_velocity = PWM_RAMP_VELOCITY;

void set_pwm_interrupt(uint8_t value) {
    if(value) {
        SET_BIT(TIMSK1, OCIE1A);
        pwm_velocity = PWM_RAMP_VELOCITY;
    } else {
        CLEAR_BIT(TIMSK1, OCIE1A);
    }
}

ISR(TIMER1_COMPA_vect) {
    SET_BIT(PORT_DEBUG, BIT_DEBUG);
    // Check if we're going down and have hit the bottom
    if(ICR1 <= PWM_TOP && pwm_velocity < 0) {
        // Disable future interrupts
        set_pwm_interrupt(0);

        ICR1 = PWM_TOP;
        TCNT1 = 0;

        // Reset direction
        pwm_velocity = PWM_RAMP_VELOCITY;
    } else {
        // Check if we've hit the top value
        if(ICR1 >= PWM_RAMP_TOP && pwm_velocity > 0) {
            pwm_velocity *= -1;
            if(GET_BIT(PIN_SWITCH, BIT_SWITCH)) {
                SET_BIT(PORT_LED, BIT_LED);
            } else {
                CLEAR_BIT(PORT_LED, BIT_LED);
            }
        }

        // Add the velocity to the top value
        // This sets the PWM frequency
        ICR1 += pwm_velocity;

        // Update the match value to stay at 50% duty
        OCR1A = ICR1 / 2;
    }
    CLEAR_BIT(PORT_DEBUG, BIT_DEBUG);
}
*/
