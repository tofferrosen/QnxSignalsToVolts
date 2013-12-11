/*
 * QNXSignalsToVolts.cc
 * Embedded and Real Time Systems: Project 6
 *
 * Implements a stand-alone system to provide a rough inidcation
 * of voltage from a waveform created by a signal generator using
 * servo motors. QNX implementation
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

/* Define PORTA address */
#define PORTA_OFFSET (8)
#define PORTA_ADDR (BASE_ADDR + PORTA_OFFSET)

int main(int argc, char *argv[]) {

	float voltage;
	signed char byteRep;
	uintptr_t porta;
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
		port_dir = mmap_device_io( BYTE, PORT_DIR_ADDR );

		// sets the direction of port to output.
		out8( port_dir, DIO_OUT_PORT);

		/* Initialize the converter */
		Converter * converter = new Converter();
		converter->initalize();

		/* Start program */
		while(true){
			converter->convert();
			voltage = converter->getVoltage();
			std::cout << "Voltage: " << voltage << "\n";
			byteRep = converter->getByteRepresentation(voltage);
			std::cout << "Byte Rep: " << byteRep << "\n";
			out8( porta, byteRep);
		}
		return EXIT_SUCCESS;
	}
}
