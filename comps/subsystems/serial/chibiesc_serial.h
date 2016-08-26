/** @file subsystems/serial/chibiesc_serial.h
 * 	@brief ChibiESC serial interface
 * 	@detail Provides a wrapper around PPRZLink and the various (future) ChibiESC serial drivers
 * 	@addtogroup  ChibiESC_Serial
 * 	@{
 */

#ifndef _CHIBIESC_SERIAL_H_
#define _CHIBIESC_SERIAL_H_

#include "hal.h"
#include <subsystems/serial/chibiesc_usb.h>

#include <subsystems/serial/chibiesc_pprz_transport_usb.h>

// for telemetry messages
#include <subsystems/pprzlink/include/messages.h>
// for datalink messages
#include <subsystems/pprzlink/include/dl_protocol.h>

#include <unistd.h>

#include <math.h> // for testing (sin)

// PPRZLink message sender aircraft ID
#define PPRZLINK_SENDER_AC_ID 19
// PPRZLink alive message checksum, must match the checksum in the paparazzi-generated var/aircrafts/.../ap/generated/airframe.h file for the PPRZLINK_SENDER_AC_ID
#define PPRZLINK_MD5SUM ((uint8_t*)"\274\002\046\311\007\062\244\056\315\375\327\330\040\232\343\274")

// for receiving PPRZLink messages
#define PPRZ_MSG_BUFFER_SIZE	2048
static uint8_t usb_pprz_msg_buffer[PPRZ_MSG_BUFFER_SIZE];
static bool usb_pprz_msg_available = false;
#define IdOfPprzMsg(x) (x[1])

extern void ce_serial_init(void);

#endif /* _CHIBIESC_SERIAL_H_ */

/** @} */
