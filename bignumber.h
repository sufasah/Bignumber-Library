#pragma once
#ifndef bignumber_h
#define bignumber_h
#define bigNumMax (unsigned long long)0xE8D4A50FFF
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
class bigNum {
public:
	bigNum();
	bigNum(const long long& x);
	bigNum(const unsigned long long& x);
	bigNum(const bigNum& x);
	void set(const std::string& x);
	std::string get();
	void operator=(const bigNum& x);
	bigNum operator+(const long long& x);
	bigNum operator-(const long long& x);
	bigNum operator+(bigNum x);
	bigNum operator-(bigNum x);
	bool operator==(bigNum& x);
	bool ignoreSignIsEqual(bigNum& left, bigNum& right);
	bigNum operator-();
	friend std::ostream& operator<<(std::ostream& os, bigNum x);
	private:
	struct _5byte
	{
	private:
		unsigned char l1;
		unsigned int r4;
	public:
		_5byte();
		_5byte(const unsigned long long& x);
		void putNum(const unsigned long long& x);
		unsigned long long readNum();
		bool operator==(const _5byte& x);
	};
	bool sign;
	std::vector<_5byte> sayi;
};

#endif