#ifndef __BIG_INT_H__
#define __BIG_INT_H__


#include <string>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <memory>
#include <iostream>
#include <cstring>

class BigInt
{
public:
    BigInt();
    BigInt(long long num);
    BigInt(const std::string& num);
    BigInt(const BigInt& other);
    ~BigInt() = default;

    friend std::ostream& operator << (std::ostream& os, BigInt num);
    friend std::istream& operator >> (std::istream& is, BigInt& num);
    BigInt& operator = (const BigInt& other);
    BigInt operator + (BigInt other);
    BigInt operator * (const BigInt& other);
    BigInt operator - (const BigInt& other);
    BigInt operator / (const BigInt& other);
    int abscompare(const BigInt& other);
    bool operator < (const BigInt& other);
    bool operator > (const BigInt& other);
    bool operator <= (const BigInt& other);
    bool operator >= (const BigInt& other);
    bool operator == (const BigInt& other);
    bool operator != (const BigInt& other);
private:
    BigInt operator * (const int s);
    void squeeze();
private:
    std::string _num;                 //´æ´¢Êý¾Ý
    int sign;                         //·ûºÅÎ»
};

#endif //__BIG_INT_H__;
BigInt::BigInt()
{
    sign = 0;
    _num = std::string();
};

BigInt::BigInt(long long num)
{
    BigInt t(std::to_string(num));
}

BigInt::BigInt(const std::string& num)
{
    sign = 1;
    if (num[0] == '-')sign = -1;
    _num = num;
    std::reverse(_num.begin(), _num.end());
}

BigInt::BigInt(const BigInt& other)
{
    this->_num = other._num;
    this->sign = other.sign;
}

std::ostream& operator << (std::ostream& os, BigInt num)
{
    std::string tmp = num._num;
    std::reverse(tmp.begin(), tmp.end());
    if (num.sign < 0)
        os << "-";
    return os << tmp;
}

std::istream& operator >> (std::istream& is, BigInt& num)
{
    is >> num._num;
    num.sign = 1;
    for (int i = 0; i < num._num.size(); i++)
    {
        if (!i && num._num[i] == '-')
        {
            num.sign = -1;
            continue;
        }

        assert(num._num[i] <= '9' && num._num[i] >= '0');
    }

    if (num._num.size() == 1 && num._num[0] == '0')
        num.sign = 0;
    if (num.sign < 0)
        num._num = num._num.substr(1);
    std::reverse(num._num.begin(), num._num.end());
    return is;
}

BigInt& BigInt::operator=(const BigInt& other)
{
    this->_num = other._num;
    this->sign = other.sign;
    return *this;
}

BigInt BigInt::operator+(BigInt other)
{

    BigInt rval;
    if (this->sign == other.sign)
        rval.sign = this->sign;
    else
    {
        if (this->sign > 0)
        {
            other.sign = 1;
            return *this - other;
        }
        else
        {
            BigInt temp(*this);
            temp.sign = 1;
            return other - temp;
        }

    }
    int len1 = this->_num.size();
    int len2 = other._num.size();
    int len = std::max(len1, len2);

    std::stringstream ss;
    int i(0), bit(0);
    for (; i < len; i++)
    {
        char a = i < len1 ? this->_num[i] : '0';
        char b = i < len2 ? other._num[i] : '0';
        char result = a + b + bit - '0';
        if (result > '9')
        {
            result -= 10;
            bit = 1;
        }
        else
            bit = 0;
        ss << result;
    }
    if (bit)
        ss << bit;
    rval._num.append(ss.str());
    return rval;

}


BigInt BigInt::operator*(const int s)
{
    BigInt rval;
    std::stringstream ss;
    int bit(0);
    for (int i = 0; i < (*this)._num.size(); i++)
    {
        int result = ((*this)._num[i] - '0') * s + bit;
        if (result > 9)
        {
            bit = result / 10;
            result = result % 10;
        }
        else
        {
            bit = 0;
        }
        ss << result;
    }
    if (bit)
        ss << bit;
    rval._num.append(ss.str());
    return rval;
}

BigInt BigInt::operator*(const BigInt& other)
{
    BigInt rval, temp;
    int size = other._num.size();
    for (int i = 0; i < size; i++)
    {
        temp = (*this) * (other._num[i] - '0');
        for (int j = 0; j < i; j++)
        {
            temp._num.insert(0, "0");
        }
        rval = rval + temp;
    }
    rval.sign = this->sign * other.sign;
    return rval;
}

BigInt BigInt::operator - (const BigInt& other)
{
    BigInt rval;
    std::string max = this->_num;
    std::string min = other._num;

    if (this->sign == other.sign)
    {
        int result = this->abscompare(other);
        if (result == 1)
        {
            rval.sign = this->sign;
        }
        else if (result == -1)
        {
            rval.sign = -other.sign;
            min = this->_num;
            max = other._num;
        }
        else
        {
            rval.sign = 0;
            rval._num.append("0");
            return rval;
        }
    }
    else if (this->sign > other.sign)
    {
        rval.sign = 1;
        rval._num = this->_num;
        BigInt temp(other);
        temp.sign = 1;
        return rval + temp;
    }
    else
    {
        rval.sign = -1;
        rval._num = this->_num;
        BigInt temp(other);
        temp.sign = -1;
        return rval + temp;
    }

    int bit(0);
    std::stringstream ss;
    int i(0);
    for (; i < max.size(); i++)
    {
        char a = max.at(i);
        char b = i < min.size() ? min.at(i) : '0';
        char result;
        if ((a - bit) >= b)
        {
            result = a - bit - b + '0';
            bit = 0;
        }
        else
        {
            result = a + 10 - b - bit + '0';
            bit = 1;
        }
        ss << result;
    }
    ss >> rval._num;
    rval.squeeze();
    return rval;
}

BigInt BigInt::operator / (const BigInt& other)
{
    BigInt tmp = *this;
    BigInt ans;
    BigInt N(std::to_string(10));
    while (tmp >= other) {
        int num = 0;
        BigInt t = other;
        while (tmp >= (t * N)) {
            num++;
            t = t * N;
        }
        int a = 0;
        while (tmp >= t) {
            tmp = tmp - t;
            a++;
        }
        BigInt res(std::to_string(a));
        while (num--) {
            res = res * N;
        }
        ans = ans + res;
    }
    return ans;
}

int BigInt::abscompare(const BigInt& other)
{

    if (this->_num.size() > other._num.size())
        return 1;
    if (this->_num.size() < other._num.size())
        return -1;

    std::string temp1 = this->_num;
    std::string temp2 = other._num;
    std::reverse(temp1.begin(), temp1.end());
    std::reverse(temp2.begin(), temp2.end());
    if (temp1 > temp2)
        return 1;
    else if (temp1 == temp2)
        return 0;
    else
        return -1;
}

bool BigInt::operator < (const BigInt& other)
{
    BigInt temp = *this - other;
    return temp.sign < 0;
}

bool BigInt::operator > (const BigInt& other)
{
    BigInt temp = *this - other;
    return temp.sign > 0;
}

bool BigInt::operator <= (const BigInt& other)
{
    return  !((*this) > other);
}

bool BigInt::operator >= (const BigInt& other)
{
    return  !((*this) < other);
}

bool BigInt::operator == (const BigInt& other)
{
    return !(*this < other) && !(*this > other);
}


void BigInt::squeeze()
{
    bool iscontinue = true;
    for (int i = _num.size() - 1; i >= 1 && iscontinue; i--)
    {
        if (_num[i] == '0')
        {
            _num[i] = 0;
            continue;
        }
        iscontinue = false;
    }
}