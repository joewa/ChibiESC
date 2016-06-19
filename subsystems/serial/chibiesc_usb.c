/**
 * @file subsystems/serial/chibiesc_usb.c
 * @brief Serial over USB driver
 * @addtogroup ChibiESC_USB
 * @{
 */

#include "subsystems/serial/chibiesc_usb.h"

// ####################### Endpoints config #############################
/*
 * Endpoints to be used for USBD1.
 */
#define USBD1_DATA_REQUEST_EP           1	///< Endpoint number of the data request endpoint. Adapted from ChibiOS demo file.
#define USBD1_DATA_AVAILABLE_EP         1	///< Endpoint number of the data available endpoint. Adapted from ChibiOS demo file.
#define USBD1_INTERRUPT_REQUEST_EP      2	///< Endpoint number of the interrupt request endpoint. Adapted from ChibiOS demo file.

/*
 * Endpoint states
 */
static USBInEndpointState	ep1instate;		///< USBEndpointState associated to the EP1 IN endpoint. Used in \ref ep1config.
static USBOutEndpointState	ep1outstate;	///< USBEndpointState associated to the EP1 OUT endpoint. Used in \ref ep2config.
static USBInEndpointState	ep2instate;		///< USBEndpointState associated to the EP2 IN endpoint. Used in \ref ep2config.

/**
 * @brief   EP1 initialization structure (both IN and OUT).
 *
 * Adapted from ChibiOS demo file.
 */
static const USBEndpointConfig ep1config = {
	USB_EP_MODE_TYPE_BULK,	// Type and mode of the endpoint: Bulk endpoint
	NULL,					// Setup packet notification callback: NULL
	sduDataTransmitted,		// IN endpoint notification callback: defined in ChibiOS
	sduDataReceived,		// OUT endpoint notification callback: defined in ChibiOS
	0x0040,					// IN endpoint maximum packet size: 64
	0x0040,					// OUT endpoint maximum packet size: 64
	&ep1instate,			// USBEndpointState associated to the IN endpoint: ...
	&ep1outstate,			// USBEndpointState associated to the OUT endpoint: ...
	4,						// Reserved field, not currently used
	NULL					// Pointer to a buffer for setup packets: NULL for non-control endpoints
};

/**
 * @brief   EP2 initialization structure (IN only).
 *
 * Adapted from ChibiOS demo file.
 */
static const USBEndpointConfig ep2config = {
	USB_EP_MODE_TYPE_INTR,	///< Type and mode of the endpoint: Interrupt endpoint
	NULL,						///< Setup packet notification callback: NULL
	sduInterruptTransmitted,	///< IN endpoint notification callback: defined in ChibiOS
	NULL,						///< OUT endpoint notification callback: NULL
	0x0010,					///< IN endpoint maximum packet size: 16
	0x0000,					///< OUT endpoint maximum packet size: 0 (not used)
	&ep2instate,				///< USBEndpointState associated to the IN endpoint: ...
	NULL,						///< USBEndpointState associated to the OUT endpoint: NULL (not used)
	1,						///< Reserved field, not currently used
	NULL						///< Pointer to a buffer for setup packets: NULL for non-control endpoints
};

// ####################### Events callback ##############################
/**
 * @brief	USB events callback
 *
 * Handles the USB driver global events. Adapted from ChibiOS demo file.
 * @param[in]	ubsp	pointer to the USBDriver object triggering the callback
 * @param[in]	event	event type
 */
