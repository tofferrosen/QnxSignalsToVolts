#include <cstdlib>
#include <iostream>
#include <Measurer.h>

/*
 * Project 6
 * Measures the signa geneator voltage and sent to the
 * Freescale program.
 *
 * Christoffer Rosen
 */

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

	Measurer * measurer = new Measurer();
	measurer->initalize();

	while(true){
		cout << "Reading: " << measurer->readPortA() << "\n";
	}
	//measurer->convert();
	//int data = measurer->getData();

	return EXIT_SUCCESS;
}
