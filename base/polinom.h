#pragma once
#include <iostream>
#include "list.h"
#include <cstring>
//#ifndef MY_SYMBOL_H
//#define MY_SYMBOL_H
//#include <math.h>

using namespace std;

struct TMonom
{
	double k;
	int power[3];
	TMonom()
	{
		for (int i = 0; i < 3; i++)
			power[i] = 0;
		k = 1;
	}
	bool operator>(TMonom &_mon)
	{
		if ((power[0] > _mon.power[0]) || ((power[0] == _mon.power[0]) && (power[1] > _mon.power[1])) || ((power[0] == _mon.power[0]) && (power[1] == _mon.power[1]) && (power[2] > _mon.power[2])))
		{
				return true;
		}
		return false;
	}
	bool operator <(TMonom &_mon)
	{
		if ((power[0] < _mon.power[0]) || ((power[0] == _mon.power[0]) && (power[1] < _mon.power[1])) || ((power[0] == _mon.power[0]) && (power[1] == _mon.power[1]) && (power[2] < _mon.power[2])))
		{
				return true;
		}
		return false;
	}
	bool operator==(TMonom &_mon)
	{
		for (int h = 0; h < 3; h++)
			if (power[h] != _mon.power[h])
				return false;
		return true;
	}
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
//#endif MY_SYMBOL_H