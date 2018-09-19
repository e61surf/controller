/*
 * High resolution implementation of timer using a 16 bit clock, no prescaler, 
 * etc.  Clicks every millisecond, with almost-microsecond resolution upon request.
 * You can use this file when you need high resolution timing, and performance of other 
 * components does not matter.
 */
#include "timer.h"

static volatile uint32_t _timer_millis;
static uint32_t _timer_micro_divisor;

/*
 * Initializes the timer, and resets the timer count to 0.  Sets up the ISRs 
 * linked with timer1.
 */
void timer_init(){
	//Set up the timer to run at F_CPU in CTC mode
	TCCR1A = 0x0;
	TCCR1B |= _BV(CS10) | _BV(WGM12);
	
	//Set compare value to be F_CPU / 1000 -- fire interrupt every millisecond
	OCR1A = F_CPU / 1000;
	
	//Every _timer_micro_divisor clock ticks is one microsecond.
	_timer_micro_divisor = F_CPU / 1000000; 
	
	//Enable compare interrupt
	TIMSK1 = _BV(OCIE1A);

	//Reset count variables
	_timer_millis = 0;
	
	//Enable interrupts if the NO_INTERRUPT_ENABLE define is not set.  If it is, you need to call sei() elsewhere.
#ifndef NO_INTERRUPT_ENABLE
	sei();
#endif
}

/*
 * Returns the number of milliseconds which have elapsed since the 
 * last time timer_init() was called.  Overflows after about 49 days.
 */
uint32_t timer_millis(){
	return _timer_millis;
}

/*
 * Returns the number of microseconds which have elapsed since the 
 * last time timer_init() was called.  Overflows after about 71 minutes.
 */
uint32_t timer_micros(){
	return (_timer_millis * 1000) + (TCNT1 / _timer_micro_divisor);
}


/* 
 * The ISR for timer1 overflow.  Increment the _timer_count here, and do the calculcations
 * to increment _timer_millis as needed.
 */
EMPTY_INTERRUPT(TIMER1_COMPB_vect)
EMPTY_INTERRUPT(TIMER1_OVF_vect)
ISR(TIMER1_COMPA_vect){
	_timer_millis++;
}
