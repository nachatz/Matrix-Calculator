/*
 * CALCULATOR HEADER FILE
 * 
 * Contains member variables and functions for controlling what is being calculated.
 */
#pragma once
#include "Matrix.h"
#include <string>

using namespace std;

class Calculator
{
private:
	// Holds 1 or 2 matrices to be added or reduced.
	Matrix* m;
	void gather_data(int);
	void arithmetic(Matrix*);
	void display(string);
	void process_arithmetic(int);
public:
	void run();
};

