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

int main(int argc, char *argv[]) {

	/* Error Handling */
	int privity_err;
	int return_code = EXIT_SUCCESS;
	float voltage;
	signed char byteRep;

	/* Enable GPIO access to the current thread: */
	privity_err = ThreadCtl(_NTO_TCTL_IO, NULL );
	if (privity_err == -1) {
		std::cout << "Error: Unable to acquire root permission for GPIO.\n";
		return_code = EXIT_FAILURE;
	} else {

		/* Initalize the converter */
		Converter * converter = new Converter();
		converter->initalize();

		/* Start program */
		while(true){
			converter->convert();
			voltage = converter->getVoltage();
			std::cout << "Voltage: " << voltage << "\n";
			byteRep = converter->getByteRepresentation(voltage);
			std::cout << "Byte Rep: " << (int)byteRep << "\n";
		}
		return EXIT_SUCCESS;
	}
}
