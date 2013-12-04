/*
 * Converter
 * Represents the A/D Converter.
 *
 * @author Christoffer Rosen
 * @author Lennard Streat
 */

#include "Converter.h"

Converter::Converter() {

}

/**
 * getData()
 * @descr 		Read the data from the board after the
 * 		  		A/D conversion
 * @return 		A/D code between -32768 to 32767 from board
 * @private
 */
int Converter::getData(){
	char lsbData = in8(_lsbPtr); // 8 Bytes
	char msbData = in8(_msbPtr); // 8 Bytes
	return ( ( msbData << 8 ) + lsbData ); // convert to 16 Bytes
}

/**
 * convert()
 * @descr		Performs the A/D conversion
 */
void Converter::convert() {

	while (( in8( _inputPtr ) & WAIT_BIT)!= 0 ){} // Allow time for the analog input circuit to settle
	out8( _lsbPtr, 0x80); // Perform the A/D conversion
	while( in8( _inputPtr ) & 0x80); // wait for conversion to finish
}

/**
 * getVoltage()
 * @descr 			returns the input voltage.
 * 					Formula = input voltage = A/D value  * full-scale input range / 32768
 * @return float	The voltage from the A/D value from the board
 */
float Converter::getVoltage(){
	int data = getData();
	float voltage = ((float)(data) * (float)(FULL_SCALE_INPUT_RANGE) ) / (float)32768;
	return voltage;
}

/**
 * initalize()
 * @descr			Set up the A/D pointers and the A/D input range
 * 					IMPORTANT: Assumes and requires that GPIO has access to
 * 					the current thread
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

// destructor
Converter::~Converter() {
	// TODO Auto-generated destructor stub
}
