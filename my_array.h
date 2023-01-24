#pragma once
#include <initializer_list>
using namespace std;

template <typename T,int Size>
class my_array
{
public:
	my_array();
	~my_array();
	int size();
	T& at(int index);
	T& back();
	void operator = (my_array<T, Size>& a);
	void operator = (initializer_list<T> a);
	void fill(T val);

private:
	T* m_data;
	int m_size = Size;
};

template <typename T, int Size>
my_array<T, Size>::my_array() {
	m_data = new T[m_size];
}

template<typename T,int Size>
my_array<T, Size>::~my_array() {
	delete[] m_data;
	m_size = 0;
}

template <typename T,int Size>
T& my_array<T, Size>::at(int index) {
	return m_data[index];
}

template <typename T, int Size>
int my_array<T, Size>::size() {
	return m_size;
}

template<int index,typename T,int N>
T& get(my_array<T,N>& val) {
	return val.at(index);
}

template<typename T, int N>
T& my_array<T, N>::back() {
	return m_data[m_size - 1];
}

template <typename T, int Size>
void my_array<T, Size>::operator = (my_array<T, Size>& a) {
	for (int i = 0; i < a.size(); i++) {
		m_data[i] = a.at(i);
	}
}

template <typename T, int Size>
void my_array<T, Size>::operator = (initializer_list<T> a){
	int i = 0;
	for (auto t : a) {
		if (i >= size())break;
		m_data[i++] = t;
	}
}

template <typename T,int Size>
void my_array<T, Size>::fill(T val) {
	for (int i = 0; i < size(); i++)
		at(i) = val;
}

template <typename T, int Size>
void swap(my_array<T, Size>& a, my_array<T, Size>& b) {
	my_array<T, Size> tmp;
	tmp = a;
	a = b;
	b = tmp;
}