#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include "stack.h"
#include "Table.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	int count = 0;
	int Compare(char _t1);
	bool CorrectRecord();
	bool IsOperations(char s);
	bool IsOperand(char s);
public:
	TPostfix(string str = "");
	void SetInfix(string _infix);
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	void ToPostfix();
	double Calculate(double x, double y, double z);
	TPolinom CalcPol(TableLine<TPolinom> &table);
};

#endif