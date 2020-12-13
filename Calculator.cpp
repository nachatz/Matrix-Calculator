#include "Calculator.h"
#include <iostream>
#include <string>

using namespace std;


/*
 * Run
 * 
 * Runs the calculator object. Allows for the user to
 * test one or two matrices.
 * 
 * PARAMS
 * 
 * 	none
 */

void Calculator::run() {

	int t;
	do {
		while (1) {
			display("Are we working with one or two Matrices?");
			cin >> t;
			if (t == 1 || t == 2) {
				gather_data(t);
				break;
			}
			else {
				display("- - - - invalid entry - - - -");
				continue;
			}
		}
		display("Press 1 to calculate more matrices");

		cin >> t;
	} while (t == 1);

}

/*
 * Gather Data
 * 
 * Creates an array of 1 or 2 matrices and then instantiates them
 * by establishing them through the object itself. The functionality of this can
 * be seen in the establish function in the matrix.cpp file. Further, once they are established
 * the user can decided how to work with the two matrices or if only one is picked, the one will be reduced
 * and printed.
 * 
 * PARAMS
 * 
 * 	matrixCount - How many matrices should be created
 */

void Calculator::gather_data(int matrixCount) {

	// how many matrices
	m = new Matrix[matrixCount];

	// establishes each matrix
	for (int i = 0; i < matrixCount; i++) {
		cout << endl << endl << "-------------------------------------------------------------------------" << endl;
		cout << "Enter data for Matrix " << i << endl;
		cout << "-------------------------------------------------------------------------" << endl;
		m[i].establish();
	}

	// If matrix count is one, reduce and print, if two then send to arithmetic.
	switch (matrixCount) {
	case 1:
		m->row_reduce();
		m->print_matrix();
		break;
	case 2:
		arithmetic(m);
	}

	// clear all memory
	for (int i = 0; i < matrixCount; i++)
		m[i].clear_mem();

	delete [] m;

}


/*
 * Arithmetic
 * 
 * This function allows the user to multiply, subtract, or add the two matrices. This does not
 * hold the functionality of these, but rather decides which one should be done. The functionality of
 * these is within the matrix.cpp file.
 * 
 * PARAMS
 * 
 * 	m - array of matrices
 */

void Calculator::arithmetic(Matrix* m) {
	int t;
	do {
		// Displays the two matrices being worked with
		display("Matrix 1");
		m[0].print_matrix();
		display("Matrix 2");
		m[1].print_matrix();

		


		cout << endl << endl << "-------------------------------------------------------------------------" << endl;
		cout << "Do you want to add (1), substract (2), or multiply (3) the two matrices?" << endl;
		cout << "Enter 0 to exit to menu" << endl;
		cout << "-------------------------------------------------------------------------" << endl;

		cin >> t;
		process_arithmetic(t);

	} while (t != 0);

}


/*
 * Display
 * 
 * Creates a message that is easily readable to the user.
 * 
 * PARAMS
 * 
 * 	t - the message to be displayed.
 */
void Calculator::display(string t)
{
	cout << endl << "-------------------------------------------------------------------------" << endl;
	cout << endl << t << endl << endl;
	cout << "-------------------------------------------------------------------------" << endl;

}

/*
 * Process Arithmetic
 * 
 * Runs the operations, but the functionality is still within matrix.cpp. The operators are
 * overloaded in the matrix object class which allows us to use simple arithmetic operations here.
 * 
 * Checks to make sure the matrices can be added, subtracted, or multiplied. If they can, it will run the operation.
 * 
 * PARAMS
 * 
 * 	t - the input read in from the user.
 */

void Calculator::process_arithmetic(int t)
{
	Matrix n;

	switch (t) {
		case 1:
			if ((m[0].get_rows() != m[1].get_rows()) || (m[0].get_cols() != m[1].get_cols())) {
				display("These matrices cannot be added!");
				break;
			}
			n = m[0] + m[1];
			display("Added matrices result");
			break;
		case 2:
			if ((m[0].get_rows() != m[1].get_rows()) || (m[0].get_cols() != m[1].get_cols())) {
				display("These matrices cannot be subtracted!");
				break;
			}
			n = m[0] - m[1];
			display("Subtracted matrices result");
			break;
		case 3:
			if ((m[0].get_cols() != m[1].get_rows())) {
				display("These matrices cannot be multiplied!");
				break;
			}
			n = m[0] * m[1];
			display("Multiplied matrices result");
			break;
	}

	n.print_matrix();
	n.clear_mem();

}
