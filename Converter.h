/**
 * Comments TBD
 *
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
#define FULL_SCALE_INPUT_RANGE (10)
/* Constant used for the mman library */
#define BYTE (1)

typedef unsigned char uint8_t;


class Converter {
public:
	Converter();

	void initalize();
	void convert();
	float getVoltage();

	virtual ~Converter();

private:
	int getData();
	uintptr_t _lsbPtr;
	uintptr_t _msbPtr;
	uintptr_t _adChannelPtr;
	uintptr_t _inputPtr;
};

#endif /* Converter_H_ */
