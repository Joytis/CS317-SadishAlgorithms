#pragma once 

#include "includes.hpp"

template<typename T>
class Comparator 
{
private:
	static int compare_count;

public:
	bool leq(T lhs, T rhs);
	bool geq(T lhs, T rhs);
	static int getCount() { return compare_count; }
	static void resetCount() { compare_count = 0; }
};

template<typename T> int Comparator<T>::compare_count = 0;
