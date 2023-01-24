#include<iostream>
#include<stdexcept>
#include <initializer_list>

using namespace std;
template <typename T>

class my_vector {
public:
	my_vector();//��ָ�����ȵĳ�ʼ��
	~my_vector();//��������
	my_vector(const T& n);//��ָ�������г��ȵĳ�ʼ��
	my_vector(const T& n,const T& val);//��ָ�����ݵĳ�ʼ��
	void push_back(T val);//��ĩβ�������
	void pop_back();//�Ƴ�ĩβ����
	int size() const;//���鳤��
	void show();//�鿴vector����
	void resize(const T& n);//���³�ʼ����ָ������
	void resize(const T& n, const T& val);//���³�ʼ��
	T& at(int index);//�����±괦����
	T& operator [] (int index);//[]����
	T& back();//��������ĩβ����
	bool empty();//�Ƿ�Ϊ��
	void clear();//�Ƴ�ȫ��Ԫ��
	int datacapacity();//���ص�ǰ�������������
	T& front();//���ص�һ��λ��Ԫ��
	void swap(my_vector<T>& other);//���齻��
	void operator = (my_vector<T>& other);//���ں�����
	void operator = (initializer_list<T> a);
	T& operator = (T& val);
	bool operator < (my_vector<T>& a);
	bool operator <= (my_vector<T>& a);
	bool operator > (my_vector<T>& a);
	bool operator >= (my_vector<T>& a);
	T* Data();//����ָ��
	void insert(int index,  T val);//��������
	void insert(int index, T val, int nums);//������������

	class Iterator {

		public:
			Iterator() : it(nullptr){}
			Iterator(T* IT) : it(IT){}
			~Iterator(){}

			bool operator == (const Iterator& other) {
				return other,it == it;
			}

			bool operator != (const Iterator& other) {
				return other.it != it;
			}

			Iterator operator = (const Iterator& other) {
				it = other.it;
				return *this;
			}

			Iterator& operator ++() {
				it += 1;
				return *this;
			}

			Iterator operator ++(int) {
				Iterator t = *this;
				++it;
				return t;
			}

			Iterator operator +(int i) {
				it += i;
				return *this;
			}

			Iterator operator -(int i) {
				it -= i;
				return *this;
			}

			Iterator &operator += (int i) {
				it += i;
				return *this;
			}

			Iterator operator -= (int i) {
				it -= i;
				return *this;
			}

			int operator - (const Iterator& other)const {
				if (other.it != it) {
					throw logic_error("������ͬ�ĵ������������");
				}
				return other.it - it > 0 ? other.it-it : it-other.it;
			}

			T& operator * () {
				return *it;
			}

			T* operator -> () {
				return it;
			}

		private:
			T* it;
	};

	Iterator begin();
	Iterator end();
	Iterator find(const T & value);

private:
	T* data;
	int dataSize;
	int capacity;
};

template <typename T>
my_vector<T>::my_vector() : data(nullptr), dataSize(0), capacity(0){}
template <typename T>
my_vector<T>::~my_vector() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	dataSize = 0;
	capacity = 0;
}

template <typename T>
my_vector<T>::my_vector(const T& n) {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	dataSize = n;
	capacity = n;
	data = new T[n];
}

template <typename T>
my_vector<T>::my_vector(const T& n,const T& val) {
	dataSize = n;
	capacity = n;
	data = new T[n];
	for (int i = 0; i < dataSize; i++) {
		data[i] = val;
	}
}

template <typename T>
void my_vector<T> :: push_back(T val) {
	if (dataSize < capacity) {
		data[dataSize] = val;
		dataSize++;
		return;
	}
	if (capacity == 0)
		capacity = 1;
	else capacity *= 2;
	T* Ndata = new T[capacity];
	for (int i = 0; i < dataSize; i++) {
		Ndata[i] = data[i];
	}
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	data = Ndata;
	data[dataSize++] = val;
}

template <typename T>
void my_vector<T>::pop_back(){
	dataSize--;
}

template <typename T>
int my_vector<T>::size() const{
	return dataSize;
}

template <typename T>
void my_vector<T>::show() {
	cout << "size = " << size() << "\n";
	for (int i = 0; i < size(); i++) {
		cout << data[i] << " ";
	}
	cout << "\n" << datacapacity() << "\n";
}

template <typename T>
void my_vector<T>::resize(const T& n) {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	data = new T[n];
	capacity = n;
	dataSize = n;
}

