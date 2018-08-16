#include <iostream>

#include "includes.hpp"
#include "comparator.hpp"
#include "matrix.hpp"

int main(int argc, char ** argv) 
{	

	Comparator<int> comp;
	std::string path("input.txt");
	Matrix matrix;

	matrix.read_from_file(path);
	matrix.sort_method1();
	Comparator<int>::resetCount();

	matrix.read_from_file(path);
	matrix.sort_method2();
	Comparator<int>::resetCount();

	return 0;
}