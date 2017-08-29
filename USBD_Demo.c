/*----------------------------------------------------------------------------
 *      RL-ARM - USB
 *----------------------------------------------------------------------------
 *      Name:    USBD_Demo.c
 *      Purpose: USB Device Demonstration
 *      Rev.:    V4.70
 *----------------------------------------------------------------------------
 *      This code is part of the RealView Run-Time Library.
 *      Copyright (c) 2004-2013 KEIL - An ARM Company. All rights reserved.
 *---------------------------------------------------------------------------*/

#include <RTL.h>
#include <rl_usb.h>
#include <stm32f10x.h>                         /* STM32F10x Definitions      */
#include "DAP_config.h"
#include "ARM_DAP\DAP.h"

extern void usbd_hid_process (void);

#define	USB_DELAY		1000
#define	LED_DELAY		500

void delay (unsigned long i)
{
	unsigned long j;
		
	for (; i; i--)
		for (j = 0x1ff; j; j--);
}

int main (void) 
{
	DAP_Setup();                          // DAP Setup 
	
	usbd_init();                          /* USB Device Initialization          */
	usbd_connect(__FALSE);                 /* USB Device Connect                 */
	delay(USB_DELAY);
	usbd_connect(__TRUE);                 /* USB Device Connect                 */

	LED_CONNECTED_OUT(1);
	while (!usbd_configured())
	{
		LED_CONNECTED_OUT(1);
		delay(LED_DELAY);
		LED_CONNECTED_OUT(0);
		delay(LED_DELAY);
	}

	while (1)
    {
	    LED_CONNECTED_OUT(1);
		usbd_hid_process();                 // Process USB HID Data
	}
}
