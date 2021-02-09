
#include "bignumber.h"
bigNum::bigNum()
{
	sayi.push_back(0);
	sign = true;
}
bigNum::bigNum(const long long& x)
{
	sign = x >= 0 ? true : false;
	if (abs(x) > bigNumMax)
		sayi.push_back(bigNumMax);
	else
		sayi.push_back(sign ? x : -x);
}
bigNum::bigNum(const unsigned long long& x)
{
	sign = true;
	sayi.push_back(x > bigNumMax ? bigNumMax : x);
}
bigNum::bigNum(const bigNum& x)
{
	sayi = x.sayi;
	sign = x.sign;
}
void bigNum::set(const std::string& x)
{
	bool xsign;
	if (x[0] == '-')
		sign = false;
	else
		sign = true;
	if (x[0] == '-' || x[0] == '+')
		sayi.resize((x.length() - 1) % 12 ? (x.length() - 1) / 12 + 1 : (x.length() - 1) / 12);
	else
		sayi.resize((x.length()) % 12 ? (x.length()) / 12 + 1 : (x.length()) / 12);
	for (long long i = 0; i < sayi.size() - 1; i++)
	{
		_5byte n(stoull(x.substr(x.length() - 12 * (i + 1), 12)));
		sayi[i] = n;
	}
	if (x[0] == '-' || x[0] == '+') {
		_5byte n(stoull(x.substr(1, (x.length() - 1) % 12 ? (x.length() - 1) % 12 : 12)));
		sayi[sayi.size() - 1] = n;
	}
	else
	{
		_5byte n(stoull(x.substr(0, x.length() % 12 ? x.length() % 12 : 12)));
		sayi[sayi.size() - 1] = n;
	}
}
std::string bigNum::get()
{
	std::stringstream ss;
	ss << (sign ? "" : "-") << sayi[sayi.size() - 1].readNum();
	for (long long i = sayi.size() - 2; i >= 0; i--) {
		long long ydk = sayi[i].readNum();
		int basamak = 12;
		do {
			ydk = (ydk - (ydk % 10)) / 10;
			basamak--;
		} while (ydk);
		while (basamak)
		{
			ss << "0";
			basamak--;
		}
		ss << sayi[i].readNum();
	}
	return ss.str();
}
void bigNum::operator=(const bigNum& x)
{
	sayi = x.sayi;
	sign = x.sign;
}
bigNum bigNum::operator+(const long long& x)
{
	bigNum bigx = x;
	return *this + bigx;
}
bigNum bigNum::operator-(const long long& x)
{
	return *this + (-x);
}
bigNum bigNum::operator+(bigNum x)
{
	bigNum res;
	if (this->sign == x.sign)
	{
		res = (this->sayi.size() >= x.sayi.size() ? *this : x);
		if (res == x)
			x = *this;
		for (long long i = x.sayi.size() - 1; i >= 0; i--)
		{
			if (bigNumMax - x.sayi[i].readNum() >= res.sayi[i].readNum())
			{
				res.sayi[i].putNum(res.sayi[i].readNum() + x.sayi[i].readNum());
			}
			else
			{
				x.sayi[i].putNum(x.sayi[i].readNum() - (bigNumMax - res.sayi[i].readNum() + 1));
				res.sayi[i] = x.sayi[i];
				x.sayi[i].putNum(1);
				for (long long j = i + 1; j < res.sayi.size(); j++)
				{
					if (res.sayi[j].readNum() == bigNumMax)
					{
						res.sayi[j].putNum(0);
					}
					else
					{
						res.sayi[j].putNum(res.sayi[j].readNum() + 1);
						x.sayi[i].putNum(0);
						break;
					}
				}
				if (x.sayi[i].readNum())
					res.sayi.push_back(1);
			}
		}
	}
	else
	{
		if (ignoreSignIsEqual(*this, x))
			return res;
		if (this->sayi.size() > x.sayi.size())
			res = *this;
		else if (this->sayi.size() == x.sayi.size())
		{
			for (long long i = this->sayi.size() - 1; i >= 0; i--)
			{
				if (this->sayi[i].readNum() > x.sayi[i].readNum())
				{
					res = *this;
					break;
				}
				if (this->sayi[i].readNum() < x.sayi[i].readNum())
				{
					res = x;
					x = *this;
					break;
				}
			}
		}
		else
		{
			res = x;
			x = *this;
		}
		for (long long i = x.sayi.size() - 1; i >= 0; i--)
		{
			if (res.sayi[i].readNum() >= x.sayi[i].readNum())
			{
				res.sayi[i].putNum(res.sayi[i].readNum() - (x.sayi[i].readNum()));
				if (res.sayi[i].readNum() == 0 && i + 1 == res.sayi.size())
					res.sayi.pop_back();
			}
			else {
				res.sayi[i].putNum(bigNumMax - x.sayi[i].readNum() + res.sayi[i].readNum() + 1);
				for (long long j = i + 1; j < res.sayi.size(); j++)
				{
					if (res.sayi[j].readNum() == 0)
						res.sayi[j].putNum(bigNumMax);
					else
					{
						res.sayi[j].putNum(res.sayi[j].readNum() - 1);
						if (res.sayi[j].readNum() == 0 && j + 1 == res.sayi.size())
							res.sayi.pop_back();
						break;
					}
				}
			}
		}
	}
	return res;
}
bigNum bigNum::operator-(bigNum x)
{
	return *this + (-x);
}
bool bigNum::operator==(bigNum& x)
{
	if (ignoreSignIsEqual(*this, x) && sign == x.sign)
		return true;
	return false;
}
bool bigNum::ignoreSignIsEqual(bigNum& left, bigNum& right)
{
	if (left.sayi.size() != right.sayi.size())
		return false;
	for (long long i = 0; i < left.sayi.size(); i++)
		if (left.sayi[i].readNum() != right.sayi[i].readNum())
			return false;
	return true;
}
bigNum bigNum::operator-()
{
	bigNum res = *this;
	res.sign = false;
	return res;
}
std::ostream& operator<<(std::ostream& os, bigNum x) {
	os << (x.sign ? "" : "-") << x.sayi[x.sayi.size() - 1].readNum();
	for (long long i = x.sayi.size() - 2; i >= 0; i--) {
		long long ydk = x.sayi[i].readNum();
		int basamak = 12;
		do {
			ydk = (ydk - (ydk % 10)) / 10;
			basamak--;
		} while (ydk);
		while (basamak)
		{
			os << "0";
			basamak--;
		}
		os << x.sayi[i].readNum();
	}
	return os;
}
bigNum::_5byte::_5byte()
{
	l1 = 0;
	r4 = 0;
}
bigNum::_5byte::_5byte(const unsigned long long& x)
{
	this->putNum(x);
}
void bigNum::_5byte::putNum(const unsigned long long& x)
{
	r4 = x;
	l1 = (x - r4) >> 32;
}
unsigned long long bigNum::_5byte::readNum()
{
	return ((unsigned long long)l1 << 32) + r4;
}
bool  bigNum::_5byte::operator==(const _5byte& x)
{
	if (l1 == x.l1&&r4 == x.r4)
		return true;
	return false;
}