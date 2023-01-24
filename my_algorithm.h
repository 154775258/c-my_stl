#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include<sstream>
#include<string>
#include<cstring>
using namespace std;

template <typename T>
T my_max(T a, T b);
template <typename T>
T my_min(T a, T b);
template <typename T>
vector<T> allShuffle(T nums);//求全排列有重复
template <typename T>
void backstrack(T& nums, int start, vector<T>& ans);//全排列功能函数
template <typename T>
vector<T> subsets(T& nums);//求子集有重复
template <typename T>
void backstrack(T temp, T& nums, int start, vector<T>& ans);//子集功能函数
template <typename T>
long long pow(T a, T b);
string multiply(string num1, string num2);
string maxPow(int a, int b);
int maxSubArrayLen(vector<int>& nums, int k);

template <typename T>
T my_max(T a, T b) {
	return a <= b ? b : a;
}

template <typename T>
T my_min(T a, T b) {
	return a <= b ? a : b;
}

template <typename T>
vector<T> allShuffle(T nums) {
    vector<T> ans;
    backstrack(nums, 0, ans);
    return ans;
}

template <typename T>
void backstrack(T& nums, int start,vector<T>& ans) {
    if (start == nums.size()) {
        ans.push_back(nums);
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        swap(nums[i], nums[start]);
        backstrack(nums, start + 1,ans);
        swap(nums[i], nums[start]);
    }
}

template <typename T>
void backstrack(T temp,T& nums, int start,vector<T>& ans) {
    ans.push_back(temp);
    if (start == nums.size()) {
        return;
    }
    for (int i = start; i < nums.size(); i++) {
        temp.push_back(nums[i]);
        backstrack(temp, nums, i + 1,ans);
        temp.pop_back();
    }
}

template <typename T>
vector<T> subsets(T& nums) {
    vector<T> ans;
    T temp;
    backstrack(temp, nums, 0, ans);
    return ans;
}


template<typename T>
void mergeSort(T& num) {
	if (num.size() == 2) {
		if (num[0] > num[1]) {
			swap(num[0], num[1]);
		}
		return;
	}
	else if (num.size() == 1)return;
	T t1(num.size() / 2);
	T t2((num.size() + 1) / 2);
	int k = 0;
	while (k < (int)num.size() / 2) {
		t1[k] = num[k];
		k++;
	}
	int m = 0;
	while (k < (int)num.size()) {
		t2[m++] = num[k];
		k++;
	}
	mergeSort(t1);
	mergeSort(t2);
	int i = 0;
	int j = 0;
	k = 0;
	while (i < (int)t1.size() || j < (int)t2.size()) {
		if (i < (int)t1.size() && j < (int)t2.size()) {
			if (t1[i] < t2[j]) {
				num[k] = t1[i];
				i++;
				k++;
			}
			else {
				num[k] = t2[j];
				j++;
				k++;
			}
		}
		else if (i < (int)t1.size()) {
			num[k] = t1[i];
			i++;
			k++;
		}
		else {
			num[k] = t2[j];
			j++;
			k++;
		}
	}
}

template <typename T>
long long my_pow(T a, T b) {
	long long ans = 1;
	while (b) {
		long long k = 1;
		long long t = a;
		while (k + k <= b) {
			t *= t;
			k += k;
		}
		ans *= t;
		b -= k;
	}
	return ans;
}

string maxPow(int a, int b) {
	string tmp = to_string(a);
	string ans = "1";
	while (b > 0) {
		long long k = 1;
		string t = tmp;
		while (k + k <= b) {
			t = multiply(t,t);
			k += k;
		}
		ans = multiply(ans, t);
		b -= k;
	}
	return ans;
}

string multiply(string num1, string num2) {
	if (num1 == "0" || num2 == "0") {
		return "0";
	}
	int m = num1.size(), n = num2.size();
	auto ansArr = vector<int>(m + n);
	for (int i = m - 1; i >= 0; i--) {
		int x = num1.at(i) - '0';
		for (int j = n - 1; j >= 0; j--) {
			int y = num2.at(j) - '0';
			ansArr[i + j + 1] += x * y;
		}
	}
	for (int i = m + n - 1; i > 0; i--) {
		ansArr[i - 1] += ansArr[i] / 10;
		ansArr[i] %= 10;
	}
	int index = ansArr[0] == 0 ? 1 : 0;
	string ans;
	while (index < m + n) {
		ans.push_back(ansArr[index]);
		index++;
	}
	for (auto& c : ans) {
		c += '0';
	}
	return ans;
}

int maxSubArrayLen(vector<int>& nums, int k) {
	unordered_map<long, int> p;
	p[0] = -1;
	long long sum = 0;
	int ans = 0;
	for (int i = 0; i < nums.size(); i++) {
		sum += nums[i];
		if (p.count(sum - k))ans = max(ans, i - p[sum - k]);
		if (!p.count(sum))p[sum] = i;
	}
	return ans;
}

template<class T1 = int, class T2 = int>
class disjoint_set {
public:
	disjoint_set() {
		clear();
	}
	~disjoint_set() {}
	T2 find(const T1& x) {
		if (m_data[x] == x)return x;
		return find(m_data[x]);
	}

	disjoint_set(const int len) {
		clear();
		for (int i = 1; i <= len; i++) {
			m_data[i] = i;
		}
		cnt = len;
	}

	T2 pathFind(const T1& x) {
		if (m_data[x] == x)return x;
		return m_data[x] = find(m_data[x]);
	}

	void add(const T1& x, const T1& y) {
		T2 a = find(x), b = find(y);
		if (a == b)return;
		m_data[a] = m_data[b];
		cnt--;
	}

	void pathAdd(const T1& x, const T1& y) {
		T2 a = pathFind(x), b = pathFind(y);
		if (a == b)return;
		m_data[a] = m_data[b];
		cnt--;
	}

	int size() {
		return cnt;
	}

	void clear() {
		m_data.clear();
	}

	T2& operator [](T1& len) {
		return m_data[len];
	}

	void addCnt() { cnt++; }

	bool count(T1& val) {
		return m_data.count(val);
	}

private:
	unordered_map<T1, T2> m_data;
	int cnt = 0;
};
