#include <stdint.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pins.h"
#include "pwm.h"
#include "lock_timer.h"

#define LOCK_DELAY 100

typedef enum {Off, Idle, Up, Down} State;

// These are run once during transitions
void off_transition(State *state) {
    *state = Off;
}

void idle_transition(State *state) {
    SET_BIT(PORT_LED, BIT_LED);
    SET_BIT(PORT_DIRECTION, BIT_DIRECTION);
    SET_BIT(PORT_RELAY, BIT_RELAY);
    SET_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    pwm_disable();
    reset_clock();
    *state = Idle;
}

void up_transition(State *state) {
    CLEAR_BIT(PORT_LED, BIT_LED);
    SET_BIT(PORT_DIRECTION, BIT_DIRECTION);
    SET_BIT(PORT_RELAY, BIT_RELAY);
    SET_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(4000);
    reset_clock();
    pwm_enable();
    *state = Up;
}

void down_transition(State *state) {
    CLEAR_BIT(PORT_LED, BIT_LED);
    CLEAR_BIT(PORT_DIRECTION, BIT_DIRECTION);
    SET_BIT(PORT_RELAY, BIT_RELAY);
    SET_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(3000);
    reset_clock();
    pwm_enable();
    *state = Down;
}

void lock_transition(State *state) {
    //Kick off lock delay timer
    lock_timer_delay(LOCK_DELAY);

    CLEAR_BIT(PORT_LED, BIT_LED);
    SET_BIT(PORT_DIRECTION, BIT_DIRECTION);
    CLEAR_BIT(PORT_RELAY, BIT_RELAY);
    CLEAR_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(0);
    reset_clock();
    *state = Idle;
}

int main(void)
{
    //wdt_enable(WDTO_1S);    // enable 1s watchdog timer
    State state;
    idle_transition(&state);

	// Set output lines
    // All of Port B is output
    DDRB = 0xFF;

    // Set switch as input
    // All of Port C is input
    DDRC = 0x00;

    pwm_init();
    lock_timer_init();
    sei();

    uint8_t up, down, safety;

    while(1) {
        wdt_reset();

        up = GET_BIT(PIN_UP, BIT_UP);
        down = GET_BIT(PIN_DOWN, BIT_DOWN);
        safety = GET_BIT(PIN_SAFETY, BIT_SAFETY);

        // Check for transitions
        switch(state) {
            case Off:
                break;
            case Idle:
                pwm_disable();
                if(!check_timer()) {
                    if(up) {
                        up_transition(&state);
                    } else if(down) {
                        down_transition(&state);
                    } else {
                        break;
                    }
                }
                break;
            case Up:
                pwm_enable();
                if(up) {
                    continue;
                } else {
                    lock_transition(&state);
                }
                break;
            case Down:
                pwm_enable();
                if(down) {
                    continue;
                } else {
                    lock_transition(&state);
                }
                break;
            default:
                state = Idle;
        }

        _delay_ms(1);
    }
}
