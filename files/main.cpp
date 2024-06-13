#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "function.h"


using namespace std;
const char* SYSTEM_CLEAR = "cls";

int main()
{
	system("chcp 1251 > nul");
	string userpass,userpasssys, password="world!", adminpass="hello";
	char choice;
	cout << "Введите пароль для входа в систему: ";
	getline(cin, userpasssys);
	while (userpasssys != adminpass)
	{
		cout << "Неверный пароль!"<<endl;
		cout << "Введите пароль для входа в систему: ";
		getline(cin, userpasssys);
	}
	system(SYSTEM_CLEAR);
		while (true)
		{
			try
			{
				system(SYSTEM_CLEAR);
				cout << "------------------МЕНЮ------------------" << endl;
				cout <<"1. Шифр Скитала" << endl;
				cout << "2. Шифр Эль - Гамаля" << endl;
				cout << "3. Шифр Аффинный" << endl;
				cout << "4. Выход" << endl;
				cout << "Введите номер шифра: ";
				cin >> choice;
				if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
				{
					throw logic_error("Такой операции нет в списке");
				}
				else if (choice == '4')
				{
					break;
				}
				switch (choice)
				{
				case '1':
				{
					system(SYSTEM_CLEAR);
					scytale(password);
					break;
				}
				case'2':
				{
					system(SYSTEM_CLEAR);
					elgamal(password);
					break;
				}
				case '3':
				{
					system(SYSTEM_CLEAR);
					affin(password);
					break;
				}
				}
			}
			catch (const exception& e)
			{
				cerr << "Ошибка: " << e.what()<<endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
		}
	}