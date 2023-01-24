#include<stdexcept>
#include<vector>
using namespace std;

template <typename T>
class my_queue {

public:
	my_queue();
	~my_queue();
	void push(T val);
	T& rear();
	T& front();
	void pop();
	bool empty();
	bool operator != (my_queue<T>& a);
	bool operator == (my_queue<T>& a);
	bool operator < (my_queue<T>& a);
	bool operator <= (my_queue<T>& a);
	bool operator > (my_queue<T>& a);
	bool operator >=(my_queue<T>& a);
	my_queue<T>& operator = (my_queue<T>& a);
	T operator [](int index);
	int size();
	int rearIndex();

private:
	int m_front;
	int m_rear;
	T* m_data;
	int m_capacity;

};

template <typename T>
my_queue<T>::my_queue() {
	m_data = nullptr;
	m_capacity = 0, m_rear = 0, m_front = -1;
}

template <typename T>
my_queue<T>::~my_queue() {
	delete[] m_data;
	m_capacity = 0, m_rear = 0, m_front = -1;
}

template <typename T>
void my_queue<T>::push(T val) {
	if (m_capacity == 0) {
		m_capacity = 1;
		m_data = new T[m_capacity];
	}
	if (m_front + 1 >= m_capacity) {
		m_capacity *= 2;
		T* tmp = new T[m_capacity];
		int index = 0;
		for (int i = m_rear; i <= m_front; i++) {
			tmp[index++] = m_data[i];
		}
		delete[] m_data;
		m_data = new T[m_capacity];
		m_rear = 0, m_front = index - 1;
		for (int i = m_rear; i <= m_front; i++)m_data[i] = tmp[i];
		delete[]tmp;
	}
	m_data[++m_front] = val;
}

template <typename T>
T& my_queue<T>::rear() {
	return m_data[m_rear];
}

template <typename T>
T& my_queue<T>::front() {
	return m_data[m_front];
}

template <typename T>
void my_queue<T>::pop() {
	m_rear++;
}

template <typename T>
int my_queue<T>::size() {
	return m_front - m_rear + 1;
}

template <typename T>
bool my_queue<T>::empty() {
	return m_front < m_rear;
}

template <typename T>
T my_queue<T>::operator [](int index) {
	return m_data[index];
}

template <typename T>
int my_queue<T>::rearIndex() {
	return m_rear;
}

template<typename T>
bool my_queue<T>::operator !=(my_queue<T>& a) {
	if (a.size() != size())return 1;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (a[index++] != m_data[i])return 1;
	}
	return 0;
}

template <typename T>
bool my_queue<T>::operator ==(my_queue<T>& a) {
	if (a.size() != size())return 0;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (a[index++] != m_data[i])return 0;
	}
	return 1;
}

template <typename T>
bool my_queue<T>::operator < (my_queue<T>& a) {
	if (a.size() < size())return 0;
	else if (a.size() > size()) return 1;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (m_data[i] > a[index++])return 0;
	}
	if (front() == a.front())return 0;
	return 1;
}

template <typename T>
bool my_queue<T>::operator <= (my_queue<T>& a) {
	if (a.size() < size())return 0;
	else if (a.size() > size()) return 1;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (m_data[i] > a[index++])return 0;
	}
	return 1;
}

template <typename T>
bool my_queue<T>::operator > (my_queue<T>& a) {
	if (a.size() < size())return 1;
	else if (a.size() > size())return 0;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (m_data[i] > a[index++])return 0;
	}
	if (front() == a.front())return 0;
	return 1;
}

template <typename T>
bool my_queue<T>::operator >= (my_queue<T>& a) {
	if (a.size() < size())return 1;
	else if (a.size() > size())return 0;
	int index = a.rearIndex();
	for (int i = m_rear; i <= m_front; i++) {
		if (m_data[i] > a[index++])return 0;
	}
	return 1;
}

template <typename T>
my_queue<T>& my_queue<T>::operator = (my_queue<T>& a) {
	if (a.size() >= m_capacity) {
		delete[] m_data;
		m_data = new T[a.size() * 2];
	}
	int index = a.rearIndex();
	for (int i = 0; i < a.size(); i++) {
		m_data[i] = a[index++];
	}
	m_rear = 0;
	m_front = a.size() - 1;
	return *this;
}

template <class T>
struct Greater {
	bool operator ()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct Less {
	bool operator ()(T a, T b) {
		return a < b;
	}
};


template <class T,class container = vector<T>,class compare = Greater<T>>
class my_priority_queue {

public:
	inline void up(int k) {
		while (k > 1 && m_mul(m_data[k],m_data[k/2])){
			swap(m_data[k], m_data[k / 2]);
			k /= 2;
		}
	}

	inline void down(int k) {
		int len = m_data.size() - 1;
		while (k + k <= len) {
			int j = k + k;
			if (j + 1 <= len && m_mul(m_data[j+1],m_data[j])) {
				j++;
			}
			if (m_mul(m_data[k],m_data[j]))break;
			swap(m_data[k], m_data[j]);
			k = j;
		}
	}

	void push(T val) {
		if (!m_data.size())m_data.push_back(-1);
		m_data.push_back(val);
		up(m_data.size() - 1);
	}

	void pop() {
		swap(m_data[1], m_data.back());
		m_data.pop_back();
		down(1);
	}

	bool empty() {
		return (m_data.size() - 1) == 0;
	}

	T top() {
		return m_data[1];
	}

	int size() {
		return m_data.size();
	}

private:
	container m_data;
	compare m_mul;
};
