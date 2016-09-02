/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"
#include "test.h"
#include "chprintf.h"
#include "subsystems/serial/chibiesc_usb.h"


static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
	// shortest time to compute, but highest frequency and highest priority
	(void)arg;
	chRegSetThreadName("Thread1");

	systime_t time = chVTGetSystemTime();

	while (true) {
		time += US2ST(1);
		palTogglePad(GPIOD, PIN_LED2);       /* LD3 (orange)  */
		chThdSleepUntil(time);
		//chThdSleepMicroseconds(1);
		//chThdYield();
	}
}

static THD_WORKING_AREA(waThread2, 128);
static THD_FUNCTION(Thread2, arg) {
	// longest time to compute (longer than Thread1 frequency, but lower frequency and lowest priority
	// long computation in this thread is interrupted by Thread1 and the main loop
	(void)arg;
	chRegSetThreadName("Thread2");

	systime_t time = chVTGetSystemTime();

	while (true) {
		time += MS2ST(250);
		int i;
		for (i = 0; i<2000000; i++) {
			int a = 5;
			float b = 6.123;
			float c = a / b * i;
		}
		palTogglePad(GPIOD, PIN_LED3_DISCO);       /* LD6 (blue)  */
		chThdSleepUntil(time);
    	//chThdSleepMilliseconds(250);
	}
}


/*
 * Application entry point.
 */
int main(void) {
	// main loop always runs at NORMALPRIO

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  usb_init(); // Serial over USB initialization

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO+20, Thread1, NULL);
  chThdCreateStatic(waThread2, sizeof(waThread2), NORMALPRIO-10, Thread2, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    palTogglePad(GPIOD, PIN_LED1);       /* LD4 (green)  */
	chThdSleepMilliseconds(5);
  }
}