template <typename T>
void my_vector<T>::resize(const T& n,const T& val) {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
	data = new T[n];
	capacity = n;
	dataSize = n;
	for (int i = 0; i < n; i++) {
		data[i] = val;
	}
}

template <typename T>
T& my_vector<T>::at(int index) {
	if (index < 0 || index >= dataSize) {
		throw logic_error("out of range");
	}
	return data[index];
}

template <typename T>
T& my_vector<T>::operator [](int index) {
	return at(index);
}

template <typename T>
T& my_vector<T>::back() {
	if (dataSize == 0) {
		throw logic_error("��ǰû�ж�β");
	}
	return data[dataSize - 1];
}

template <typename T>
bool my_vector<T>::empty() {
	return !dataSize;
}

template <typename T>
void my_vector<T>::clear() {
	delete[] data;
	data = nullptr;
	capacity = 0;
	dataSize = 0;
}
template <typename T>
int my_vector<T>::datacapacity() {
	return capacity;
}

template <typename T>
T& my_vector<T>::front() {
	if (dataSize == 0) {
		throw logic_error("��ǰû�ж�ͷ");
	}
	return data[0];
}

template <typename T>
void my_vector<T>::swap(my_vector<T>& other) {
	T* temp = other.data;
	int size = other.dataSize;
	int tmpcapacity = other.capacity;

	other.data = data;
	other.dataSize = dataSize;
	other.capacity = capacity;

	data = temp;
	dataSize = size;
	capacity = tmpcapacity;
}

template <typename T>
void my_vector<T>::operator = (my_vector<T>& other) {
	if (other.data == data)return;
	delete[] data;
	data = nullptr;
	data = new T[other.capacity];
	dataSize = other.dataSize;
	capacity = other.capacity;
	for (int i = 0; i < dataSize; i++) {
		data[i] = other[i];
	}
}

template <typename T>
bool my_vector<T>::operator < (my_vector<T>& a) {
	if (size() < a.size())return 1;
	else if (size() > a.size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (data[i] > a[i])return 0;
	}
	if (back() == a.back())return 0;
	return 1;
}

template <typename T>
bool my_vector<T>::operator <= (my_vector<T>& a) {
	if (size() < a.size())return 1;
	else if (size() > a.size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (data[i] > a[i])return 0;
	}
	return 1;
}

template <typename T>
bool my_vector<T>::operator > (my_vector<T>& a) {
	if (size() > a.size())return 1;
	else if (size() < a.size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (data[i] < a[i])return 0;
	}
	if (back() == a.back())return 0;
	return 1;
}

template <typename T>
bool my_vector<T>::operator >= (my_vector<T>& a) {
	if (size() > a.size())return 1;
	else if (size() < a.size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (data[i] < a[i])return 0;
	}
	return 1;
}

template <typename T>
T* my_vector<T>::Data() {
	return data;
}

template <typename T>
typename my_vector<T>::Iterator my_vector<T>::begin() {
	my_vector<T>::Iterator IT(data);
	return IT;
}

template <typename T>
typename my_vector<T>::Iterator my_vector<T>::end() {
	my_vector<T>::Iterator IT(data + dataSize);
	return IT;
}

template <typename T>
typename my_vector<T>::Iterator my_vector<T>::find(const T & value) {
	for (my_vector<T>::Iterator i = begin(); i != end(); i++) {
		if (*i == value)return i;
	}
	return end();
}

template <typename T>
T& my_vector<T>::operator = (T& val) {
	return val;
}

template <typename T>
void my_vector<T>::insert(int index, T val) {
	push_back(val);
	for (int i = index; i < size(); i++) {
		T tmp = data[i];
		data[i] = data[size() - 1];
		data[size() - 1] = tmp;
	}
}

template <typename T>
void my_vector<T>::insert(int index, T val,int nums) {
	my_vector<T> t = *this;
	data = nullptr;
	data = new T[(nums + t.size()) * 2];
	dataSize = 0;
	for (int i = 0; i < t.size(); i++) {
		if (i == index) {
			while(nums--)
			data[dataSize++] = val;
		}
		data[dataSize++] = t[i];
	}
}

template <typename T>
void my_vector<T>::operator = (initializer_list<T> a) {
	delete[] data;
	dataSize = 0;
	capacity = 2 * a.size();
	data = new T[capacity];
	for (auto t : a) {
		data[dataSize++] = t;
	}
}