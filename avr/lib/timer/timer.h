#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#if defined (__cplusplus)
extern "C" {
#endif

/*
 * Initializes the timer, and resets the timer count to 0.  Sets up the ISRs
 * linked with timer1.
 */
void timer_init();

/*
 * Returns the number of milliseconds which have elapsed since the
 * last time timer_init() was called.  Overflows after about 49 days.
 */
uint32_t timer_millis();

/*
 * Returns the number of microseconds which have elapsed since the
 * last time timer_init() was called.  Overflows after about 71 minutes.
 */
uint32_t timer_micros();

#if defined (__cplusplus)
}
#endif

#endif
