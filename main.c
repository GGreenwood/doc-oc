#include <stdint.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pins.h"
#include "pwm.h"

typedef enum {Off, Idle, Up, Down, Lock} State;

// These are run once during transitions
void off_transition(State *state) {
    *state = Off;
}

void idle_transition(State *state) {
    SET_BIT(PORT_LED, BIT_LED);
    SET_BIT(PORT_DIRECTION, BIT_DIRECTION);
    SET_BIT(PORT_RELAY, BIT_RELAY);
    SET_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(0);
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
    *state = Up;
}

void down_transition(State *state) {
    CLEAR_BIT(PORT_LED, BIT_LED);
    CLEAR_BIT(PORT_DIRECTION, BIT_DIRECTION);
    SET_BIT(PORT_RELAY, BIT_RELAY);
    SET_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(3000);
    reset_clock();
    *state = Down;
}

void lock_transition(State *state) {
    CLEAR_BIT(PORT_LED, BIT_LED);
    SET_BIT(PORT_DIRECTION, BIT_DIRECTION);
    CLEAR_BIT(PORT_RELAY, BIT_RELAY);
    CLEAR_BIT(PORT_MOTOR_ENABLE, BIT_MOTOR_ENABLE);
    set_frequency(0);
    reset_clock();
    *state = Lock;
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

    // Set up Timer1 to count lock state timings
    // CTC Mode
    TCCR0A = (1 << WGM01)
    //sei();

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
                if(up) {
                    up_transition(&state);
                } else if(down) {
                    down_transition(&state);
                }
                break;
            case Up:
                if(up) {
                    continue;
                } else if(down) {
                    lock_transition(&state);
                    _delay_ms(500);

                    down_transition(&state);
                } else {
                    idle_transition(&state);
                }
                break;
            case Down:
                if(down) {
                    continue;
                } else if(up) {
                    lock_transition(&state);
                    _delay_ms(500);
                    up_transition(&state);
                } else {
                    idle_transition(&state);
                }
                break;
            case Lock:
                break;
            default:
                state = Idle;
        }

        _delay_ms(1);
    }
}
