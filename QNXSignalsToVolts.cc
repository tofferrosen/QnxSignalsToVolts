/*
 * QNXSignalsToVolts.cc
 * Embedded and Real Time Systems: Project 6
 *
 * Implements a stand-alone system to provide a rough inidcation
 * of voltage from a waveform created by a signal generator using
 * servo motors. QNX implementation
 *
 *
 * 
 * Uses PORTA to output voltage (byte)
 * Uses PORTB to output error conditions. 
 * 
 * @author Christoffer Rosen
 * @author Lennard Streat
 */

#include <cstdlib>
#include <iostream>
#include <Converter.h>

/* Port Direction Register */
#define PORT_DIR_OFFSET (11)
#define PORT_DIR_ADDR (BASE_ADDR + PORT_DIR_OFFSET)

/* Set port for output */
#define DIO_OUT_PORT (0b00000000) // all output

/* Define PORTA address for output */
#define PORTA_OFFSET (8)
#define PORTA_ADDR (BASE_ADDR + PORTA_OFFSET)

/* Define PORTB address for error conditions */
#define PORTB_OFFSET (9)
#define PORTB_ADDR (BASE_ADDR + PORTB_OFFSET)

#define MIN_VOLTAGE_ALLOWED (-5)
#define MAX_VOLTAGE_ALLOWED (5)

int main(int argc, char *argv[]) {

	float voltage;
	signed char byteRep;
	uintptr_t porta;
	uintptr_t portb;
	uintptr_t port_dir;

	/* Error Handling */
	int privity_err;
	int return_code = EXIT_SUCCESS;

	/* Enable GPIO access to the current thread: */
	privity_err = ThreadCtl(_NTO_TCTL_IO, NULL );
	if (privity_err == -1) {
		std::cout << "Error: Unable to acquire root permission for GPIO.\n";
		return_code = EXIT_FAILURE;
	} else {
		porta =  mmap_device_io( BYTE, PORTA_ADDR );
		portb = mmap_device_io( BYTE, PORTB_ADDR );
		port_dir = mmap_device_io( BYTE, PORT_DIR_ADDR );

		// sets the direction of ports to output.
		out8( port_dir, DIO_OUT_PORT);

		/* Initialize the converter */
		Converter * converter = new Converter();
		converter->initalize();

		/* Start program */
		while(true){
			converter->convert();
			voltage = converter->getVoltage();
			
			// write the voltage as byte to port A on the digital I/O if the voltage is acceptable 
			if( voltage > MIN_VOLTAGE_ALLOWED && voltage < MAX_VOLTAGE_ALLOWED ){
				byteRep = converter->getByteRepresentation(voltage);
				out8( porta, byteRep);
				out8( portb, 0x0); // clear led error flag
			} else {
				out8( portb, 0xFF);  // signal error w/ led 
			}
		}
		return EXIT_SUCCESS;
	}
}
