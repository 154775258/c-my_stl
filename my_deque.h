#pragma once
#include <initializer_list>
//和标准库实现方式不一样 标准库采用的是链式数组进行快速添加头尾数据。
template<typename T>
class my_deque
{
public:
	my_deque();
	my_deque(const int size);
	~my_deque();
	int size() const;
	bool empty()const;
	void push_front(T val);//往屁股放数据
	void push_rear(T val);//往头放数据
	T& operator [](int index);
	my_deque<T>& operator = (my_deque<T>& a);
	int capacity();
	void pop_front();
	void pop_rear();
	void clear();
	T& front();//获取尾部元素
	T& rear();//获取头部元素
private:
	T* m_data;
	int m_front = -1;//头指针
	int m_rear = 0;//尾指针
	int m_capacity = 0;//空间容量
};

template <typename T>
my_deque<T>::my_deque() {
	m_front = 4;
	m_rear = 5;
	m_capacity = 12;
	delete[]m_data;
	m_data = nullptr;
	m_data = new T[m_capacity];
}

template <typename T>
my_deque<T>::my_deque(const int size) {
	m_front = size / 3;
	m_rear = size / 3 + 1;
	m_capacity = size;
	delete[]m_data;
	m_data = nullptr;
	m_data = new T[m_capacity];
}

template <typename T>
my_deque<T>::~my_deque() {
	m_front = -1;
	m_rear = 0;
	m_capacity = 0;
	delete[]m_data;
	m_data = nullptr;
}

template <typename T>
int my_deque<T>::size()const {
	return m_front - m_rear + 1;
}

template <typename T>
bool my_deque<T>::empty() const {
	return m_rear > m_front;
}

template <typename T>
void my_deque<T>::push_front(T val) {
	if (m_front == m_capacity - 1) {
		m_capacity *= 2;
		T* tmp = new T[m_capacity];
		int a = m_capacity / 3;
		int b = m_capacity / 3 + 1;
		int len = size();
		while (len--) {
			tmp[++a] = m_data[m_rear++];
		}
		tmp[++a] = val;
		delete[]m_data;
		m_data = tmp;
		m_rear = b;
		m_front = a;
	}
	else m_data[++m_front] = val;
}

template <typename T>
void my_deque<T>::push_rear(T val) {
	if (m_rear == 0) {
		m_capacity *= 2;
		T* tmp = new T[m_capacity];
		int a = m_capacity / 3;
		int b = m_capacity / 3 + 1;
		int len = size();
		while (len--) {
			tmp[++a] = m_data[m_rear++];
		}
		tmp[--b] = val;
		delete[]m_data;
		m_data = tmp;
		m_rear = b;
		m_front = a;
	}
	else m_data[--m_rear] = val;
}

template <typename T>
T& my_deque<T>::operator[](int index) {
	return m_data[m_rear + index];
}

template <typename T>
my_deque<T>& my_deque<T>::operator =(my_deque<T>& a) {
	delete[]m_data;
	m_data = new T[a.capacity()];
	m_rear = a.m_rear;
	m_front = a.m_front;
	for (int i = m_rear; i <= m_front; i++) {
		m_data[i] = a[i - m_rear];
	}
	return*this;
}

template <typename T>
void my_deque<T>::pop_front() {
	m_front--;
}

template <typename T>
void my_deque<T>::pop_rear() {
	++m_rear;
}

template <typename T>
int my_deque<T>::capacity() {
	return m_capacity;
}

template <typename T>
void my_deque<T>::clear() {
	m_rear = m_capacity / 3 + 1;
	m_front = m_capacity / 3;
}

template <typename T>
T& my_deque<T>::front() {
	return m_data[m_front];
}

template <typename T>
T& my_deque<T>::rear() {
	return m_data[m_rear];
}

template <typename T>
void swap(my_deque<T>& a, my_deque<T>& b) {
	my_deque<T> t;
	t = a;
	a = b;
	b = t;
}