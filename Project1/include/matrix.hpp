#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "includes.hpp"
#include "comparator.hpp"

using matrix_data = std::vector<int>;

// This class is kind of silly and non-functional in a larger project. 
// If we use this again, I'll seperate it into a generic quicksort class
// and a matrix class. This should work, though, albeit in an ugly way.
class Matrix 
{
private:
	Comparator<int> comp;
	int rows;
	int cols;
	int i_iter;
	int j_iter;
	matrix_data data;
	bool (Matrix::*first)(matrix_data* d, int left);
	bool (Matrix::*second)(matrix_data* d, int left);

	void quicksort(matrix_data* d, int left, int right);
	int quicksort_partition(matrix_data* d, int left, int right);
	bool quicksort_partition_icomp(matrix_data* d, int left);
	bool quicksort_partition_jcomp(matrix_data* d, int left);
public:
	Matrix(); 
	void read_from_file(std::string path);
	void sort_method1();
	void sort_method2();
	void output_to_file(std::string path);
	void print_matrix();
};