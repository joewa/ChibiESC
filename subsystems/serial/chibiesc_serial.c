/** @file subsystems/serial/chibiesc_serial.c
 * 	@brief ChibiESC serial interface
 * 	@detail Provides a wrapper around PPRZLink and the various (future) ChibiESC serial drivers
 * 	@addtogroup  ChibiESC_Serial
 * 	@{
 */

#include <subsystems/serial/chibiesc_serial.h>

/*void do_stuff(void)
{
	// send a datalink message
	uint8_t ac_id = 42;
	uint8_t settings_index = 42;
	float foo_value = 123.45;
	//pprz_msg_send_SETTING(&pprz_tp.trans_tx, &link_dev, SENDER_AC_ID, &settings_index, &ac_id, &foo_value);
	uint8_t data = 12;
	palTogglePad(GPIOD, PIN_LED3);
	//chnPutTimeout(&SDU1, (const uint8_t *) data, TIME_IMMEDIATE);
	chprintf(&SDU1, "Blubb\r\n");
	//palClearPad(GPIOD, PIN_LED3);
}*/
void do_stuff(void) {
	chprintf(&SDU1, "Test\r\n");
}

/**
 * @brief   Static SerialTestThread working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 *
 * @param[in] s         the name to be assigned to the stack array
 * @param[in] n         the stack size to be assigned to the thread
 *
 * @todo	Define reasonable stack size
 */
static THD_WORKING_AREA(waSerialTestThread, 128);
/**
 * @brief	SerialTestThread declaration
 */
static THD_FUNCTION(SerialTestThread, arg) {
	(void)arg;
	chRegSetThreadName("SerialTestThread");
	while (true) {
		chThdSleepMilliseconds(500);
		palTogglePad(GPIOD, PIN_LED3_DISCO);
		//chprintf(&SDU1, "Test\r\n");
		do_stuff();
	}
}

void ce_serial_init(void) {
	// initialize USB interface
	usb_init();

	//chThdSleepMilliseconds(1000);
	// initialize PPRZLink-over-USB
	//pprz_link_init();

	// Create a test thread
	chThdCreateStatic(waSerialTestThread, sizeof(waSerialTestThread), NORMALPRIO, SerialTestThread, NULL);
}
/** @} */
