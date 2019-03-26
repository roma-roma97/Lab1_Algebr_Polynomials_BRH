#ifndef __TPOLINOM_H__
#define __TPOLINOM_H__

#include<iostream>
#include "list.h"
#include <string>
#include <math.h>

using namespace std;

struct TMonom
{
	double k;
	int power[3];
	TMonom()
	{
		for (int i = 0; i < 3; i++)
			power[i] = 0;
		k = 0;
	};
};


class TPolinom
{
	TList<TMonom> monoms;
	string polinom;
	void strPolinom();
public:
	friend ostream& operator << (std::ostream &out, TPolinom &pol);
	TPolinom();
	TPolinom(string _polinom);
	TPolinom(TPolinom &_TPolinom);
	TPolinom& operator=(TPolinom &_TPolinom);
	TPolinom operator+(TPolinom &_TPolinom);
	TPolinom operator-(TPolinom &_TPolinom);
	TPolinom operator*(TPolinom &_TPolinom);
	TPolinom operator/(TPolinom &_TPolinom);
	TPolinom Integration(TPolinom & _Polinom, int var);
	TPolinom Differentiation(TPolinom & _Polinom, int var);
	TPolinom operator%(TPolinom &_TPolinom);
	void SetPolinom(string &_polinom);
	TList<TMonom> GetPolinom();
	string GetStrPolinom();
	double Calculate(const double &x, const double &y, const double &z);
};

#endif 