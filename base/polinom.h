#include<iostream>
#include "list.h"
#include <cstring>
#include <math.h>

using namespace std;

struct TMonom
{
	double k;
	int power[3];
	TMonom() : k(0) {
		for (int i = 0; i < 3; i++)
			power[i] = 0;
	};
};


class TPolinom
{
	TList<TMonom> monoms;
	string polinom;
	void strPolinom();
public:
	TPolinom();
	TPolinom(string _polinom);
	TPolinom(TPolinom &_TPolinom);
	TPolinom& operator=(TPolinom &_TPolinom);
	TPolinom operator+(TPolinom &_TPolinom);
	TPolinom operator-(TPolinom &_TPolinom);
	TPolinom operator*(TPolinom &_TPolinom);
	TPolinom operator/(TPolinom &_TPolinom);
	TPolinom operator%(TPolinom &_TPolinom);
	TPolinom Integration(TPolinom &_TPolinom, char var);
	TPolinom Differentiation(TPolinom &_TPolinom, char var);
	void SetPolinom(string &_polinom);
	TList<TMonom> GetPolinom();
	string GetStrPolinom();
	double Calculate(const double &x, const double &y, const double &z);
};
