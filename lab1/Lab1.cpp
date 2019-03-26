#include "pch.h"
#include <iostream>
#include <cstring>
#include <Windows.h>
#include "Table.h"
#include "polinom.h"

using namespace std;

void WriteMenu()
{
	cout << "Выбереите действие:\n1.Добавить полином\n2.Удалить полином\n3.Выбрать таблицу для показа\n4.Показать таблицу\n5.Найти полином\n6.Произвести вычисления\n7.Выход\n";
}
int main()
{
	TableLine<TPolinom>  table1;
	TableSort<TPolinom>  table2;
	TableList<TPolinom>  table3;
	AVL_tree<TPolinom>   table4;
	HashTable<TPolinom>  table5;
	Hash_Table<TPolinom> table6;
	int idtab = 1;
	string polinom;
	int key;
	TPolinom pol;
	int flag = 0;
	while (flag != 7)
	{
		WriteMenu();
		cin >> flag;
		switch (flag) {
		case 1:
			system("cls");
			cout << "Введите имя полинома: ";
			cin >> key;
			cout << endl;
			cout << "Введите полином: ";
			cin >> polinom;
			cout << endl;
			pol.SetPolinom(polinom);
			table1.Insert(pol, key);
			table2.Insert(pol, key);
			table3.Insert(pol, key);
			//table4.Insert(pol, key);
			table5.Insert(pol, key);
			table6.Insert(pol, key);
			break;
		case 2:
			system("cls");
			cout << "Введите имя полинома: ";
			cin >> key;
			cout << endl;
			pol.SetPolinom(polinom);
			try {
				table1.Delete(key);
				table2.Delete(key);
				table3.Delete(key);
				//table4.Delete(key);
				table5.Delete(key);
				table6.Delete(key);
			}
			catch (string t) {
				cout << t << endl;
			}
			break;
		case 3:
			system("cls");
			int i;
			cout << "Введите тип:\n1.Линейная на массиве\n2.Отсортированная на массиве\n3.На списке\n4.Дерево\n5.Хэш-таблица(цепочки)\n6.Хэш-таблица()" << endl;
			cin >> i;
			switch (i)
			{
			case 1: idtab = 1; break;
			case 2: idtab = 2; break;
			case 3: idtab = 3; break;
			case 4: idtab = 4; break;
			case 5: idtab = 5; break;
			case 6: idtab = 6; break;
			default:cout << "Указанный тип не найден."; break;
			}
			break;
		case 4:
			switch (idtab) {
			case 1: table1.PrintTable(); break;
			case 2: table2.PrintTable(); break;
			/*case 3: table3.PrintTable(); break;
			case 4: table4.PrintTable(); break;
			case 5: table5.PrintTable(); break;
			case 6: table6.PrintTable(); break;*/
			}
		case 5:
			system("cls");
			cout << "Введите id полинома: ";
			cin >> key;
			try {
				switch (idtab) {
				case 1: pol = table1.Search(key); break;
				case 2: pol = table2.Search(key); break;
				case 3: pol = table3.Search(key); break;
				case 4: pol = table4.SearchByKey(key); break;
				case 5: pol = table5.Search(key); break;
				case 6: pol = table6.Search(key); break;
				}
			}
			catch (string str)
			{
				cout << str;
				break;
			}
			cout << pol;
			break;
		case 6:
			break;
		case 7: flag = 7; break;
		default:
			cout << "Неверно введена команда" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}
