/** @file subsystems/serial/chibiesc_pprz_transport_usb.c
 * 	@brief PPRZLink over USB transport
 * 	@detail Adapted from PPRZLink Linux example file https://github.com/paparazzi/pprzlink/blob/C_examples/examples/C/linux_uart_pprz_transport.c
 * 	@addtogroup  ChibiESC_PPRZ_Transport_USB
 * 	@{
 */

#include <subsystems/serial/chibiesc_pprz_transport_usb.h>


struct pprz_transport pprz_tp;
struct link_device link_dev;

#define USB_RX_BUFFER_SIZE	2048
static uint8_t usb_rx_buffer[USB_RX_BUFFER_SIZE];
static int usb_rx_read_pos = 0;
static int usb_rx_write_pos = 0;

void put_byte(void *p, long fd __attribute__((unused)), uint8_t data);
bool check_free_space(void *p, long *fd __attribute__((unused)), uint16_t len);
void put_buffer(void *p, long fd, const uint8_t *data, uint16_t len);
void send_message(void *p __attribute__((unused)), long fd __attribute__((unused)));
uint8_t get_byte(void *p);
uint16_t char_available(void *p);


/**
 * @brief   Static USBRXThread working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 *
 * @param[in] s         the name to be assigned to the stack array
 * @param[in] n         the stack size to be assigned to the thread
 *
 * @todo	Define reasonable stack size (http://www.chibios.org/dokuwiki/doku.php?id=chibios:kb:stacks)
 */
static THD_WORKING_AREA(waUSBRXThread, 256);
/**
 * @brief	USBRXThread declaration
 */
static THD_FUNCTION(USBRXThread, arg) {
	(void)arg;
	chRegSetThreadName("USBRXThread");

	uint8_t buffer[128];
	int i;
	int len;

	while (true) {
		// read (1 byte?) from SDU1 into buffer
		// returns number pf bytes transferred
		len = chSequentialStreamRead(&SDU1, (uint8_t*) buffer, 1);

		for (i = 0; i < len; i++) {
			usb_rx_buffer[usb_rx_write_pos++] = buffer[i];

			if(usb_rx_write_pos == USB_RX_BUFFER_SIZE) {
				usb_rx_write_pos = 0;
			}
			palTogglePad(GPIOD, PIN_LED2);
		}
	}
}


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
 */
uint8_t get_byte(void *p) {
	uint8_t got_byte;
	got_byte = usb_rx_buffer[usb_rx_read_pos++];
	if(usb_rx_read_pos == USB_RX_BUFFER_SIZE) {
		usb_rx_read_pos = 0;
	}
	return got_byte; // No reading. Further implementation not needed for sending only
}

/**
 * @brief	Return number of chars that are available for reading
 *
 * @todo	Add description of parameters
 */
uint16_t char_available(void *p) {
	uint16_t available_bytes = 0;

	if (usb_rx_write_pos >= usb_rx_read_pos) {
		// i.e. write_pos = 5, read_pos = 2 -> bytes 2,3,4 available -> 3 bytes
		available_bytes = usb_rx_write_pos - usb_rx_read_pos;
	} else {
		// i.e. write_pos = 2, read_pos = 2046 -> bytes 2046,2047,0,1 available -> 4 bytes
		available_bytes = USB_RX_BUFFER_SIZE - usb_rx_read_pos + usb_rx_write_pos;
	}
	return available_bytes;
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

	// Create thread for receiving
	chThdCreateStatic(waUSBRXThread, sizeof(waUSBRXThread), NORMALPRIO, USBRXThread, NULL);
}

/** @} */
