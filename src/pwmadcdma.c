/**
 * @file    pwmdma.c
 * @author  Joerg Wangemann <joerg.wangemann@gmail.com>
 * @brief   WS2812 LED driver
 *
 * Copyright (C) 2017 Joerg Wangemann
 *
 * This software may be modified and distributed under the terms
 * of the GPL-V3 license.  See the LICENSE file for details.
 *
 * @todo    Put in names and descriptions of variables which need to be defined to use this file
 *
 * @addtogroup pwmdma
 * @{
 */

/* --- PRIVATE DEPENDENCIES ------------------------------------------------- */

// This Driver
#include "pwmadcdma.h"
#include <stdint.h>

// Application
#include "board.h"
#include "chutil.h"


#define PWM_DMA_TIM_N		1 // 8 oder 1
#define PWM_DMA_TIM_CH		0 // so lassen

/* --- CONFIGURATION CHECK -------------------------------------------------- */


#if !defined(PWM_DMA_TIM_N)
    #error PWM_DMA timer not specified
#elif PWM_DMA_TIM_N == 1				// DMA funzt, ADC-Trigger noch nicht
    #define PWM_DMA_STREAM				STM32_DMA2_STREAM6 // OK
	#define PWM_DMA_TIM_DIER			TIM_DIER_CC1DE //OK
	#define PWM_DMA_CR_CHSEL 			STM32_DMA_CR_CHSEL(0) // OK
	#define PWM_DMA_ADC_CR2_EXTSEL_SRC	ADC_CR2_EXTSEL_SRC(0)  // TIM1_CC1 event
	#define PWM_DMA_TIM_CR2				(TIM_CR2_MMS_1)	// MMS = 011 = TRGO on Compare Pulse --> Trigger ADC
#elif PWM_DMA_TIM_N == 8
    #define PWM_DMA_STREAM				STM32_DMA2_STREAM1
	#define PWM_DMA_CR_CHSEL 			STM32_DMA_CR_CHSEL(7)
	#define PWM_DMA_ADC_CR2_EXTSEL_SRC	ADC_CR2_EXTSEL_SRC(14)	// TIM8_TRGO event
	#define PWM_DMA_TIM_CR2				TIM_CR2_MMS_1			// MMS = 010 = TRGO on Update Event --> Trigger ADC
	#define PWM_DMA_TIM_DIER			TIM_DIER_UDE
#else
    #error PWM_DMA timer set to invalid value
#endif

#if !defined(PWM_DMA_TIM_CH)
    #error PWM_DMA timer channel not specified
#elif PWM_DMA_TIM_CH >= 4
    #error PWM_DMA timer channel set to invalid value
#endif

/* --- PRIVATE CONSTANTS ---------------------------------------------------- */



/**
 * @brief   Number of bit-periods to hold the data line low at the end of a frame
 *
 * The reset period for each frame must be at least 50 uS; so we add in 50 bit-times
 * of zeroes at the end. (50 bits)*(1.25 uS/bit) = 62.5 uS, which gives us some
 * slack in the timing requirements
 */
//#define WS2812_COLOR_BIT_N      (WS2812_LED_N*24)                           /**< Number of data bits */
#define PWM_DMA_BIT_N            PWM_DMA_MAXIMUM_PERIOD_CYCLES   /**< Total number of bits in a frame */

/**
 * @brief   High period for a zero, in ticks
 *
 * Per the datasheet:
 * - T0H: 0.200 uS to 0.500 uS, inclusive
 * - T0L: 0.650 uS to 0.950 uS, inclusive
 *
 * With a duty cycle of 22 ticks, we have a high period of 22/(72 MHz) = 3.06 uS, and
 * a low period of (90 - 22)/(72 MHz) = 9.44 uS. These values are within the allowable
 * bounds, and intentionally skewed as far to the low duty-cycle side as possible
 */
//#define WS2812_DUTYCYCLE_0      (22)

/**
 * @brief   High period for a one, in ticks
 *
 * Per the datasheet:
 * - T0H: 0.550 uS to 0.850 uS, inclusive
 * - T0L: 0.450 uS to 0.750 uS, inclusive
 *
 * With a duty cycle of 56 ticks, we have a high period of 56/(72 MHz) = 7.68 uS, and
 * a low period of (90 - 56)/(72 MHz) = 4.72 uS. These values are within the allowable
 * bounds, and intentionally skewed as far to the high duty-cycle side as possible
 */