static void usb_event_cb(USBDriver *usbp, usbevent_t event) {
	switch (event) {
		case USB_EVENT_RESET:
			return;
		case USB_EVENT_ADDRESS:
			return;
		case USB_EVENT_CONFIGURED:
			chSysLockFromISR();

			/* Enables the endpoints specified into the configuration.
       	   	   Note, this callback is invoked from an ISR so I-Class functions
       	   	   must be used.*/
			usbInitEndpointI(usbp, USBD1_DATA_REQUEST_EP, &ep1config); // Enables data request endpoint
			usbInitEndpointI(usbp, USBD1_INTERRUPT_REQUEST_EP, &ep2config); // Enables interrupt request endpoint

			/* Resetting the state of the CDC subsystem.*/
			sduConfigureHookI(&SDU1);

			chSysUnlockFromISR();
			return;
		case USB_EVENT_SUSPEND:
			return;
		case USB_EVENT_WAKEUP:
			return;
		case USB_EVENT_STALLED:
			return;
	}
	return;
}

// ####################### USB DESCRIPTOR ###############################
/**
 * @brief	USB Device Descriptor.
 *
 * Adapted from ChibiOS demo file
 */
static const uint8_t vcom_device_descriptor_data[18] = {
	USB_DESC_DEVICE       (0x0200,        ///< bcdUSB (2.0)
                           0x02,          ///< bDeviceClass (CDC)
                           0x00,          ///< bDeviceSubClass
                           0x00,          ///< bDeviceProtocol
                           0x40,          ///< bMaxPacketSize
                           0x0483,        ///< idVendor (ST)
                           0x5740,        ///< idProduct
                           0x0200,        ///< bcdDevice
                           1,             ///< iManufacturer
                           2,             ///< iProduct
                           3,             ///< iSerialNumber
                           1)             ///< bNumConfigurations
};

/**
 * @brief	Device Descriptor wrapper.
 *
 * From ChibiOS demo file
 */
static const USBDescriptor vcom_device_descriptor = {
	sizeof vcom_device_descriptor_data,
	vcom_device_descriptor_data
};

/**
 * @brief	Configuration Descriptor tree for a CDC.
 *
 * Adapted from ChibiOS demo file
 */
static const uint8_t vcom_configuration_descriptor_data[67] = {
	/* Configuration Descriptor.*/
	USB_DESC_CONFIGURATION(67,							///< wTotalLength
                           0x02,						///< bNumInterfaces
                           0x01,						///< bConfigurationValue
                           0,							///< iConfiguration
                           0xC0,						///< bmAttributes (self powered)
                           50),							///< bMaxPower (100mA)
	/* Interface Descriptor.*/
	USB_DESC_INTERFACE    (0x00,						///< bInterfaceNumber
                           0x00,						///< bAlternateSetting
                           0x01,						///< bNumEndpoints
                           0x02,						///< bInterfaceClass (Communications Interface Class, CDC section 4.2)
                           0x02,						///< bInterfaceSubClass (Abstract Control Model, CDC section 4.3)
                           0x01,						///< bInterfaceProtocol (AT commands, CDC section 4.4)
                           0),							///< iInterface
	/* Header Functional Descriptor (CDC section 5.2.3).*/
	USB_DESC_BYTE         (5),							///< bLength
	USB_DESC_BYTE         (0x24),						///< bDescriptorType (CS_INTERFACE)
	USB_DESC_BYTE         (0x00),						///< bDescriptorSubtype (Header Functional Descriptor
	USB_DESC_BCD          (0x0110),						///< bcdCDC
	/* Call Management Functional Descriptor. */
	USB_DESC_BYTE         (5),							///< bFunctionLength
	USB_DESC_BYTE         (0x24),						///< bDescriptorType (CS_INTERFACE)
	USB_DESC_BYTE         (0x01),						///< bDescriptorSubtype (Call Management Functional Descriptor)
	USB_DESC_BYTE         (0x00),						///< bmCapabilities (D0+D1)
	USB_DESC_BYTE         (0x01),						///< bDataInterface
	/* ACM Functional Descriptor.*/
	USB_DESC_BYTE         (4),							///< bFunctionLength
	USB_DESC_BYTE         (0x24),						///< bDescriptorType (CS_INTERFACE)
	USB_DESC_BYTE         (0x02),						///< bDescriptorSubtype (Abstract Control Management Descriptor)
	USB_DESC_BYTE         (0x02),						///< bmCapabilities
	/* Union Functional Descriptor.*/
	USB_DESC_BYTE         (5),							///< bFunctionLength
	USB_DESC_BYTE         (0x24),						///< bDescriptorType (CS_INTERFACE)
	USB_DESC_BYTE         (0x06),						///< bDescriptorSubtype (Union Functional Descriptor)
	USB_DESC_BYTE         (0x00),						///< bMasterInterface (Communication Class Interface)
	USB_DESC_BYTE         (0x01),						///< bSlaveInterface0 (Data Class Interface)
	/* Endpoint 2 Descriptor.*/
	USB_DESC_ENDPOINT     (USBD1_INTERRUPT_REQUEST_EP|0x80,
                           0x03,						///< bmAttributes (Interrupt)
                           0x0008,						///< wMaxPacketSize
                           0xFF),						///< bInterval
	/* Interface Descriptor.*/
	USB_DESC_INTERFACE    (0x01,						///< bInterfaceNumber
                           0x00,						///< bAlternateSetting
                           0x02,						///< bNumEndpoints
                           0x0A,						///< bInterfaceClass (Data Class Interface, CDC section 4.5)
                           0x00,						///< bInterfaceSubClass (CDC section 4.6)
                           0x00,						///< bInterfaceProtocol (CDC section 4.7)
                           0x00),						///< iInterface
	/* Endpoint 3 Descriptor.*/
	USB_DESC_ENDPOINT     (USBD1_DATA_AVAILABLE_EP,		///< bEndpointAddress
                           0x02,						///< bmAttributes (Bulk)
                           0x0040,						///< wMaxPacketSize
                           0x00),						///< bInterval
	/* Endpoint 1 Descriptor.*/
	USB_DESC_ENDPOINT     (USBD1_DATA_REQUEST_EP|0x80,	///< bEndpointAddress
                           0x02,						///< bmAttributes (Bulk)
                           0x0040,						///< wMaxPacketSize
                           0x00)						///< bInterval
};

