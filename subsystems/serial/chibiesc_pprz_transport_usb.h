/** @file subsystems/serial/chibiesc_pprz_transport_usb.h
 * 	@brief PPRZLink over USB transport
 * 	@detail Adapted from PPRZLink Linux example file https://github.com/paparazzi/pprzlink/blob/C_examples/examples/C/linux_uart_pprz_transport.h
 * 	@addtogroup  ChibiESC_PPRZ_Transport_USB
 * 	@{
 */

#ifndef _CHIBIESC_PPRZ_TRANSPORT_USB_H_
#define _CHIBIESC_PPRZ_TRANSPORT_USB_H_

//#include <subsystems/pprzlink/include/pprz_transport.h>

#include <subsystems/serial/chibiesc_usb.h> // required in order to use SDU1

#define DOWNLINK TRUE // send PPRZLink messages 'from aircraft to ground'

extern struct pprz_transport usb_pprz_tp;
extern struct link_device usb_link_dev;

extern void usb_pprz_link_init(void);

#endif /* _CHIBIESC_PPRZ_TRANSPORT_USB_H_ */

/** @} */