//#define WS2812_DUTYCYCLE_1      (56)

/* --- PRIVATE MACROS ------------------------------------------------------- */

/**
 * @brief   Generates a reference to a numbered PWM driver
 *
 * @param[in] n:            The driver (timer) number
 *
 * @return                  A reference to the driver
 */
#define PWMD(n)                             CONCAT_EXPANDED_SYMBOLS(PWMD, n)

#define PWMDMA_PWMD                         PWMD(PWM_DMA_TIM_N)      /**< The PWM driver to use for the LED chain */

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given bit
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] byte:                 The byte number [0, 2]
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_BIT(led, byte, bit)          (24*(led) + 8*(byte) + (7 - (bit))) // Nützlich auch für PWM??

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given red bit
 *
 * @note    The red byte is the middle byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_RED_BIT(led, bit)            WS2812_BIT((led), 1, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given green bit
 *
 * @note    The red byte is the first byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit number [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_GREEN_BIT(led, bit)          WS2812_BIT((led), 0, (bit))

/**
 * @brief   Determine the index in @ref ws2812_frame_buffer "the frame buffer" of a given blue bit
 *
 * @note    The red byte is the last byte in the color packet
 *
 * @param[in] led:                  The led index [0, @ref WS2812_LED_N)
 * @param[in] bit:                  The bit index [0, 7]
 *
 * @return                          The bit index
 */
#define WS2812_BLUE_BIT(led, bit)           WS2812_BIT((led), 2, (bit))


#define intoSRAM2  __attribute__((section(".ram2")))  __attribute__((aligned(4)))

/* --- PRIVATE VARIABLES ---------------------------------------------------- */
volatile uint32_t pwm_dma_frame_buffer[PWM_DMA_BIT_N] intoSRAM2;			/**< Buffer for a frame */

adcsample_t commutatesamples[ADC_COMMUTATE_BUF_DEPTH];// intoSRAM2; // Better NOT ADC Buffer into SRAM2

static pwm_dma_state_t pwm_dma_state = PWM_DMA_STOPPED;

/* --- PUBLIC FUNCTIONS ----------------------------------------------------- */
/*
 * Gedanke: Double-buffer type transactions: double buffer transfers using two memory pointers for
the memory (while the DMA is reading/writing from/to a buffer, the application can
write/read to/from the other buffer).
 */


/*
 * ADC streaming callback.
 */
thread_reference_t adc_trp = NULL; // Declare static
systime_t count_adc, count_frt;
size_t nx = 0, ny = 0; int adc_blink_count = 1000;
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void)adcp;
  if (commutatesamples == buffer) {
    nx += n;
  }
  else {
    ny += n;
  }
  count_adc++;

  if(adc_blink_count-- <= 0) {
	  adc_blink_count = 1000;
	  //palTogglePad(BANK_LED_RED, PIN_LED_RED);
	  //palTogglePad(BANK_LED_GREEN, PIN_LED_GREEN);
  }
  palTogglePad(BANK_LED_GREEN, PIN_LED_GREEN);
  /* Wakes up the thread.*/
  chSysLockFromISR();
  chThdResumeI(&adc_trp, (msg_t)0x1337);  /* Resuming the thread with message.*/
  chSysUnlockFromISR();
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
ADCConversionGroup adc_commutate_group = { // TODO: Check if this is fine for F4
  TRUE,
  ADC_COMMUTATE_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0,                        // CR1
  ADC_CR2_CONT | ADC_CR2_EXTEN_RISING | PWM_DMA_ADC_CR2_EXTSEL_SRC,// | ADC_CR2_EXTSEL_3 | ADC_CR2_EXTSEL_2 | ADC_CR2_EXTSEL_0,//ADC_CR2_SWSTART,// Rising Edge: CR2 --> 1101: Timer 8 CC1 event EXTSEL und EXTEN!
  ADC_SMPR1_SMP_AN12(ADC_SAMPLE_3) /*| ADC_SMPR1_SMP_AN11(ADC_SAMPLE_3)*/,
  0,                        /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_COMMUTATE_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN12)   /*| ADC_SQR3_SQ1_N(ADC_CHANNEL_IN11)*/
};

