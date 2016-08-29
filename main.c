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
#include "subsystems/serial/chibiesc_serial.h"

#include "misc.h"
//#include "bal_interface.h"

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {

  (void)arg;
  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOD, PIN_LED1);       /* Orange.  */
    chThdSleepMilliseconds(500);
    palClearPad(GPIOD, PIN_LED1);     /* Orange.  */
    chThdSleepMilliseconds(500);
  }
}

/*
 * Application entry point.
 */
char testtext[8] = "Hallo\n";

float testfloat = 3.14;



//#define chprintf printf
// BEGIN copy&paste from stmbl usb_cdc

#include "ringbuf.h"
#include "bal.h"
#include "bal_term.h"

#define RX_QUEUE_SIZE  512
uint8_t usb_rx_buf_raw[RX_QUEUE_SIZE];
uint8_t usb_rx_string[RX_QUEUE_SIZE];
//uint8_t usb_rx_buf[RX_QUEUE_SIZE];

struct ringbuf usb_rx_buf = { .buf = (char[RX_QUEUE_SIZE]) {0}, .bufsize = RX_QUEUE_SIZE };

uint16_t cr_count = 0;

static uint16_t VCP_DataRx(uint8_t *buf, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++) {
    	if (buf[i] == 0x0A)
    	    cr_count++;
        rb_putc(&usb_rx_buf, buf[i]);
    }
    return 1; //USBD_OK;
}


#define USB_CDC_FIRST_ASCII 32    // erstes Ascii-Zeichen
#define USB_CDC_LAST_ASCII  255   // letztes Ascii-Zeichen
uint16_t USB_VCP_get_string(char *ptr)
{
    uint16_t akt_pos = 0;
    char wert;

    // test ob eine Endekennung empfangen wurde
    if (cr_count == 0) return 0;

    if (usb_rx_buf.len == 0) return 0;

    // kompletten String bis zur Endekennung auslesen
    // (oder bis Puffer leer ist)
    // es werden nur Ascii-Zeichen übergeben
    do {
        rb_getc(&usb_rx_buf, &wert);
        if ((wert >= USB_CDC_FIRST_ASCII) && (wert <= USB_CDC_LAST_ASCII)) {
            *(ptr + akt_pos) = wert;
            akt_pos++;
        }
    } while ((usb_rx_buf.len != 0) && (wert != 0x0A)); // 0x0A = '\n'

    // Stringende anhängen
    *(ptr + akt_pos) = 0x00;

    // eine Endekennung wurde bearbeitet
    cr_count--;

    return akt_pos;
}



void USB_VCP_send_string(unsigned char *ptr)
{ //TODO: Joerg implementiere senden von 0-terminiertem string. Implementiere was Schnelleres als PRINTF!!!
	chprintf("%s", ptr);
    /*while (*ptr != 0) {
        // send a queued byte - copy to usb stack buffer
        APP_Rx_Buffer[APP_Rx_ptr_in++] = *ptr;
        ptr++;

            // To avoid buffer overflow
            if (APP_Rx_ptr_in >= APP_RX_DATA_SIZE) {
               APP_Rx_ptr_in = 0;
            }
    }*/
}

//END copy&paste



int main(void) {
	int len;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();
  //osalSysEnable(); // just copied here from example to test why LED blinking doesn't work

  /*
   * Activates the serial driver 2 using the driver default configuration.
   * PA2(TX) and PA3(RX) are routed to USART2.
   */
  //sdStart(&SD2, NULL);
  //palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
  //palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));

  /*
   * Creates the example thread.
   */
  //chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

  //usb_init(); // Serial over USB initialization
  ce_serial_init();
  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */

  chThdSleepMilliseconds(2000);
  hal_init();

  hal_set_comp_type("foo"); // default pin for mem errors
  HAL_PIN(bar) = 0.0;

  //feedback comps
  #include "comps/term.comp"
  hal_comp_init();

  while (true) {
	chThdSleepMilliseconds(1);
    //if (palReadPad(GPIOA, GPIOA_BUTTON))
    //  TestThread(&SD2);
	//palSetPad(GPIOD, PIN_LED1);       /* Orange.  */
	//palSetPad(GPIOD, PIN_LED2);
	//palSetPad(GPIOD, PIN_LED3_DISCO);
	//chprintf(&SDU1,"Hallo %f\n", testfloat);

	len = chSequentialStreamRead(&SDU1, (uint8_t*)usb_rx_buf_raw, 1);
	VCP_DataRx(usb_rx_buf_raw, len);
	//hal_run_nrt(1); // Calls term which calls USB_VCP_get_string. Call from own thread, NOT HERE!!!
	if( USB_VCP_get_string(usb_rx_string) ) {
		palTogglePad(GPIOD, PIN_LED2); // usb_rx_string holds the result of "getln"
		chprintf(&SDU1,"%s", usb_rx_string); // Echo recieved string.
	}

	//usb_put_buffer(0, 0, testtext, 5);
	//printf("Hallo\n");
	//palClearPad(GPIOD, PIN_LED1);     /* Orange.  */
	//palClearPad(GPIOD, PIN_LED2);
	//palClearPad(GPIOD, PIN_LED3_DISCO);
	chThdSleepMilliseconds(1);
  }
}
