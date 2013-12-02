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
 * Reads data from the digital I/O board port A
 */
int Measurer::readPortA(){
	return in8(porta);
}

/**
 * Writes data to the channel register
 */
void Measurer::writeRegister(int data){
	std::cout << "writing data: " << data << "\n";
	out8(adChannelPtr, data);

	std::cout << "starting conversion" << "\n";
	convert();

	std::cout << "voltage: " << getData() << "\n";
}
/**
 * Set up the A/D pointers and the A/D input range
 */
void Measurer::initalize(){
	uintptr_t port_dir;
	int privity_err;
	int return_code = EXIT_SUCCESS;

	/* Enable GPIO access to the current thread: */
	privity_err = ThreadCtl(_NTO_TCTL_IO, NULL );
	if (privity_err == -1) {
		std::cout << "Error: Unable to acquire root permission for GPIO.\n";
		return_code = EXIT_FAILURE;
	} else {
		lsbPtr = mmap_device_io( BYTE, BASE_ADDR + LSB_OFFSET );
		msbPtr = mmap_device_io( BYTE, BASE_ADDR + MSB_OFFSET );
		adChannelPtr = mmap_device_io ( BYTE, BASE_ADDR + AD_REGISTER_OFFSET);
		porta = mmap_device_io(BYTE, PORTA_ADDR);
		port_dir = mmap_device_io(BYTE, PORT_DIR_ADDR);

		/* Initalize ports for input (specifically for porta!) */
		out8(port_dir, DIOIN_PORT);

		/* Set the board to use channel 4 only */
		out8( adChannelPtr, AD_CHANEL);

		inputPtr = mmap_device_io ( BYTE, INPUT_RANGE_REGISTER);
		out8( inputPtr, VOLTAGE_RANGE );
	}
}

Measurer::~Measurer() {
	// TODO Auto-generated destructor stub
}
