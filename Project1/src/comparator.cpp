#include "comparator.hpp"

template <typename T> bool Comparator<T>::leq(T lhs, T rhs)
{
	compare_count++;
	return (lhs <= rhs);
}
template <typename T> bool Comparator<T>::geq(T lhs, T rhs)
{
	compare_count++;
	return (lhs >= rhs);
}

template class Comparator<int>;