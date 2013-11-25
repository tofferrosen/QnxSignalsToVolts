/*
 * Measurer.h
 *
 *  Created on: Nov 20, 2013
 *      Author: Christoffer Rosen, Lennard Streat
 *
 *  Measures the voltages of a wave by converting an analog wave to digital
 *  data and sends it to Freescale
 */

#include <stdint.h>						/* Resource for uintptr_t */
#include <sys/mman.h>					/* Resource for mmap_device_io */
#include <hw/inout.h>					/* Resource for in and out fns */
#include <sys/neutrino.h>       	 	/* Resource(s): ThreadCtl() */
#include <cstdlib>
#include <iostream>

#ifndef MEASURER_H_
#define MEASURER_H_

#define BASE_ADDR ( 0x280 )						/* Base address to A/D converter */
#define LSB_OFFSET ( 0 )						/* The least significant byte of data */
#define MSB_OFFSET ( 1 )						/* The most significant byte of data */
#define PORTA_OFFSET (8)						/* PORT A */
#define PORTA_ADDR (BASE_ADDR + PORTA_OFFSET)	/* PORT A ADDR */
#define AD_REGISTER_OFFSET ( 2 )				/* AD CHANEL OFFSET */
#define AD_GAIN_SCAN_OFFSET ( 3 )				/* Analog input status offset */
#define AD_CHANEL ( 0x44 ) 						/* AD Chanel */
#define INPUT_RANGE_REGISTER ( BASE_ADDR + 3)	/* Input range register */
#define VOLTAGE_RANGE (0x01)					/* Range of input voltage +-5V (gain of 2) */
#define WAIT_BIT (0b00100000)					/* The WAIT bit for analog input circuit */

/* Port Direction Register */
#define PORT_DIR_OFFSET (11)
#define PORT_DIR_ADDR (BASE_ADDR + PORT_DIR_OFFSET)

/* Set ports for input */
#define DIOIN_PORT (0b1111111)

/* Constant used for the mman library */
#define BYTE (1)

typedef unsigned char uint8_t;


class Measurer {
public:
	Measurer();


	void initalize();
	int readPortA();
	int getData();
	void convert();

	virtual ~Measurer();

private:
	uintptr_t lsbPtr;
	uintptr_t msbPtr;
	uintptr_t adChannelPtr;
	uintptr_t inputPtr;
	uintptr_t porta;
};

#endif /* MEASURER_H_ */
