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
	cout << "������� ������ ��� ����� � �������: ";
	getline(cin, userpasssys);
	while (userpasssys != adminpass)
	{
		cout << "�������� ������!"<<endl;
		cout << "������� ������ ��� ����� � �������: ";
		getline(cin, userpasssys);
	}
	system(SYSTEM_CLEAR);
		while (true)
		{
			try
			{
				system(SYSTEM_CLEAR);
				cout << "------------------����------------------" << endl;
				cout <<"1. ���� �������" << endl;
				cout << "2. ���� ��� - ������" << endl;
				cout << "3. ���� ��������" << endl;
				cout << "4. �����" << endl;
				cout << "������� ����� �����: ";
				cin >> choice;
				if (choice != '1' && choice != '2' && choice != '3' && choice != '4')
				{
					throw logic_error("����� �������� ��� � ������");
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
				cerr << "������: " << e.what()<<endl;
				cin.clear();
				cin.ignore(256, '\n');
			}
		}
	}