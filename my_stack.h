#include <initializer_list>

template <typename T>
class my_stack {

public:
	my_stack();
	~my_stack();
	void push(T val);
	void pop();
	T& top();
	int size();
	bool empty();
	bool operator != (my_stack<T>& a);
	bool operator == (my_stack<T>& a);
	bool operator < (my_stack<T>& a);
	bool operator <= (my_stack<T>& a);
	bool operator > (my_stack<T>& a);
	bool operator >=(my_stack<T>& a);
	T operator [](int index);

private:
	T* m_data;
	int m_top;
	int m_capacity;
};

template <typename T>
my_stack<T>::my_stack() {
	m_top = 0;
	m_capacity = 0;
	m_data = nullptr;
}

template <typename T>
my_stack<T>::~my_stack() {
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_top = 0;
	m_capacity = 0;
}

template <typename T>
void my_stack<T>::push(T val) {
	if (m_top < m_capacity) {
		m_data[m_top] = val;
		m_top++;
		return;
	}
	if (m_capacity == 0)
		m_capacity = 1;
	else m_capacity *= 2;
	T* Ndata = new T[m_capacity];
	for (int i = 0; i < m_top; i++) {
		Ndata[i] = m_data[i];
	}
	if (m_data != nullptr) {
		delete[] m_data;
		m_data = nullptr;
	}
	m_data = Ndata;
	m_data[m_top++] = val;
	return;
}

template <typename T>
void my_stack<T>:: pop() {
	m_top--;
}

template <typename T>
T& my_stack<T>::top() {
	return m_data[m_top - 1];
}

template <typename T>
int my_stack<T>::size() {
	return m_top;
}

template <typename T>
bool my_stack<T>::empty() {
	return m_top == 0;
}

template<typename T>
bool my_stack<T>::operator !=(my_stack<T>& a) {
	if (a.size() != size())return 1;
	for (int i = 0; i < m_top; i++) {
		if (a[i] != m_data[i])return 1;
	}
	return 0;
}

template <typename T>
bool my_stack<T>::operator ==(my_stack<T>& a) {
	if (a.size() == size())return 0;
	for (int i = 0; i < m_top; i++) {
		if (a[i] != m_data[i])return 0;
	}
	return 1;
}

template <typename T>
T my_stack<T>::operator [](int index) {
	return m_data[index];
}

template <typename T>
bool my_stack<T>::operator < (my_stack<T>& a) {
	if (a.size() < size())return 0;
	else if(a.size() > size()) return 1;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	if (top() == a.top())return 0;
	return 1;
}

template <typename T>
bool my_stack<T>::operator <= (my_stack<T>& a) {
	if (a.size() < size())return 0;
	else if(a.size() > size()) return 1;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	return 1;
}

template <typename T>
bool my_stack<T>::operator > (my_stack<T>& a) {
	if (a.size() < size())return 1;
	else if(a.size() > size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	if (a.top() == top())return 0;
	return 1;
}

template <typename T>
bool my_stack<T>::operator >= (my_stack<T>& a) {
	if (a.size() < size())return 1;
	else if(a.size() > size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	return 1;
}