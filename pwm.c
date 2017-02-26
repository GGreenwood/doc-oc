#include "pwm.h"

static int8_t pwm_velocity = PWM_RAMP_VELOCITY;

void pwm_init(void) {
    // Set PWM pin as output
    SET_BIT(DDR_PWM_1, BIT_PWM_1);

    // Set up PWM output on DDR_PWM_1=PB1=OC1A
    // Fast PWM mode(WGM=1110=14)
    // Prescaler is set to 16, or 250kHz(4us) per count
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);

    // Set initial PWM constants
    set_top(PWM_TOP);
    set_match(PWM_MATCH);
}

// ICR1 is the 16-bit top value
void set_top(uint16_t x) {
    ICR1 = PWM_TOP;
}

// OCR1A is the 16-bit match value
void set_match(uint16_t x) {
    OCR1A = PWM_MATCH;
}

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
        }

        // Add the velocity to the top value
        // This sets the PWM frequency
        ICR1 += pwm_velocity;

        // Update the match value to stay at 50% duty
        OCR1A = ICR1 / 2;
    }
    CLEAR_BIT(PORT_DEBUG, BIT_DEBUG);
}
