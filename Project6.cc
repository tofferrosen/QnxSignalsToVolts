#include <cstdlib>
#include <iostream>
#include <Converter.h>


/*
 * Project 6
 * Receives input from the QNX Digital I/O board from a signal generator.
 * Converts the input into voltage, converts this value to corresponding servo motor
 * position and sends it to Freescale.
 *
 * The main loop will consistently check the input pin, send the input to the converter class, and wait
 * for the voltage result. It will then convert this value to a servos motor positon and send it to freescale.
 *
 * @author Christoffer Rosen
 * @author Lennard Streat
 */

/* Port Direction Register */
#define PORT_DIR_OFFSET (11)
#define PORT_DIR_ADDR (BASE_ADDR + PORT_DIR_OFFSET)

/* Set port for input */
#define DIOIN_PORT (0b1111111) // all input

/* Define PORTA address */
#define PORTA_OFFSET (8)
#define PORTA_ADDR (BASE_ADDR + PORTA_OFFSET)

#define A0BIT (0b11111110) // A mask used to access the 0 bit of Port A

int main(int argc, char *argv[]) {

	/* Error Handling */
	int privity_err;
	int return_code = EXIT_SUCCESS;

	/* Enable GPIO access to the current thread: */
	privity_err = ThreadCtl(_NTO_TCTL_IO, NULL );
	if (privity_err == -1) {
		std::cout << "Error: Unable to acquire root permission for GPIO.\n";
		return_code = EXIT_FAILURE;
	} else {

		/* Initalize the converter */
		Converter * converter = new Converter();
		converter->initalize();

		while(true){
			converter->convert();
			std::cout << "Reading.. " << converter->getVoltage() << "\n";
		}



		return EXIT_SUCCESS;
	}
}
