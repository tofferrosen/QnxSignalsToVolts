#include <cstdlib>
#include <iostream>
#include <Measurer.h>


/*
 * Project 6
 * Measures the signa geneator voltage and sent to the
 * Freescale program.
 *
 * Christoffer Rosen
 * Lennard Streat
 */

int main(int argc, char *argv[]) {
	std::cout << "Welcome to the QNX Momentics IDE" << std::endl;

	Measurer measurer = new Measurer();

	return EXIT_SUCCESS;
}
