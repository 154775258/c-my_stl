#include<stdexcept>
#include<cstring>
#include<iostream>
using namespace std;

class my_string {
	public:
		my_string();
		~my_string();
		my_string(const char* val);
		my_string(int size, char val);
		friend ostream& operator << (ostream& out,my_string val);
		friend istream& operator >> (istream& in, my_string& val);
		bool empty();
		my_string& operator += (char* val);
		my_string& operator += (my_string& val);
		my_string& operator + (my_string& val);
		my_string& operator + (char* val);
		my_string& operator += (char val);
		my_string& operator + (char val);
		my_string& operator = (char val);
		my_string& operator = (my_string& val);
		my_string& operator = (char* val);
		bool operator < (my_string& a);
		bool operator > (my_string& a);
		bool operator <= (my_string& a);
		bool operator >= (my_string& a);
		bool operator == (my_string a);
		bool operator != (my_string a);
		char& operator [](int index);
		int size();
		void pop_back();
		my_string substr(int start, int len);
		my_string substr(int start);
		void insert(int index, char val);
		void insert(int index, char val, int nums);
		char& back();
		bool find(my_string val);
		bool find(char* val);
		bool find(char val);
		int coiledFind(char val);
		int coiledFind(char* val);
		int coiledFind(my_string val);

private:
	char* m_data;
	int m_size;
	int m_capacity;
};

my_string::my_string() :m_data(nullptr), m_size(0), m_capacity(0){}

my_string::~my_string() {
	if (m_capacity != 0) {
		m_size = 0, m_capacity = 0;
	}
}

my_string::my_string(int size, char val) {
	m_capacity = 2 * size;
	m_data = new char[m_capacity];
	while (m_size < size)m_data[m_size++] = val;
}

my_string::my_string(const char* val) {
	m_size = strlen(val);
	m_capacity = m_size;
	m_data = new char [2*m_capacity];
	for (int i = 0; i < m_size; i++) {
		m_data[i] = val[i];
	}
}

ostream& operator << (ostream& out,my_string val) {
	if (val.m_data != nullptr) {
		for (int i = 0; i < val.m_size; i++) {
			out << val[i];
		}
	}
	return out;
}

istream& operator >> (istream& in, my_string& val) {
	char t[4096];
	in >> t;
	int n = strlen(t);
	delete[] val.m_data;
	val.m_data = nullptr;
	val.m_data = new char[2 * n];
	val.m_size = n;
	val.m_capacity = 2 * n;
	for (int i = 0; i < n; i++) {
		val.m_data[i] = t[i];
	}
	delete[] t;
	return in;
}

bool my_string::empty() {
	return m_size == 0;
}

my_string ____;
void swap(my_string& left, my_string& right){
	____ = left;
	left = right;
	right = ____; 
}

my_string& my_string::operator += (char* val) {
	int n = strlen(val);
	if (m_capacity - m_size - n < 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_size);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
		delete[] tmp;
	}
	else {
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
	}
	return *this;
}

my_string& my_string::operator += (my_string& val) {
	int n = val.size();
	if (m_capacity - m_size - n <= 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_capacity);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
		delete[]tmp;
	}
	else {
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
	}
	return *this;
}

my_string& my_string::operator + (my_string& val) {
	int n = val.m_size;
	if (m_capacity - m_size < 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_size);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val.m_data[i];
		}
		delete[] tmp;
	}
	else {
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val.m_data[i];
		}
	}
	return *this;
}

my_string& my_string::operator + (char* val) {
	int n = strlen(val);
	if (m_capacity - m_size - n < 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_size);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
		delete[] tmp;
	}
	else {
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
	}
	return *this;
}

my_string& my_string::operator = (char* val) {
	int n = strlen(val);
	if (n > m_capacity) {
		delete[] m_data;
		m_data = nullptr;
		m_data = new char[2 * n];
		m_capacity = 2 * n;
		m_size = 0;
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
	}
	else {
		m_size = 0;
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val[i];
		}
	}
	return *this;
}

my_string& my_string::operator = (my_string& val) {
	int n = val.size();
	if (n > m_capacity) {
		delete[] m_data;
		m_data = nullptr;
		m_data = new char[2 * n];
		m_capacity = 2 * n;
		m_size = n;
		for (int i = 0; i < n; i++) {
			m_data[i] = val[i];
		}
	}
	else {
		m_size = n;
		for (int i = 0; i < n; i++) {
			m_data[i] = val[i];
		}
	}
	return *this;
}

