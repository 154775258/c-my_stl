#pragma once
#include<iostream>
using namespace std;

class valtype {
public:
	~valtype(){}
};

template<typename T>
class hold : public valtype {
public:
	hold(const T t) {
		a = new T(t);
	}

	~hold() { delete a; }
private:
	T* a;
};

class my_any
{
public:
	my_any() { m_data = nullptr; }
	template <class T>
	my_any(T val) : m_data(new hold<T>(val)){}
	~my_any() { delete m_data; }

	template <typename T>
	my_any& operator = (T val) {
		delete m_data;
		m_data = new hold<T>(val);
		return *this;
	}

	valtype* data() {
		return m_data;
	}


private:
	valtype* m_data;
};