/**
 * @brief	Configuration Descriptor wrapper.
 *
 * From ChibiOS demo file
 */
static const USBDescriptor vcom_configuration_descriptor = {
	sizeof vcom_configuration_descriptor_data,
	vcom_configuration_descriptor_data
};

/**
 * @brief	U.S. English language identifier.
 *
 * From ChibiOS demo file
 */
static const uint8_t vcom_string0[] = {
	USB_DESC_BYTE(4),						///< bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING),	///< bDescriptorType
	USB_DESC_WORD(0x0409)					///< wLANGID (U.S. English)
};

/**
 * @brief	Vendor string.
 *
 * From ChibiOS demo file
 */
static const uint8_t vcom_string1[] = {
	USB_DESC_BYTE(38),					///< bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING),	///< bDescriptorType
	'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
	'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
	'c', 0, 's', 0
};

/**
 * @brief	Device Description string.
 *
 * From ChibiOS demo file
 */
static const uint8_t vcom_string2[] = {
	USB_DESC_BYTE(56),					///< bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING),	///< bDescriptorType
	'C', 0, 'h', 0, 'i', 0, 'b', 0, 'i', 0, 'O', 0, 'S', 0, '/', 0,
	'R', 0, 'T', 0, ' ', 0, 'V', 0, 'i', 0, 'r', 0, 't', 0, 'u', 0,
	'a', 0, 'l', 0, ' ', 0, 'C', 0, 'O', 0, 'M', 0, ' ', 0, 'P', 0,
	'o', 0, 'r', 0, 't', 0
};

/**
 * @brief	Serial Number string.
 *
 * From ChibiOS demo file
 */
static const uint8_t vcom_string3[] = {
	USB_DESC_BYTE(8),						///< bLength
	USB_DESC_BYTE(USB_DESCRIPTOR_STRING),	///< bDescriptorType
	'0' + CH_KERNEL_MAJOR, 0,
	'0' + CH_KERNEL_MINOR, 0,
	'0' + CH_KERNEL_PATCH, 0
};