my_string& my_string::operator + (char val) {
	int n = 1;
	if (m_capacity - m_size - n < 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_size);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val;
		}
		delete[] tmp;
	}
	else {
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val;
		}
	}
	return *this;
}

my_string& my_string::operator += (char val) {
	int n = 1;
	if (m_capacity - m_size - n < 0) {
		char* tmp = m_data;
		m_capacity = 2 * (n + m_size);
		m_data = new char[m_capacity];
		for (int i = 0; i < m_size; i++) {
			m_data[i] = tmp[i];
		}
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val;
		}
	}
	else {
		m_data[m_size++] = val;
	}
	return *this;
}

my_string& my_string::operator = (char val) {
	int n = 1;
	if (n > m_capacity) {
		delete[] m_data;
		m_data = nullptr;
		m_data = new char[2 * n];
		m_capacity = 2 * n;
		m_size = 0;
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val;
		}
	}
	else {
		m_size = 0;
		for (int i = 0; i < n; i++) {
			m_data[m_size++] = val;
		}
	}
	return *this;
}

bool my_string::operator < (my_string& a) {
	if (a.size() > size())return 1;
	else if(a.size() < size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	if (back() == a.back())return 0;
	return 1;
}

bool my_string::operator <= (my_string& a) {
	if (a.size() > size())return 1;
	else if (a.size() < size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] > a[i])return 0;
	}
	return 1;
}

bool my_string::operator > (my_string& a) {
	if (a.size() < size())return 1;
	else if (a.size() > size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] < a[i])return 0;
	}
	if (back() == a.back())return 0;
	return 1;
}

bool my_string::operator >= (my_string& a) {
	if (a.size() < size())return 1;
	else if (a.size() > size())return 0;
	for (int i = 0; i < a.size(); i++) {
		if (m_data[i] < a[i])return 0;
	}
	return 1;
}

void my_string::pop_back() {
	m_size--;
}

int my_string::size() {
	return m_size;
}

char& my_string::operator [](int index) {
	if (index < 0 || index >= m_size) {
		throw logic_error("下标越界");
	}
	return m_data[index];
}

void reverse(my_string& a) {
	my_string b;
	for (int i = a.size() - 1; i >= 0; i--) {
		b += a[i];
	}
	for (int i = 0; i < a.size(); i++) {
		a[i] = b[i];
	}
}

my_string ans;
my_string& my_to_string(const int& a) {
	long long t = a;
	while (!ans.empty())ans.pop_back();
	if (a < 0) {
		t *= -1;
		while (t) {
			ans += (char)(t % 10 + '0');
			t /= 10;
		}
		ans += '-';
		reverse(ans);
		return ans;
	}
	if (a == 0) {
		ans += '0';
		return ans;
	}
	if (a > 0) {
		while (t) {
			ans += (char)(t % 10 + '0');
			t /= 10;
		}
		reverse(ans);
		return ans;
	}
	return ans;
}

my_string& my_to_string(const long long& a) {
	long long t = a;
	while (!ans.empty())ans.pop_back();
	if (a < 0) {
		t *= -1;
		while (t) {
			ans += (char)(t % 10 + '0');
			t /= 10;
		}
		ans += '-';
		reverse(ans);
		return ans;
	}
	if (a == 0) {
		ans += '0';
		return ans;
	}
	if (a > 0) {
		while (t) {
			ans += (char)(t % 10 + '0');
			t /= 10;
		}
		reverse(ans);
		return ans;
	}
	return ans;
}

my_string& my_to_string(double a) {
	int t = a / 1;
	int num = 0;
	double tmp = a;
	while (tmp != (double)t) {
		tmp *= 10;
		num++;
		t = tmp / 1;
	}
	while (!ans.empty())ans.pop_back();
	if (a < 0) {
		tmp *= -1;
		int k = 0;
		while ((int)tmp) {
			k++;
			ans += (char)((int)tmp % 10 + '0');
			if (k == num)ans += '.';
			tmp /= 10;
		}
		ans += '-';
		reverse(ans);
		return ans;
	}
	if (a == 0) {
		ans += '0';
		return ans;
	}
	if (a > 0) {
		int k = 0;
		while ((int)tmp) {
			k++;
			ans += (char)((int)tmp % 10 + '0');
			if (k == num)ans += '.';
			tmp /= 10;
		}
		reverse(ans);
		return ans;
	}
	return ans;
}

