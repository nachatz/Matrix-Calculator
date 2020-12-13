/*
 * MATRIX HEADER FILE
 * 
 * Member variables and functions for each matrix created. 
 */

#pragma once
class Matrix
{
private: 
	void fill_matrix();
	// Allows for a n x n matrix to be created
	float** matrix;
	int rows, cols;
public:
	Matrix();
	Matrix(int, int);
	Matrix operator+(Matrix);
	Matrix operator-(Matrix);
	Matrix operator*(Matrix);
	void establish();
	void print_matrix();
	void add_matrix(int, int, float);
	void row_reduce();
	void clear_mem();
	float determinant();
	float** get_matrix();
	int get_rows();
	int get_cols();
};

