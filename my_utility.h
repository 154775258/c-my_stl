#pragma once
#include <initializer_list>
template <class T1,class T2>
struct my_pair {
	T1 first;
	T2 second;
	my_pair() {};
	my_pair(T1 a,T2 b) {
		first = a;
		second = b;
	}
	~my_pair() {}
};

