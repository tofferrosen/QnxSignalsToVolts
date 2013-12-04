/*
 * Measurer.cpp
 *
 *  Created on: Nov 20, 2013
 *      Author: cbr4830
 */

#include "Converter.h"

Converter::Converter() {

}

/**
 * Read the data from the board after the
 * A/D conversion
 * @private
 */
int Converter::getData(){
	char lsbData = in8(_lsbPtr); // 8 Bytes
	char msbData = in8(_msbPtr); // 8 Bytes
	return ( ( msbData << 8 ) + lsbData ); // convert to 16 Bytes
}

/**
 * Perorms an A/D conversion
 * TODO: Have a timeout in case hardware fault causes bit 1 to be stuck
 */
void Converter::convert() {

	while (( in8( _inputPtr ) & WAIT_BIT)!= 0 ){} // Allow time for the analog input circuit to settle
	out8( _lsbPtr, 0x80); // Perform the A/D conversion
	while( in8( _inputPtr ) & 0x80); // wait for conversion to finish
}

/**
 * Returns the input voltage
 * input voltage = A/D value  * full-scale input range / 32768
 */
float Converter::getVoltage(){
	int data = getData();
	float voltage = ((float)(data) * (float)(FULL_SCALE_INPUT_RANGE) ) / (float)32768;
	return voltage;
}

/**
 * function: initalize()
 * description: Set up the A/D pointers and the A/D input range
 * 	IMPORTANT: Assumes and requires that GPIO has access to the current
 * 	thread
 */
void Converter::initalize(){
	_lsbPtr = mmap_device_io( BYTE, BASE_ADDR + LSB_OFFSET );
	_msbPtr = mmap_device_io( BYTE, BASE_ADDR + MSB_OFFSET );
	_adChannelPtr = mmap_device_io ( BYTE, BASE_ADDR + AD_REGISTER_OFFSET);

	/* Set the board to use channel 4 only */
	out8( _adChannelPtr, AD_CHANEL);

	_inputPtr = mmap_device_io ( BYTE, INPUT_RANGE_REGISTER);
	out8( _inputPtr, VOLTAGE_RANGE );
}

Converter::~Converter() {
	// TODO Auto-generated destructor stub
}