/**
 * @brief	Strings wrappers array.
 *
 * From ChibiOS demo file
 */
static const USBDescriptor vcom_strings[] = {
	{sizeof vcom_string0, vcom_string0},
	{sizeof vcom_string1, vcom_string1},
	{sizeof vcom_string2, vcom_string2},
	{sizeof vcom_string3, vcom_string3}
};

/**
 * @brief	Handles the GET_DESCRIPTOR callback
 *
 * All required descriptors must be handled here. From ChibiOS demo file
 */
static const USBDescriptor *usb_get_descriptor_cb(USBDriver *usbp, uint8_t dtype, uint8_t dindex, uint16_t lang) {
	(void)usbp;
	(void)lang;
	switch (dtype) {
		case USB_DESCRIPTOR_DEVICE:
			return &vcom_device_descriptor;
		case USB_DESCRIPTOR_CONFIGURATION:
			return &vcom_configuration_descriptor;
		case USB_DESCRIPTOR_STRING:
			if (dindex < 4)
				return &vcom_strings[dindex];
	}
	return NULL;
}

// ######################### SOF handler ###############################
/**
 * @brief	Handles the USB driver global events.
 *
 * From ChibiOS demo file
 */
static void sof_cb(USBDriver *usbp) {
	(void)usbp;

	osalSysLockFromISR();
	sduSOFHookI(&SDU1);
	osalSysUnlockFromISR();
}

// ####################### Driver configuration #########################
/**
 * @brief	USB driver configuration
 */
const USBConfig usbcfg = {
	usb_event_cb,				///< USB events callback
	usb_get_descriptor_cb,		///< Device GET_DESCRIPTOR request callback
	sduRequestsHook,			///< Requests hook callback (defined in ChibiOS)
	sof_cb						///< Start Of Frame callback
};

/**
 * @brief	Serial over USB driver configuration
 */
const SerialUSBConfig serusbcfg = {
	&USBD1,						///< USB driver to use
	USBD1_DATA_REQUEST_EP,		///< Bulk IN endpoint used for outgoing data transfer
	USBD1_DATA_AVAILABLE_EP,	///< Bulk OUT endpoint used for incoming data transfer
	USBD1_INTERRUPT_REQUEST_EP	///< Interrupt IN endpoint used for notifications
};

/**
 * @brief   Static USBTestThread working area allocation.
 * @details This macro is used to allocate a static thread working area
 *          aligned as both position and size.
 *
 * @param[in] s         the name to be assigned to the stack array
 * @param[in] n         the stack size to be assigned to the thread
 *
 * @todo	Define reasonable stack size
 */
static THD_WORKING_AREA(waUSBTestThread, 128);
/**
 * @brief	USBTestThread declaration
 */
static THD_FUNCTION(USBTestThread, arg) {
	(void)arg;
	chRegSetThreadName("USBTestThread");
	while (true) {
		chThdSleepMilliseconds(500);
		chprintf(&SDU1, "Test\r\n");
	}
}

/**
 * @brief	Initializes a serial over USB CDC driver
 */
void usb_init(void) {
	sduObjectInit(&SDU1);			// initializes a generic full duplex driver object
	sduStart(&SDU1, &serusbcfg);	// configures and starts the driver

	/*
	 * Activates the USB driver and then the USB bus pull-up on D+.
	 * Note, a delay is inserted in order to not have to disconnect the cable
	 * after a reset.
	 */
	usbDisconnectBus(serusbcfg.usbp);
	chThdSleepMilliseconds(1500);
	usbStart(serusbcfg.usbp, &usbcfg);
	usbConnectBus(serusbcfg.usbp);

	/*
	 * Creates the test thread.
	 */
	chThdCreateStatic(waUSBTestThread, sizeof(waUSBTestThread), NORMALPRIO, USBTestThread, NULL);
}

/** @} */
