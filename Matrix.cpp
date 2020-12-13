/*
 * MATRIX IMPLEMENTATION FILE
 * 
 * This file holds all of the functions that each matrix needs.
 */
#include "Matrix.h"
#include <cstddef>
#include <iostream>
#include <cmath> 

using namespace std;


/*
 * Matrix Constructor 
 * 
 * Basic constructor for the matrix object. Sets the 
 * matrix to be nonexistent and sets both values of rows
 * and columns to 0.
 * 
 * PARAMS
 * 
 * 	none
 */

Matrix::Matrix() {
	matrix = NULL;
	rows = 0;
	cols = 0;

}

/*
 * Matrix Constructor 
 * 
 * Constructor that instantiates the matrix off the bat.
 * Needs a row and column input.
 * 
 * PARAMS
 * 
 * 	n - Rows of the matrix
 * 	m - Columns of the matrix
 */

Matrix::Matrix(int n, int m) {
	matrix = NULL;
	rows = n;
	cols = m;

	matrix = new float* [rows]; 
	for (int i = 0; i < rows; ++i)
		matrix[i] = new float[cols];

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = 0;

}

/*
 * Operator Overload - Addition
 * 
 * Allows for the current matrix object to be added to another and return
 * the new matrix.
 * 
 * PARAMS
 * 
 * 	m - The matrix object to be added to this matrix object.
 */

Matrix Matrix::operator+(Matrix m) {
	Matrix n(rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			n.matrix[i][j] = this->matrix[i][j] + m.matrix[i][j];

	return n;
	
}


/*
 * Operator Overload - Subtraction
 * 
 * Allows for the current matrix object to be subtracted by another and return
 * the new matrix.
 * 
 * PARAMS
 * 
 * 	m - The matrix object to subtract from this matrix object.
 */

Matrix Matrix::operator-(Matrix m) {
	Matrix n(rows, cols);

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			n.matrix[i][j] = this->matrix[i][j] - m.matrix[i][j];

	return n;
	
	
}

/*
 * Operator Overload - Multiplication
 * 
 * Allows for the current matrix object to be multiplied by another and return
 * the new matrix.
 * 
 * PARAMS
 * 
 * 	m - The matrix object to be multiplied to this matrix object.
 */

Matrix Matrix::operator*(Matrix m) {
	//Take current matrix rows and the other matrix's columns to get the new size
	Matrix n(rows, m.cols);
	float b;

	for (int i = 0; i < n.get_rows(); i++)
		for (int j = 0; j < n.get_cols(); j++)
			for (int k = 0; k < cols; k++) {
				// multiply rows and columns
				b = this->matrix[i][k] * m.get_matrix()[k][j];
				// the result is the value in that placeholder
				n.add_matrix(i, j, b);
			}

	return n;
	
}

/*
 * Establish 
 * 
 * Takes in inputs for the new matrix to be created. Goes to instantiate
 * that matrix and sends it to the fill_matrix function to have values inputted.
 * 
 * PARAMS
 * 
 * 	none
 */

void Matrix::establish() {
	cout << "Rows: ";
	cin >> rows;
	cout << "Columns: ";
	cin >> cols;

	matrix = new float* [rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new float[cols];

	fill_matrix();
}


/*
 * Fill Matrix
 * 
 * Takes user inputs to fill each value in the new matrix.
 * 
 * PARAMS
 * 
 * 	none
 */
void Matrix::fill_matrix() {
	float t;

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = 0;

	for (int i = 0; i < rows; i++) 
		for (int j = 0; j < cols; j++) {
			cout << endl << "Enter value for row " << i << " and column " << j << endl;
			cin >> t;
			matrix[i][j] = t;
			print_matrix();
		}

}

/*
 * Print Matrix
 * 
 * Simply outputs each value in the matrix in correct form.
 * 
 * PARAMS
 * 
 * 	none
 */

void Matrix::print_matrix() {
	
	for (int i = 0; i < rows; i++) {
		cout << endl;
		for (int j = 0; j < cols; j++)
			cout << matrix[i][j] << " ";

	}
}

/*
 * Getter function for the matrix array
 * 
 */

float** Matrix::get_matrix()
{
	return matrix;
}

/*
 * Getter function for the rows amount
 * 
 */

int Matrix::get_rows()
{
	return rows;
}

/*
 * Getter function for the column amount
 * 
 */

int Matrix::get_cols()
{
	return cols;
}

/*
 * Add Matrix
 * 
 * Adds a value to a index in the matrix
 * 
 * PARAMS
 * 
 *  i - Row location
 *  j - Column location
 *  b - Value to add
 */

void Matrix::add_matrix(int i, int j, float b)
{
	matrix[i][j] += b;

}

/*
 * Row Reduce
 * 
 * This function reduces the matrix to a upper triangular form.
 * This allows us to easily take the determinant of the matrix
 * as well as gather more information.
 * 
 * 
 * PARAMS
 * 
 * 	none
 */

void Matrix::row_reduce() {

	int p = rows;  //rows
	int q = cols;  //columns
	double hold = 0;

	int lead = 0; //"lead" determines the column we are at that
	int curr = 0;	  // holds the diagonal "pivot". This helps us to zero out all numbers 
					  //above and below the pivot.

	cout << endl;
	
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++)
		{
			if (j == lead){
				for(int k = i; k < p; k++){
					if((k + 1 < p) && (matrix[i][lead] != 0)){
						hold = matrix[k + 1][lead] / matrix[i][lead];
						for(int m = lead; m < q; m++)
							matrix[k + 1][m] = (matrix[k+1][m] - (matrix[i][m] * hold));
					 }
				}
			}
		}
		lead++;  // Now go to the next column pivot
	}
		cout << endl;
		determinant();
}


/*
 * Determinant
 * 
 * Yields the determinant of the matrix by simplying
 * multiplying across the diagonal of a reduced matrix.
 * 
 * PARAMS
 * 
 * 	none
 */
float Matrix::determinant(){

	int p = rows;  //rows
	int q = cols;  //columns
	double hold = 0;

	int lead = 0; //"lead" determines the column we are at that
	float det = 1;			   // holds the diagonal "pivot". This helps us to zero out all numbers 
					  //above and below the pivot.

	cout << endl;
	if( p != q)
		return -1;

	for(int i = 0; i < p; i++){
		det = det * matrix[i][lead];
		cout << det << endl;
		lead++;
	}

	cout << endl << endl << "DETERMINANT: " << det << endl << endl;

}


/*
 * Clear Memory
 * 
 * Clears the memory of the matrix
 * 
 * PARAMS
 * 
 * 	none
 */

void Matrix::clear_mem() {

	for (int i = 0; i < rows; i++)
		delete[] matrix[i];

	delete[] matrix;

}
