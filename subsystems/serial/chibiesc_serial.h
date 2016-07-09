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

//#include <subsystems/serial/chibiesc_pprz_transport_usb.h>

// for telemetry messages
//#include <subsystems/pprzlink/include/messages.h>
// for datalink messages
//#include <subsystems/pprzlink/include/dl_protocol.h>

//#include <unistd.h>

//struct pprz_transport pprz_tp;
//struct link_device link_dev;

#define SENDER_AC_ID 0

extern void do_stuff(void);

extern void ce_serial_init(void);

#endif /* _CHIBIESC_SERIAL_H_ */

/** @} */
