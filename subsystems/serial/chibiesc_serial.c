/** @file subsystems/serial/chibiesc_serial.c
 * 	@brief ChibiESC serial interface
 * 	@detail Provides a wrapper around PPRZLink and the various (future) ChibiESC serial drivers
 * 	@addtogroup  ChibiESC_Serial
 * 	@{
 */

#include <subsystems/serial/chibiesc_serial.h>

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

		// send an 'alive' message to make the paparazzi GCS believe we're an aircraft and display the messages
		pprz_msg_send_ALIVE(&pprz_tp.trans_tx, &link_dev, PPRZLINK_SENDER_AC_ID, 16, PPRZLINK_MD5SUM);

		// send a telemetry message
		uint8_t chibiesc_mode = 1;
		float chibiesc_bat_volts = 1.34;
		float chibiesc_rpm = 500.4;
		pprz_msg_send_CHIBIESC(&pprz_tp.trans_tx, &link_dev, PPRZLINK_SENDER_AC_ID, &chibiesc_mode, &chibiesc_bat_volts, &chibiesc_rpm);

		palTogglePad(GPIOD, PIN_LED3_DISCO);
	}
}

void ce_serial_init(void) {
	// initialize USB interface
	usb_init();

	chThdSleepMilliseconds(1000);
	// initialize PPRZLink-over-USB
	pprz_link_init();

	// Create a test thread
	chThdCreateStatic(waSerialTestThread, sizeof(waSerialTestThread), NORMALPRIO, SerialTestThread, NULL);
}
/** @} */
