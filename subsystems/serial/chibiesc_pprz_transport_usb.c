/** @file subsystems/serial/chibiesc_pprz_transport_usb.c
 * 	@brief PPRZLink over USB transport
 * 	@detail Adapted from PPRZLink Linux example file https://github.com/paparazzi/pprzlink/blob/C_examples/examples/C/linux_uart_pprz_transport.c
 * 	@addtogroup  ChibiESC_PPRZ_Transport_USB
 * 	@{
 */

#include <subsystems/serial/chibiesc_pprz_transport_usb.h>


struct pprz_transport pprz_tp;
struct link_device link_dev;


void put_byte(void *p, long fd __attribute__((unused)), uint8_t data);
bool check_free_space(void *p, long *fd __attribute__((unused)), uint16_t len);
void put_buffer(void *p, long fd, const uint8_t *data, uint16_t len);
void send_message(void *p __attribute__((unused)), long fd __attribute__((unused)));
uint8_t get_byte(void *p);
uint16_t char_available(void *p);

/**
 * @brief	Write one byte to USB
 *
 * @todo	Add description of parameters
 * @todo	Add implementation
 */
void put_byte(void *p, long fd __attribute__((unused)), uint8_t data) {
	// add implementation here to write one byte to USB
	//palSetPad(GPIOD, PIN_LED3);
	chSequentialStreamPut(&SDU1, data);
	//palClearPad(GPIOD, PIN_LED3);
	//chnPutTimeout(&SDU1, data, TIME_IMMEDIATE);
	//palTogglePad(GPIOD, PIN_LED3);
}

/**
 * @brief	Check if there is enough space to send len bytes to USB
 *
 * Always returns true
 * @param[in]	p	Pointer to ???
 * @param[in]	fd	Pointer to ???
 * @param[in]	len	Length of the message to send
 * @return	Returns a boolean which is always true
 * @todo	Add description of parameters
 * @todo	Check if always returning 'true' is appropriate
 */
bool check_free_space(void *p, long *fd __attribute__((unused)), uint16_t len) {
	return true;
}

/**
 * @brief	Calls \ref put_buffer byte by byte
 *
 * @todo	Add description of parameters
 * @todo	Check if it is usefule to implement a function here that writes multiple bytes directly to the device
 */
void put_buffer(void *p, long fd, const uint8_t *data, uint16_t len) {
	int i = 0;
	for (i = 0; i < len; i++) {
		put_byte(p, fd, data[i]);
	}

	//palTogglePad(GPIOD, PIN_LED3);
	//sdWrite(&SDU1, data, len);
	//chnWriteTimeout(&SDU1, data, len, TIME_IMMEDIATE);
	//chSequentialStreamWrite(&SDU1, data, len);
}

/**
 * @brief	Called after each message
 *
 * @todo	Add description of parameters
 */
void send_message(void *p __attribute__((unused)), long fd __attribute__((unused))) {
	// here we could e.g. flush the buffer, but usually not needed (says example file)
}

/**
 * @brief	Read one char from the USB
 *
 * @todo	Add description of parameters
 * @todo	Implement function for reading, not needed for sending only
 */
uint8_t get_byte(void *p) {
	return 0; // No reading. Further implementation not needed for sending only
}

/**
 * @brief	Return number of chars that are available for reading
 *
 * @todo	Add description of parameters
 * @todo	Implement function for reading, not needed for sending only
 */
uint16_t char_available(void *p) {
	return 0; // No reading. Further implementation not needed for sending only
}

void pprz_link_init(void) {
	pprz_transport_init(&pprz_tp); // initialize the PPRZ transport

	// setup the link device
	link_dev.periph = NULL; // if you want to pass a pointer to the other functions, set it here
	link_dev.check_free_space = (check_free_space_t) check_free_space;
	link_dev.put_byte = (put_byte_t) put_byte;
	link_dev.put_buffer = (put_buffer_t) put_buffer;
	link_dev.send_message = (send_message_t) send_message;
	link_dev.char_available = (char_available_t) char_available;
	link_dev.get_byte = (get_byte_t) get_byte;
}

/** @} */
