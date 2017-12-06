/*
 * max17043.h
 *
 *  Created on: Dec 6, 2017
 *      Author: Station13
 */

#ifndef MAX17043_H_
#define MAX17043_H_

/* MAX17043 Register Definitions */
#define MAX17043_VCELL    0x02 // R - 12-bit A/D measurement of battery voltage
#define MAX17043_SOC      0x04 // R - 16-bit state of charge (SOC)
#define MAX17043_MODE     0x06 // W - Sends special commands to IC
#define MAX17043_VERSION  0x08 // R - Returns IC version
#define MAX17043_CONFIG   0x0C // R/W - Battery compensation (default 0x971C)
#define MAX17043_COMMAND  0xFE // W - Sends special comands to IC

/* MAX17043 Config Register Bits */
#define MAX17043_CONFIG_SLEEP     7
#define MAX17043_CONFIG_ALERT     5
#define MAX17043_CONFIG_THRESHOLD 0
/* MAX17043 Mode Register Commands */
#define MAX17043_MODE_QUICKSTART 0x4000

/* MAX17043 Command Register Commands */
#define MAX17043_COMMAND_POR 0x5400

/* MAX17043 7-Bit I2C Address */

#endif /* MAX17043_H_ */
