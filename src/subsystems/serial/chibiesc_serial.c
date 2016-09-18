/** @file subsystems/serial/chibiesc_serial.c
 * 	@brief ChibiESC serial interface
 * 	@detail Provides a wrapper around PPRZLink and the various (future) ChibiESC serial drivers
 * 	@addtogroup  ChibiESC_Serial
 * 	@{
 */

#include <src/subsystems/serial/chibiesc_serial.h>

/**
 * @brief   Static SerialTestThread working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 *
 * @param[in] s         the name to be assigned to the stack array
 * @param[in] n         the stack size to be assigned to the thread
 *
 * @todo	Define reasonable stack size (http://www.chibios.org/dokuwiki/doku.php?id=chibios:kb:stacks)
 */
static THD_WORKING_AREA(waSerialTestThread, 128);
/**
 * @brief	SerialTestThread declaration
 */
static THD_FUNCTION(SerialTestThread, arg) {
	(void)arg;
	chRegSetThreadName("SerialTestThread");

	int pprzlink_test_loop = 0;

	while (true) {
		chThdSleepMilliseconds(500);

		// send an 'alive' message to make the paparazzi GCS believe we're an aircraft and display the messages
		//pprz_msg_send_ALIVE(&usb_pprz_tp.trans_tx, &usb_link_dev, PPRZLINK_SENDER_AC_ID, 16, PPRZLINK_MD5SUM);

		// send a telemetry message
		uint8_t chibiesc_mode = 1;
		float chibiesc_bat_volts = sin(pprzlink_test_loop/10.0*3.14159265);
		float chibiesc_rpm = 500.4;
		//pprz_msg_send_CHIBIESC(&usb_pprz_tp.trans_tx, &usb_link_dev, PPRZLINK_SENDER_AC_ID, &chibiesc_mode, &chibiesc_bat_volts, &chibiesc_rpm);

		pprzlink_test_loop++;
		if (pprzlink_test_loop > 19) pprzlink_test_loop = 0;

		palTogglePad(BANK_LED3_DISCO, PIN_LED3_DISCO);
	}
}

/**
 * @brief   Static SerialRXThread working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 *
 * @param[in] s         the name to be assigned to the stack array
 * @param[in] n         the stack size to be assigned to the thread
 *
 * @todo	Define reasonable stack size (http://www.chibios.org/dokuwiki/doku.php?id=chibios:kb:stacks)
 */
static THD_WORKING_AREA(waSerialRXThread, 128);
/**
 * @brief	SerialRXThread declaration
 */
static THD_FUNCTION(SerialRXThread, arg) {
	(void)arg;
	chRegSetThreadName("SerialRXThread");
	// TODO: convert this thread to a function which is callable from all serial subsystems?

	while (true) {
		chThdSleepMilliseconds(50);

		// try receiving messages
		/*if(!usb_pprz_msg_available) {
			//pprz_check_and_parse(&usb_link_dev, &usb_pprz_tp, &usb_pprz_msg_buffer, &usb_pprz_msg_available);
		} else {
			uint8_t msg_id = IdOfPprzMsg(usb_pprz_msg_buffer);
			if (msg_id == DL_PING) {
				palTogglePad(BANK_LED1, PIN_LED1);
			}
		}*/
	}
}

void ce_serial_init(void) {
	// initialize USB interface
	usb_init();

	chThdSleepMilliseconds(1000);
	// initialize PPRZLink-over-USB
	usb_pprz_link_init();

	// Create a test thread
	chThdCreateStatic(waSerialTestThread, sizeof(waSerialTestThread), NORMALPRIO, SerialTestThread, NULL);

	// Create thread for receiving
	chThdCreateStatic(waSerialRXThread, sizeof(waSerialRXThread), NORMALPRIO, SerialRXThread, NULL);
}
/** @} */
