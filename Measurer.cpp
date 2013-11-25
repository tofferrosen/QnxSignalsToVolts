/*
 * Measurer.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: cbr4830
 */

#include "Measurer.h"

Measurer::Measurer() {

}

/**
 * Read the data from the board after the
 * A/D conversion
 */
int Measurer::getData(){

	int lsbData = in8(BASE_ADDR + LSB_OFFSET); // 8 Bytes
	int msbData = in8(BASE_ADDR + MSB_OFFSET); // 8 Bytes

	return (msbData * 256 + lsbData); // convert to 16 Bytes
}

/**
 * Perorms an A/D conversion
 * TODO: Have a timeout in case hardware fault causes bit 1 to be stuck
 */
void Measurer::convert() {

	// Allow time for the analog input circuit to settle
	while (( in8( inputPtr ) & WAIT_BIT)!= 0 ){

	}

	// Perform the A/D conversion
	out8( lsbPtr, 0x80);

	while( in8( inputPtr ) & 0x80); // wait for conversion to finish

}
/**
 * Set up the A/D pointers and the A/D input range
 */
void Measurer::initalize(){
	lsbPtr = mmap_device_io( 0x01, BASE_ADDR + LSB_OFFSET );
	msbPtr = mmap_device_io( 0x01, BASE_ADDR + MSB_OFFSET );
	adChannelPtr = mmap_device_io ( 0x01, BASE_ADDR + AD_REGISTER_OFFSET);

	/* Set the board to use channel 4 only */
	out8( adChannelPtr, AD_CHANEL);

	inputPtr = mmap_device_io ( 0x01, INPUT_RANGE_REGISTER);
	out8( inputPtr, VOLTAGE_RANGE );
}

Measurer::~Measurer() {
	// TODO Auto-generated destructor stub
}
