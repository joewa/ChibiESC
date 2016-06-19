/** @file subsystems/serial/chibiesc_usb.h
 * 	@brief Serial over USB driver
 * 	@addtogroup  ChibiESC_USB
 * 	@{
 */

#ifndef _CHIBIESC_USB_H_
#define _CHIBIESC_USB_H_

#include "hal.h"


extern const USBConfig usbcfg;		///< USB driver configuration structure
extern const SerialUSBConfig serusbcfg;	///< Serial over USB configuration structure
static SerialUSBDriver SDU1;		///< Full duplex serial driver class

void usb_init(void);				// Serial over USB initialization

#endif /* _CHIBIESC_USB_H_ */

/** @} */
