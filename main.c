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
#include <stdint.h>


#define ADC_GRP2_NUM_CHANNELS   2
#define ADC_GRP2_BUF_DEPTH      48

static adcsample_t samples2[ADC_GRP2_NUM_CHANNELS * ADC_GRP2_BUF_DEPTH];


systime_t count_adc, count_frt;
/*
 * ADC streaming callback.
 */
size_t nx = 0, ny = 0;
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void)adcp;
  if (samples2 == buffer) {
    nx += n;
  }
  else {
    ny += n;
  }
  count_adc++;
}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}


/*
 * ADC conversion group.
 * Mode:        Continuous, 16 samples of 8 channels, SW triggered.
 * Channels:    IN11, IN12, IN11, IN12, IN11, IN12, Sensor, VRef.
 */
static const ADCConversionGroup adcgrpcfg2 = {
  TRUE,
  ADC_GRP2_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0,                        /* CR1 */
  ADC_CR2_SWSTART,          /* CR2 */
  ADC_SMPR1_SMP_AN12(ADC_SAMPLE_3) | ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3),
  0,                        /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_GRP2_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN12)   | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)
};



static THD_WORKING_AREA(waThreadFRT, 4096);
static THD_FUNCTION(ThreadFRT, arg) {
	// shortest time to compute, but highest frequency and highest priority
	(void)arg;
	chRegSetThreadName("ThreadFRT");

	int delta_count, last_delta_count;
	delta_count=0; last_delta_count=0;
	count_adc=0; count_frt=0;
	systime_t time = chVTGetSystemTime();
	adcStartConversion(&ADCD1, &adcgrpcfg2, samples2, ADC_GRP2_BUF_DEPTH);

	while (true) {
		time += US2ST(20); //20
		palTogglePad(GPIOD, PIN_LED2);       /* LD3 (orange)  */
		delta_count = count_frt - count_adc;
		if(delta_count != last_delta_count) {
			palTogglePad(GPIOD, PIN_LED1);
		}
		last_delta_count = delta_count;
		count_frt++;
		chThdSleepUntil(time);
		//chThdYield();
	}
}

static THD_WORKING_AREA(waThreadRT, 4096);
static THD_FUNCTION(ThreadRT, arg) {
	// longest time to compute (longer than ThreadFRT frequency, but lower frequency and lowest priority
	// long computation in this thread is interrupted by ThreadFRT and the main loop
	(void)arg;
	chRegSetThreadName("ThreadRT");

	systime_t time = chVTGetSystemTime();

	while (true) {
		time += MS2ST(250);
		int i,i2;
		for (i = 0; i<200000; i++) {
			for (i2 = 0; i2<2; i2++) {
				int a = 5;
				float b = 6.123;
				float c = a / b * i2;
			}
		}
		palTogglePad(GPIOD, PIN_LED3_DISCO);       /* LD6 (blue)  */
		//chThdSleepUntil(time);
		//chThdYield();
    	chThdSleepMilliseconds(100);
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


  /*
   * Activates the ADC1 driver and the temperature sensor.
   */
  adcStart(&ADCD1, NULL);
  //adcSTM32EnableTSVREFE();
  /*
   * Starts an ADC continuous conversion.
   */

  chThdCreateStatic(waThreadFRT, sizeof(waThreadFRT), NORMALPRIO+20, ThreadFRT, NULL);
  chThdCreateStatic(waThreadRT, sizeof(waThreadRT), NORMALPRIO-10, ThreadRT, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    //palTogglePad(GPIOD, PIN_LED1);       /* LD4 (green)  */
	chThdSleepMilliseconds(5);
  }
}