bool my_string::operator == (my_string a) {
	if (a.size() != m_size)return 0;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != m_data[i])return 0;
	return 1;
}

bool my_string::operator != (my_string a) {
	if (a.size() != m_size)return 1;
	for (int i = 0; i < a.size(); i++)
		if (a[i] != m_data[i])return 1;
	return 0;
}

my_string my_string::substr(int start, int len) {
	while (ans.size())ans.pop_back();
	int n = start + len;
	if (n > m_size) {
		throw logic_error("erroo index");
	}
	for (int i = start; i < n; i++) {
		ans += m_data[i];
	}
	return ans;
}

my_string my_string::substr(int start) {
	while (ans.size())ans.pop_back();
	if (start >= size()) {
		throw logic_error("超出字符串长度");
	}
	for (int i = start; i < size(); i++) {
		ans += m_data[i];
	}
	return ans;
}

void my_string::insert(int index, char val) {
	my_string p = *this;
	p += val;
	for (int i = index; i < p.size(); i++) {
		char tmp = p[i];
		p[i] = p[p.size() - 1];
		p[p.size() - 1] = tmp;
	}
	*this = p;
}

void my_string::insert(int index, char val, int nums) {
	my_string p = *this;
	delete[] m_data;
	m_data = nullptr;
	m_data = new char[(p.size() + nums) * 2];
	m_size = 0;
	for (int i = 0; i < p.size(); i++) {
		if (i == index) {
			while (nums--) {
				m_data[m_size++] = val;
			}
		}
		m_data[m_size++] = p[i];
	}
}

char& my_string::back() {
	return m_data[m_size - 1];
}

int strlen(my_string val) {
	return val.size();
}

bool my_string::find(my_string val) {
	if (empty() || val.empty())return 0;
	int n = strlen(val);
	for (int i = 0; i <= m_size - n; i++) {
		if (m_data[i] == val[0]) {
			int index = 0;
			bool use = 1;
			for (int j = i; j < i + n; j++) {
				if (m_data[j] != val[index++])use = 0;
			}
			if (use)return 1;
		}
	}
	return 0;
}

bool my_string::find(char* val) {
	if (empty())return 0;
	int n = strlen(val);
	if (n == 0)return 0;
	for (int i = 0; i <= m_size - n; i++) {
		if (m_data[i] == val[0]) {
			int index = 0;
			bool use = 1;
			for (int j = i; j < i + n; j++) {
				if (m_data[j] != val[index++])use = 0;
			}
			if (use)return 1;
		}
	}
	return 0;
}

bool my_string::find(char val) {
	if (empty())return 0;
	for (int i = 0; i < m_size; i++)
		if (val == m_data[i])return 1;
	return 0;
}

int my_string::coiledFind(char val) {
	if (empty())return 0;
	int res = 0;
	int tmpN = 0;
	for (int i = 0; i < m_size; i++) {
		if (val != m_data[i])tmpN = 0;
		else tmpN++;
		res = res > tmpN ? res : tmpN;
	}
	return res;
}

int my_string::coiledFind(char* val) {
	int n = strlen(val);
	if (n == 0 || empty())return 0;
	int res = 0;
	int tmpN = 0;
	for (int i = 0; i <= m_size - n; i++) {
		if (val[0] == m_data[i]) {
			my_string tmp;
			tmp += val;
			while (i + tmp.size() <= size() && tmp == substr(i, tmp.size())) {
				tmp += val;
				tmpN++;
			}
			res = res > tmpN ? res : tmpN;
			tmpN = 0;
		}
	}
	return res;
}

int my_string::coiledFind(my_string val) {
	int n = strlen(val);
	if (n == 0 || empty())return 0;
	int res = 0;
	int tmpN = 0;
	for (int i = 0; i <= m_size - n; i++) {
		if (val[0] == m_data[i]) {
			my_string tmp;
			tmp += val;
			while (i + tmp.size() <= size() && tmp == substr(i, tmp.size())) {
				tmp += val;
				tmpN++;
			}
			res = res > tmpN ? res : tmpN;
			tmpN = 0;
		}
	}
	return res;
}