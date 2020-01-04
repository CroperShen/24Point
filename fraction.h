//========================================
//fraction.h
//Created by Croper
//last modified in Dec.15.2018
//实现分数类，并通过重载，实现分数类的四则运算以及类型转换
//=========================================================


#pragma once
#include <iostream>
#include <stack>

double fraction_accuracy = 0.000001;   //当与实数进行转换时允许的最大误差

class fraction
{
	friend const fraction& operator+(const fraction, const  fraction);
	friend const fraction& operator-(const fraction, const  fraction);
	friend const fraction& operator*(const fraction, const  fraction);
	friend const fraction& operator/(const fraction, const  fraction);
	friend bool operator==(const fraction, const  fraction);
	friend bool operator!=(const fraction, const  fraction);
	friend std::ostream &operator<<(std::ostream&, fraction);
private:
	long num;   //分子
	long den;   //分母
	void Reduce();    //约分
public:
	fraction();
	fraction(int);
	fraction(int,int);
	
	fraction(double);
	fraction(const fraction&);

	explicit operator int() const;     //向下取整
	explicit operator long() const;
	explicit operator double() const;
	explicit operator float() const;

	fraction& operator+=(const fraction);
	fraction& operator-=(const fraction);
	fraction& operator*=(const fraction);
	fraction& operator/=(const fraction);
};

void fraction::Reduce() //约分
{
	long a;
	long p, q;

	if (den < 0) {
		num = 0 - num;
		den = 0 - den;
	}
	p = num;
	q = den;
	do                         //辗转相除求最大公约数
	{
		a = p % q;
		p = q;
		q = a;
	} while (a != 0);

	num/= p;
	den/= p;
}

fraction::fraction()
{
	num = 0;
	den = 1;
}

fraction::fraction(int a)
{
	num = a;
	den = 1;
}

fraction::fraction(int a, int b)
{
	if (b == 0) throw "除数不能为 0" ;
	num = a;
	den = b;
	Reduce();
}

#if 0==1 
fraction::fraction(double d)
{
	static fraction fsum;
	double e;
	fsum = (long)floor(d + 0.5);
	e = abs((double)fsum - d);
	while (abs(e) > abs(fraction_accuracy))
	{
		double x = 1. / e;
		double y = x + 0.5;
		int z = (int)floor(y);

		fsum += fraction(1,z);
		e = d-(double)fsum;
	}
	num = fsum.num;
	den = fsum.den;
}
#endif

fraction::fraction(double d)
{
	std::stack<int> stk,stk1;
	static fraction fsum;
	long n;
	double e,err;

	n = (long)floor(d + 0.5);
	stk.push(n);
	e = d-(double)n;
	err = abs(e);
	while (err > fraction_accuracy)
	{
		e = 1. / e;
		n = (long)floor(e + 0.5);
		e = e - (double)n;
		stk.push(n);
		stk1 = stk;
		fsum = 0;
		while (!stk1.empty())
		{
			n = stk1.top();
			stk1.pop();
			fsum = 1 / (fsum+n);
		}
		fsum = 1 / fsum;
		err = abs((double)fsum - d);
	}
	num = fsum.num;
	den = fsum.den;
}
fraction::fraction(const fraction& f)
{
	num = f.num;
	den = f.den;
}

fraction& fraction::operator+=(const fraction f)
{
	num = num*f.den + f.num*den;
	den = den * f.den;
	Reduce();
	return *this;
}

fraction& fraction::operator-=(const fraction f)
{
	num = num * f.den - f.num*den;
	den = den * f.den;
	Reduce();
	return *this;
}
fraction& fraction::operator*=(const fraction f)
{
	num = num * f.num;
	den = den * f.den;
	Reduce();
	return *this;
}
fraction& fraction::operator/=(const fraction f)
{
	if (f.num == 0) throw "除数不能为0";
	num = num * f.den;
	den = den * f.num;
	Reduce();
	return *this;
}

fraction::operator int() const      //按c++取整规则
{
	return (num / den);
}

fraction::operator long() const      //按c++取整规则
{
	return (num / den);
}

fraction::operator double() const
{
	return ((double)num / (double)den);
}

fraction::operator float() const
{
	return ((float)num / (float)den);
}

const fraction& operator+(const fraction f1, const fraction f2)
{
	static fraction f;
	f.num = f1.num*f2.den + f2.num*f1.den;
	f.den = f1.den*f2.den;
	f.Reduce();
	return f;
}
const fraction& operator-(const fraction f1, const fraction f2)
{
	static fraction f;
	f.num = f1.num*f2.den - f2.num*f1.den;
	f.den = f1.den*f2.den;
	f.Reduce();
	return f;
}

const fraction& operator*(const fraction f1, const fraction f2)
{
	static fraction f;
	f.num = f1.num*f2.num;
	f.den = f1.den*f2.den;
	f.Reduce();
	return f;
}

const fraction& operator/(const fraction f1, const fraction f2)
{
	static fraction f;
	if (f2.num == 0) throw "除数不能为0";
	f.num = f1.num*f2.den;
	f.den = f1.den*f2.num;
	f.Reduce();
	return f;
}
bool operator==(const fraction f1, const fraction f2)
{
	return ((f1.num == f2.num) && (f1.den == f2.den));
}
bool operator!=(const fraction f1, const fraction f2)
{
	return ((f1.num != f2.num) || (f1.den != f2.den));
}

std::ostream &operator<<(std::ostream& os, fraction f)
{
	os << f.num << "/" << f.den;
	return os;
}

