/*
 * Converter
 * Represents the A/D Converter.
 *
 * @author Christoffer Rosen
 * @author Lennard Streat
 */

#include <stdint.h>						/* Resource for uintptr_t */
#include <sys/mman.h>					/* Resource for mmap_device_io */
#include <hw/inout.h>					/* Resource for in and out fns */
#include <sys/neutrino.h>       	 	/* Resource(s): ThreadCtl() */
#include <cstdlib>
#include <iostream>

#ifndef CONVERTER_H_
#define CONVERTER_H_

#define BASE_ADDR ( 0x280 )						/* Base address to A/D converter */
#define LSB_OFFSET ( 0 )						/* The least significant byte of data */
#define MSB_OFFSET ( 1 )						/* The most significant byte of data */
#define AD_REGISTER_OFFSET ( 2 )				/* AD CHANEL OFFSET */
#define AD_GAIN_SCAN_OFFSET ( 3 )				/* Analog input status offset */
#define AD_CHANEL ( 0x44 ) 						/* AD Chanel */
#define INPUT_RANGE_REGISTER ( BASE_ADDR + 3)	/* Input range register */
#define VOLTAGE_RANGE (0x01)					/* Range of input voltage +-5V (gain of 2) */
#define WAIT_BIT (0b00100000)					/* The WAIT bit for analog input circuit */
#define FULL_SCALE_INPUT_RANGE (5)

/* For converting voltage float to byte value */
#define SIGNED_MINUS_MAX (128)
#define SIGNED_POSITIVE_MAX (127)

/* Constant used for the mman library */
#define BYTE (1)

class Converter {
public:

	// constructor
	Converter();

	/**
	 * Set up the A/D pointers and the A/D input range
	 * IMPORTANT: Assumes and requires that GPIO has access to
	 * the current thread
	 */
	void initalize();
	/**
	 *	Performs the A/D conversion
	 */
	void convert();
	/**
	 * Returns the input voltage.
	 * Formula: input voltage = A/D value  * full-scale input range / 32768
	 * @return float		The voltage from the A/D value from the board
	 */
	float getVoltage();

	/**
	 * Returns byte representation of a float voltage value to be used
	 * by the freescale implementation.
	 * @param 		A float voltage value ranging between -5 to 5.
	 * @return		Returns a signed character byte representation of the voltage value
	 */
	signed char getByteRepresentation(float);

	// deconstructor
	virtual ~Converter();

private:
	/**
	 * The data from the board after the A/D conversion
	 * @return 			The A/D code between -32768 to 32767 from board
	 * @private
	 */
	int getData();

	uintptr_t _lsbPtr;	/* Memory mapped I/O to the A/D least significant byte of data */
	uintptr_t _msbPtr;	/* Memory mapped I/O to the A/D most significant byte of data */
	uintptr_t _adChannelPtr; /* Memory mapped I/O to the A/D channel */
	uintptr_t _inputPtr; /* Memory mapped I/O to the input */
};

#endif /* Converter_H_ */
