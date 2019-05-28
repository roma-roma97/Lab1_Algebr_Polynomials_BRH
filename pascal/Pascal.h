#pragma once

#include "TableVar.h"
#include "Node.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Pascal {
	TableLine<Var<int>> varint;  // int переменные
	TableLine<Var<double>> vardob; // double переменные
	node<vector<string>>* pFirst;
	vector<vector<string>> tmp;
	vector<string> prog;
	int countB = 0;
	int countE = 0;
	int lvl = 0;
	bool Separation(char _str)
	{
		if (_str == ' ' || _str == '*' || _str == '/' || _str == '+' || _str == '-' || _str == ':' || _str == '=' || _str == ';' || _str == ',' || _str == '(' || _str == ')' || _str == '"')
			return true;
		return false;
	}
	string DeleteTab(string _str)
	{
		for (int i = 0; i < _str.size(); i++)
			if (_str[i] == ' ')
				continue;
			else
				_str = _str.substr(i);
		return _str;
	}
	vector<string> SeparStr(string _str)
	{
		string tmp = "";
		vector<string>words;
		for (int i = 0; i < _str.size() - 1; i++)
		{
			if (!Separation(_str[i]))
				tmp += _str[i];
			else if (_str[i] == ' ')
			{
				if (tmp != "")
				{
					words.push_back(tmp);
					tmp = "";
				}
			}
			else if (_str[i] == ':' && _str[i + 1] == '=')
			{
				words.push_back(_str);
				words.push_back(":=");
				i++;
				tmp = "";
			}
			else
				if (tmp != "")
				{
					words.push_back(tmp);
					tmp = _str[i];
					words.push_back(tmp);
				}
		}
		if (tmp != "")
			words.push_back(tmp);
		return words;
	}
	int Begin(int& _lvl)
	{
		while (_lvl != tmp.size() || tmp[_lvl][0] != "end." || tmp[_lvl][0] != "end")
		{
			if (tmp[_lvl][0] == "Write")
			{
				if (tmp[_lvl][1] != "(" || tmp[_lvl][tmp[_lvl].size() - 2] != ")")
				{
					cout << "" << endl;
					return 1;
				}
				if (tmp[_lvl][tmp[_lvl].size() - 1] != ";")
				{
					cout << "" << endl;
					return 1;
				}
				for (int l = 2; l < tmp[_lvl].size() - 2; l++)
				{
					//обработка внутри write;
				}
				lvl++;
				continue;
			}
			if (tmp[_lvl][0] == "Read")
			{
				if (tmp[_lvl][1] != "(" || tmp[_lvl][tmp[_lvl].size() - 2] != ")")
				{
					cout << "" << endl;
					return 1;
				}
				if (tmp[_lvl][tmp[_lvl].size() - 1] != ";")
				{
					cout << "" << endl;
					return 1;
				}
				for (int l = 2; l < tmp[_lvl].size() - 2; l++)
				{
					//обработка внутри write;
				}
				_lvl++;
				continue;
			}
			if (tmp[_lvl][0] == "begin")
			{
				countB++;
				if (countB < countE)
				{
					cout << "Error " << lvl << endl;
					return 1;
				}
				_lvl++;
				continue;
			}
			if (tmp[_lvl][0] == "end")
			{
				countE++;
				if (countB < countE)
				{
					cout << "Error " << _lvl << endl;
					return 1;
				}
				_lvl++;
				continue;
			}
			if (tmp[_lvl][0] == "if")
			{
				if (tmp[_lvl][1] != "(" || tmp[_lvl][tmp[_lvl].size() - 2] != ")")
				{
					cout << "" << endl;
					return 1;
				}
			}
		}
	}
	void Read(string progway)
	{
		ifstream fin;
		tmp.clear();
		fin.open(progway);
		if (!fin.is_open())
			cout << "Ошибка открытия";
		else
			while (!fin.eof())
			{
				string str = "";
				getline(fin, str);
				prog.push_back(str);
			}
		fin.close();
		for (auto p : prog)
			tmp.push_back(SeparStr(p));
	}
	int Checksynt()
	{
		if (tmp[0][0] != "program" || tmp[0][2] != ";" || tmp[0].size() > 3)
		{
			cout << "Ошибка в " << lvl << "строке";
		}
		lvl++;
		if (tmp[tmp.size()][0] != "end.")
		{
			cout << "Error " << tmp.size();
			return 1;
		}
		if (tmp[lvl][0] == "const")
		{
			if (tmp[lvl].size() != 1)
				cout << "Ошибка в " << lvl << "строке." << endl;
			lvl++;
			while ((tmp[lvl][0] != "begin") || (tmp[lvl][0] != "var"))
			{
				if (tmp[lvl][1] != ":")
				{
					cout << "Ошибка в " << lvl << "строке." << endl;
					return 1;
				}
				if (tmp[lvl][2] != "integer")
					if (tmp[lvl][2] != "double")
					{
						cout << "Ошибка в " << lvl << "строке." << endl;
						return 1;
					}
				if (tmp[lvl][3] != "=")
				{
					cout << "Ошибка в " << lvl << "строке." << endl;
					return 1;
				}
				if (tmp[lvl][4] == ";" || tmp[lvl][5] != ";")
				{
					cout << "Ошибка в " << lvl << "строке." << endl;
					return 1;
				}
				if (tmp[lvl][2] == "integer")
				{
					Var<int> val;
					val.sconst = true;
					val.value = stoi(tmp[lvl][4]);
					varint.Insert(val, tmp[lvl][0]);
				}
				else
				{
					Var<double> val1;
					val1.sconst = true;
					val1.value = stod(tmp[lvl][4]);
					vardob.Insert(val1, tmp[lvl][0]);
				}
				lvl++;
			}
		}
		if (tmp[lvl][0] == "var")
		{
			if (tmp[lvl].size() != 1)
			{
				cout << "Ошибка в " << lvl << "строке." << endl;
			}
			lvl++;
			while (tmp[lvl][0] != "begin")
			{
				vector<string> vartm;
				int countсomma = 0;
				int i = 0;
				if (tmp[1][tmp[1].size() - 1] != ";")
					cout << "Ошибка в " << lvl << "строке, пропущена \";\".";
				lvl++;
				while (i < tmp[1].size() && tmp[1][i] != ":")
				{
					if (tmp[1][i] != ",")
						vartm.push_back(tmp[1][i]);
					else
						countсomma++;
					i++;
				}
				if (tmp[1][i] != ":")
					cout << "Ошибка в " << lvl << "строке, пропущено \":\".";
				if (countсomma > vartm.size() - 1)
					cout << "Ошибка в " << lvl << "строке, слишком много ,";
				if (tmp[1][tmp[1].size() - 2] != "integer")
					if (tmp[1][tmp[1].size() - 2] != "double")
						cout << "Ошибка в " << lvl << "строке, неизвестный тип данных.";
				if (tmp[lvl][tmp[1].size() - 2] == "integer")
				{
					Var<int> val;
					for (auto k : vartm)
						varint.Insert(val, k);
				}
				else
				{
					Var<double> val1;
					for (auto k : vartm)
						vardob.Insert(val1, k);
				}
				lvl++;
			}
		}
		if (tmp[lvl].size() > 1)
		{
			cout << "Ошибка в " << lvl << "строке.";
			return 1;
		}
		lvl++;
		Begin(lvl);
	}
	void confprog()
	{
		vector<string> tmp;
		int nstr = 1;
		string str, str1 = "";
		if (prog.size() == 0)
			cout << "Empty File";
		str = prog[0];
		for (int i = 0; i < str.size(); i++)
		{
			//if(str[i]<'a'||str[i]>'Z')
			if (str[i] != ' ' && str[i] != ';')
				str1 += str[i];
			else
			{
				if (str[i] == ' ')
				{
					tmp.push_back(str1);
					str1 = "";
				}
				else
				{
					str = str[i];
					tmp.push_back(str1);
					tmp.push_back(str);
					str1 = "";
				}
			}
		}
		if (tmp.size() > 3 || tmp[0] != "program" || tmp[2] != ";")
			cout << "Ошибка в строке " << nstr;
		//	if pFirst

	}
public:
	void Start(string Program)
	{

	}
};