// DMA scheint Werte zu verlieren!


static uint16_t actual_PWM_DMA_PERIOD_CYCLES = PWM_DMA_MAXIMUM_PERIOD_CYCLES; // Aktuelle Zahl von PWM-Period-Cycles - je nachdem wie weit der DMA kreist
void pwm_dma_init(void)
{
	if(pwm_dma_state == PWM_DMA_RUNNING) return;
	pwm_dma_state = PWM_DMA_RUNNING;

    // Initialize frame buffer
    uint32_t i;
    for (i = 0; i < PWM_DMA_BIT_N; i++) pwm_dma_frame_buffer[i] = 0;   // All color bits are zero duty cycle
    uint32_t tx_high   = GPIO_BSRR_BS_10; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    uint32_t tx_low    = GPIO_BSRR_BR_10; // Pin 10 auf low setzen
    //uint32_t tx_high   = GPIO_BSRR_BS_1; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    //uint32_t tx_low    = GPIO_BSRR_BR_1; // Pin 10 auf low setzen

    // Configure PA0 as AF output
    //palSetPadMode(GPIOA, 1, PAL_MODE_ALTERNATE(1)); //palSetPadMode(GPIOA, 1, PAL_MODE_ALTERNATE(1)); Nur für TIM1&2? Siehe F4-Datenblatt
    pwm_dma_frame_buffer[PWM_DMA_MAXIMUM_PERIOD_CYCLES - 1] = tx_low;// Test: Pin am Ende der Periode zurücksetzen

    // PWM Configuration
    #pragma GCC diagnostic ignored "-Woverride-init"                                        // Turn off override-init warning for this struct. We use the overriding ability to set a "default" channel config
    static const PWMConfig pwm_dma_config = {
        .frequency          = PWM_CLOCK_FREQUENCY,
        .period             = PWM_DMA_TRANSFER_PERIOD_TICKS, //Mit dieser Periode wird UDE-Event erzeugt und ein neuer Wert (Länge WS2812_BIT_N) vom DMA ins CCR geschrieben
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Channels default to disabled
            [PWM_DMA_TIM_CH]= {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Turn on the channel we care about
        },
        .cr2                = PWM_DMA_TIM_CR2,
        .dier               = PWM_DMA_TIM_DIER,											// DMA on update event for next period
    };
    #pragma GCC diagnostic pop                                                              // Restore command-line warning options

    // Configure DMA
    dmaStreamAllocate(PWM_DMA_STREAM, 10, NULL, NULL);
    dmaStreamSetPeripheral(PWM_DMA_STREAM, &(GPIOA->BSRR.W));  // BSSR: Bit-Set-Reset-Register
    dmaStreamSetMemory0(PWM_DMA_STREAM, pwm_dma_frame_buffer);
    dmaStreamSetTransactionSize(PWM_DMA_STREAM, PWM_DMA_MAXIMUM_PERIOD_CYCLES); // Anhand der aktuellen FRT-Periodendauer einstellen. Maximal PWM_DMA_BIT_N
    dmaStreamSetMode(PWM_DMA_STREAM,
    		PWM_DMA_CR_CHSEL | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
			STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
    //CHSEL(7): Select DMA-channel 7 (TIM8_UP); M2P: Memory 2 Periph; PL: Priority Level

    dmaStreamEnable(PWM_DMA_STREAM); // Start DMA

    // Configure PWM
    // NOTE: It's required that preload be enabled on the timer channel CCR register. This is currently enabled in the
    // ChibiOS driver code, so we don't have to do anything special to the timer. If we did, we'd have to start the timer,
    // disable counting, enable the channel, and then make whatever configuration changes we need.
    adcStartConversion(&ADCD1, &adc_commutate_group, commutatesamples, 2*ADC_FRT_DEFAULT_PERIOD_CYCLES);
    pwmStart(&PWMDMA_PWMD, &pwm_dma_config);
    pwmEnableChannel(&PWMDMA_PWMD, PWM_DMA_TIM_CH, 1);     // Initial period is 0; output will be low until first duty cycle is DMA'd in
}

void pwm_dma_stop(void) {
	if(pwm_dma_state == PWM_DMA_STOPPED) return;
	pwm_dma_state = PWM_DMA_STOPPED;
	pwmStop(&PWMDMA_PWMD); // Stop triggering DMA transfers
	dmaStreamDisable(PWM_DMA_STREAM);
	dmaStreamRelease(PWM_DMA_STREAM);
	adcStopConversion(&ADCD1);
}



// HW-Double-Buffer brauchen wir nicht. Aber über ADC-Callback auswählen!
// Dazu muss der frame_buffer doppelt so groß sein
// TODO: Mache eine Funktion für PWM-EN (Strip) und H-L (VESC)
// TODO: verwende actual_PWM_DMA_PERIOD_CYCLES
// TODO: setvals MUSS im adc-Callback in den Frame-Buffer geschrieben werden, nicht hier! Es kann hier vorbereitet werden.
uint16_t last_offset = 0;
int pwm_dma_setvals(uint8_t channel_number, uint16_t t_on, uint16_t offset, uint16_t period) { // Einheit ist DMA-Request-Ticks
	pwm_dma_frame_buffer[last_offset] = 0;  // Bei diesem Offset wurde das letzte Mal eingeschaltet.
	pwm_dma_frame_buffer[offset] = GPIO_BSRR_BS_10; // Pin10 einschalten
	//pwm_dma_frame_buffer[offset] = GPIO_BSRR_BS_1; // Pin1 einschalten
	last_offset = offset;
	return 0;
}


/*ws2812_err_t ws2812_write_led(uint32_t led_number, uint8_t r, uint8_t g, uint8_t b)
{
    // Check for valid LED
    if (led_number >= WS2812_LED_N) return WS2812_LED_INVALID;

    // Write color to frame buffer
    uint32_t bit;
    for (bit = 0; bit < 8; bit++) {
        ws2812_frame_buffer[WS2812_RED_BIT(led_number, bit)]      = ((r >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_GREEN_BIT(led_number, bit)]    = ((g >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
        ws2812_frame_buffer[WS2812_BLUE_BIT(led_number, bit)]     = ((b >> bit) & 0x01) ? WS2812_DUTYCYCLE_1 : WS2812_DUTYCYCLE_0;
    }

    // Success
    return WS2812_SUCCESS;
}*/

/** @} addtogroup pwmdma */



// PWM_DMA_TIM_N == 8!!!
/*#define PWM_DMA_STREAM1				STM32_DMA2_STREAM1 // Stream 1 writes to GPIO
#define PWM_DMA_CR_CHSEL1 			STM32_DMA_CR_CHSEL(7)
#define PWM_DMA_STREAM2				STM32_DMA2_STREAM2 // Stream 1 writes to GPIO
#define PWM_DMA_CR_CHSEL2 			STM32_DMA_CR_CHSEL(7)

#define PWM_DMA_TIM_DIER_2			(TIM_DIER_UDE | TIM_DIER_CC1DE)*/

#define PWM_DMA_STREAM2				STM32_DMA2_STREAM6 // Does not start when STREAM1 and 2 are exchanged or when BSSR-DMA-priority is < than DMA-ARR-prio
#define PWM_DMA_CR_CHSEL2 			STM32_DMA_CR_CHSEL(0) //
#define PWM_DMA_STREAM1				STM32_DMA2_STREAM1 //
#define PWM_DMA_CR_CHSEL1 			STM32_DMA_CR_CHSEL(6) //
// Timmer 1 CH1 kann auch noch Stream 3 triggern!

#define PWM_DMA_TIM_DIER			TIM_DIER_CC1DE // CC1 triggert BEIDE DMA-Streams!



#define PWM_DMA_MAX_EDGES (6*10) // Number of pwm-channels * max number of edges per period (>=2, even number)
volatile uint16_t pwm_dma_timer_buffer[PWM_DMA_MAX_EDGES] intoSRAM2;		/**< Buffer for the duration to the next pulse*/


void pwm_dma_init_2(void)
{
	if(pwm_dma_state == PWM_DMA_RUNNING) return;
	pwm_dma_state = PWM_DMA_RUNNING;

    // Initialize frame buffer
    uint32_t i;
    for (i = 0; i < PWM_DMA_BIT_N; i++) pwm_dma_frame_buffer[i] = 0;   // All color bits are zero duty cycle
    uint32_t tx_high   = GPIO_BSRR_BS_10; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    uint32_t tx_low    = GPIO_BSRR_BR_10; // Pin 10 auf low setzen
    //uint32_t tx_high   = GPIO_BSRR_BS_1; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    //uint32_t tx_low    = GPIO_BSRR_BR_1; // Pin 10 auf low setzen

    pwm_dma_frame_buffer[0] = tx_high;
    pwm_dma_frame_buffer[1] = tx_low;// Test: Pin am Ende der Periode zurücksetzen
    pwm_dma_timer_buffer[0] = 100;//PWM_MAXIMUM_PERIOD_CYCLES / 2;
    pwm_dma_timer_buffer[1] = 400;//PWM_MAXIMUM_PERIOD_CYCLES / 2;

    // PWM Configuration
    #pragma GCC diagnostic ignored "-Woverride-init"                                        // Turn off override-init warning for this struct. We use the overriding ability to set a "default" channel config
    static const PWMConfig pwm_dma_config = {
        .frequency          = PWM_CLOCK_FREQUENCY,
        .period             = PWM_DMA_TRANSFER_PERIOD_TICKS, //Mit dieser Periode wird UDE-Event erzeugt und ein neuer Wert (Länge WS2812_BIT_N) vom DMA ins CCR geschrieben
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Channels default to disabled
            [PWM_DMA_TIM_CH]= {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Turn on the channel we care about
        },
        .cr2                = PWM_DMA_TIM_CR2,
        .dier               = PWM_DMA_TIM_DIER,											// DMA on update event for next period
    };
    #pragma GCC diagnostic pop                                                              // Restore command-line warning options
    // Configure DMA stream to GPIO
    dmaStreamAllocate(PWM_DMA_STREAM1, 10, NULL, NULL);
    dmaStreamSetPeripheral(PWM_DMA_STREAM1, &(GPIOA->BSRR.W));  // BSSR: Bit-Set-Reset-Register
    dmaStreamSetMemory0(PWM_DMA_STREAM1, pwm_dma_frame_buffer);
    dmaStreamSetTransactionSize(PWM_DMA_STREAM1, 2); // Number of edges per 2*FRT-Period
    dmaStreamSetMode(PWM_DMA_STREAM1,
    		PWM_DMA_CR_CHSEL1 | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
			STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
    //dmaStreamEnable(PWM_DMA_STREAM1); // Start DMA

    // Configure DMA stream to Timer ARR
    dmaStreamAllocate(PWM_DMA_STREAM2, 10, NULL, NULL);
    dmaStreamSetPeripheral(PWM_DMA_STREAM2, &(PWMDMA_PWMD.tim->DMAR));// Write to Auto-Reload-Register &(PWMDMA_PWMD.tim->ARR) through DMAR and DCR!
    dmaStreamSetMemory0(PWM_DMA_STREAM2, pwm_dma_timer_buffer);
    dmaStreamSetTransactionSize(PWM_DMA_STREAM2, 2); // Number of edges per 2*FRT-Period
    dmaStreamSetMode(PWM_DMA_STREAM2,
    		PWM_DMA_CR_CHSEL2 | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_HWORD | STM32_DMA_CR_MSIZE_HWORD |
			STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
    //dmaStreamEnable(PWM_DMA_STREAM2); // Start DMA

    // Configure PWM
    adcStartConversion(&ADCD1, &adc_commutate_group, commutatesamples, 2*ADC_FRT_DEFAULT_PERIOD_CYCLES);// TODO: Start in sync!

    PWMDMA_PWMD.tim->DCR = 11; // DMA base address = ARR; DMA Circular mode disable?
    pwmStart(&PWMDMA_PWMD, &pwm_dma_config);
    PWMDMA_PWMD.tim->DCR = 11; // DMA base address = ARR; DMA Circular mode disable?
    pwmEnableChannel(&PWMDMA_PWMD, PWM_DMA_TIM_CH, 0);     // Initial period is 0; output will be low until first duty cycle is DMA'd in
    dmaStreamEnable(PWM_DMA_STREAM2); // Start DMA 2
    dmaStreamEnable(PWM_DMA_STREAM1); // Start DMA 1
}



// DMA für GPIO
#define XPWM_DMA_STREAM1				STM32_DMA2_STREAM1 // OK
#define XPWM_DMA_CR_CHSEL1 			STM32_DMA_CR_CHSEL(6) // OK
// DMA für ARR
#define XPWM_DMA_STREAM2				STM32_DMA1_STREAM1 // ??
#define XPWM_DMA_CR_CHSEL2 			STM32_DMA_CR_CHSEL(3) // OK

// Timmer 1 CH1 kann auch noch Stream 3 triggern!

#define PWM_DMA_TIM_DIER_T1			TIM_DIER_CC1DE // CC1 triggert BEIDE DMA-Streams!
#define PWM_DMA_TIM_DIER_T2			TIM_DIER_UDE

void pwm_dma_init_3(void) // mit 2 timern und DMA1 + DMA2
{
	if(pwm_dma_state == PWM_DMA_RUNNING) return;
	pwm_dma_state = PWM_DMA_RUNNING;

    // Initialize frame buffer
    uint32_t i;
    for (i = 0; i < PWM_DMA_BIT_N; i++) pwm_dma_frame_buffer[i] = 0;   // All color bits are zero duty cycle
    uint32_t tx_high   = GPIO_BSRR_BS_10; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    uint32_t tx_low    = GPIO_BSRR_BR_10; // Pin 10 auf low setzen
    //uint32_t tx_high   = GPIO_BSRR_BS_1; // Dies in den request_buf schreiben, um Pin 10 auf high zu setzen. Nimm CONCAT_SYMBOLS mit PIN_PWM_X...
    //uint32_t tx_low    = GPIO_BSRR_BR_1; // Pin 10 auf low setzen

    // Configure PA0 as AF output
    //palSetPadMode(GPIOA, 1, PAL_MODE_ALTERNATE(1)); //palSetPadMode(GPIOA, 1, PAL_MODE_ALTERNATE(1)); Nur für TIM1&2? Siehe F4-Datenblatt
    pwm_dma_frame_buffer[0] = tx_high;
    pwm_dma_frame_buffer[1] = tx_low;// Test: Pin am Ende der Periode zurücksetzen
    pwm_dma_timer_buffer[0] = 9;//PWM_MAXIMUM_PERIOD_CYCLES / 2;
    pwm_dma_timer_buffer[1] = 9;//PWM_MAXIMUM_PERIOD_CYCLES / 2;

    // PWM Configuration
    #pragma GCC diagnostic ignored "-Woverride-init"                                        // Turn off override-init warning for this struct. We use the overriding ability to set a "default" channel config
    static const PWMConfig pwm_dma_config = {
        .frequency          = PWM_CLOCK_FREQUENCY,
        .period             = PWM_DMA_TRANSFER_PERIOD_TICKS, //Mit dieser Periode wird UDE-Event erzeugt und ein neuer Wert (Länge WS2812_BIT_N) vom DMA ins CCR geschrieben
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Channels default to disabled
            [PWM_DMA_TIM_CH]= {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Turn on the channel we care about
        },
        .cr2                = 0,//PWM_DMA_TIM_CR2, // Master timer
        .dier               = PWM_DMA_TIM_DIER_T1,											// DMA on update event for next period
    };
    static const PWMConfig tim_dma_config = {
        .frequency          = PWM_CLOCK_FREQUENCY,
        .period             = 10000, //Mit dieser Periode wird UDE-Event erzeugt und ein neuer Wert (Länge WS2812_BIT_N) vom DMA ins CCR geschrieben
        .callback           = NULL,
        .channels = {
            [0 ... 3]       = {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Channels default to disabled
            [1]= {.mode = PWM_OUTPUT_DISABLED,  .callback = NULL},         // Turn on the channel we care about
        },
        .cr2                = 0,// Slave timer
        .dier               = PWM_DMA_TIM_DIER_T2,											// DMA on update event for next period
    };
    #pragma GCC diagnostic pop                                                              // Restore command-line warning options

    //PWMD.tim->CR1: ARPE-Bit: Auto-reload preload enable. TODO: Damit rumspielen.
    // Configure DMA stream to GPIO
    dmaStreamAllocate(XPWM_DMA_STREAM1, 10, NULL, NULL);
    dmaStreamSetPeripheral(XPWM_DMA_STREAM1, &(GPIOA->BSRR.W));  // BSSR: Bit-Set-Reset-Register
    dmaStreamSetMemory0(XPWM_DMA_STREAM1, pwm_dma_frame_buffer);
    dmaStreamSetTransactionSize(XPWM_DMA_STREAM1, 2); // Anzahl der Edges je 2*FRT-Periode
    dmaStreamSetMode(XPWM_DMA_STREAM1,
    		XPWM_DMA_CR_CHSEL1 | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
			STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
    //CHSEL(7): Select DMA-channel 7 (TIM8_UP); M2P: Memory 2 Periph; PL: Priority Level
    //dmaStreamEnable(XPWM_DMA_STREAM1); // Start DMA

    // Configure DMA stream to Timer ARR
    dmaStreamAllocate(XPWM_DMA_STREAM2, 10, NULL, NULL);
    dmaStreamSetPeripheral(XPWM_DMA_STREAM2, &(PWMDMA_PWMD.tim->DMAR));  // ARR: Auto-Reload-Register &(PWMDMA_PWMD.tim->ARR)
    dmaStreamSetMemory0(XPWM_DMA_STREAM2, pwm_dma_timer_buffer);
    dmaStreamSetTransactionSize(XPWM_DMA_STREAM2, 2); // Anzahl der Edges je 2*FRT-Periode
    dmaStreamSetMode(XPWM_DMA_STREAM2,
    		XPWM_DMA_CR_CHSEL2 | STM32_DMA_CR_DIR_M2P | STM32_DMA_CR_PSIZE_WORD | STM32_DMA_CR_MSIZE_WORD |
			STM32_DMA_CR_MINC | STM32_DMA_CR_CIRC | STM32_DMA_CR_PL(3));
    //CHSEL(7): Select DMA-channel 7 (TIM8_UP); M2P: Memory 2 Periph; PL: Priority Level
    dmaStreamEnable(XPWM_DMA_STREAM2); // Start DMA

    // Configure PWM
    // NOTE: It's required that preload be enabled on the timer channel CCR register. This is currently enabled in the
    // ChibiOS driver code, so we don't have to do anything special to the timer. If we did, we'd have to start the timer,
    // disable counting, enable the channel, and then make whatever configuration changes we need.
    adcStartConversion(&ADCD1, &adc_commutate_group, commutatesamples, 2*ADC_FRT_DEFAULT_PERIOD_CYCLES);
    // Slave-Timer Tim 2
    //PWMD2.tim->CR1 = PWMD2.tim->CR1 | STM32_TIM_CR1_OPM; // One-Pulse-Mode
    //PWMD2.tim->SMCR = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 ;  // SlaveModeSelection: Trigger Mode; TS: Trigger selection = 000 ->TIM1
    pwmStart(&PWMD2, &tim_dma_config);
    //PWMD2.tim->CR1 = PWMD2.tim->CR1 | STM32_TIM_CR1_OPM; // One-Pulse-Mode
    //PWMD2.tim->SMCR = TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1 ;  // SlaveModeSelection: Trigger Mode; TS: Trigger selection = 000 ->TIM1
    pwmEnableChannel(&PWMD2, 2, 5);

    pwmStart(&PWMDMA_PWMD, &pwm_dma_config);
    pwmEnableChannel(&PWMDMA_PWMD, 1, 1);     // Initial period is 0; output will be low until first duty cycle is DMA'd in
}

void pwm_dma_stop_2(void) {
	if(pwm_dma_state == PWM_DMA_STOPPED) return;
	pwm_dma_state = PWM_DMA_STOPPED;
	pwmStop(&PWMDMA_PWMD); // Stop triggering DMA transfers
	dmaStreamDisable(PWM_DMA_STREAM1);
	dmaStreamRelease(PWM_DMA_STREAM1);
	dmaStreamDisable(PWM_DMA_STREAM2);
	dmaStreamRelease(PWM_DMA_STREAM2);
	adcStopConversion(&ADCD1);
}
