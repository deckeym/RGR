#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "function.h"

using namespace std;
extern const char* SYSTEM_CLEAR;



// ������� �������� ������������� �����
bool exist(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// ������� ������ ������ � ����
void WriteIntoFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        cout << "����� ������� ������� � ���� " << filename << endl;
    } else {
        throw logic_error("���������� ������� ���� ��� ������: " + filename);
    }
}

// ������� ������ ������ �� �����
string ReadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        file.close();
        return content;
    } else {
        throw logic_error("���������� ������� ���� ��� ������: " + filename);
    }
}

string cleanOutput(const string& output) {
	string cleanedOutput = output;
	cleanedOutput.erase(remove(cleanedOutput.begin(), cleanedOutput.end(), '_'), cleanedOutput.end());
	return cleanedOutput;
}


string encodeScytale(string& message, int diameter) {
	int length = message.length();
	int height = (length + diameter - 1) / diameter;

	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0;
	for (int j = 0; j < diameter; j++) {
		for (int i = 0; i < height; i++) {
			if (index < length) {
				if (message[index] == '\n') {
					grid[i][j] = '@'; 
				}
				else {
					grid[i][j] = message[index];
				}
				index++;
			}
		}
	}

	string encodedMessage = "";
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			encodedMessage += grid[i][j];
		}
	}
	encodedMessage = encodedMessage.substr(0, encodedMessage.length() - 1);
	return encodedMessage;
}

string decodeScytale(string& encodedMessage, int diameter) {
	int length = encodedMessage.length();
	int height = (length + diameter - 1) / diameter;

	vector<vector<char>> grid(height, vector<char>(diameter, '_'));

	int index = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < diameter; j++) {
			if (index < length) {
				grid[i][j] = encodedMessage[index++];
			}
		}
	}

	string decodedMessage = "";
	for (int j = 0; j < diameter; j++) {
		for (int i = 0; i < height; i++) {
			if (grid[i][j] == '@') { 
				decodedMessage += '\n'; 
			}
			else {
				decodedMessage += grid[i][j];
			}
		}
	}
	decodedMessage = decodedMessage.substr(0, decodedMessage.length() - 1);
	return decodedMessage;
}


void scytale(string& password)
{
    string userpass;
    do{
    cout << "������� ������: ";
    cin >> userpass;
    if (password == userpass)
    {   
        break;
    }
    else {
        cout << endl << "�������� ������!" << endl;
    }

    } while(true);
    
	system("chcp 1251 > nul");
	int pick, diametr1, diametr2, pickencode;
	string pass1, pass2, message, filename;
	while (true) {
		try {
			cout << "���� �������" << endl
				<< "�������� ��������:" << endl
				<< "1.�����������" << endl
				<< "2.�����������" << endl
				<< "3.����� � ������� ����" << endl;
			cin >> pick;
			while (cin.fail() || cin.peek()!='\n') {
				throw logic_error("������ �����!");
				cin >> pick;
			}
			if (pick!= 1 && pick != 2 && pick != 3) {
				throw logic_error("�� ����� �������� �������!");
			}
			if (pick == 1) {
				cout << "������� ������ �����������" << endl;
				cin >> pass1;
				if (pass1 == password) {
					cout << "�������� ��������:" << endl
						<< "1.������ ����� � �������" << endl
						<< "2.������� ����� �� �����" << endl;
					cin >> pickencode;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("������ �����!");
					}
					if (pickencode != 1 && pickencode != 2) {
						throw logic_error("�� ����� �������� �������!");
					}
					if (pickencode == 1) {
						cout << "������� �����: ";
						cin.ignore();
						getline(cin, message);
						cout << "������� ������� �������: ";
						cin >> diametr1;
						if (cin.fail() || cin.peek() != '\n') {
							throw logic_error("�� ������� �� �����!");
						}
						WriteIntoFile("s�ytale.txt", message);
						string encodedText2 = ReadFromFile("scytale.txt");
						string encoded2 = encodeScytale(encodedText2, diametr1);
						string cleanedEncoded2 = cleanOutput(encoded2);
						
						WriteIntoFile("decoded.txt", encoded2);
					}
					if (pickencode == 2) {
						cout << "������� �������� ����� � �����������:";
						cin >> filename;
						if (exist(filename) == false)
							throw logic_error("������ ����� �� ���������� ��� ��� ���������� �������!");
						cout << "������� ������� �������: ";
						cin >> diametr2;
						if (cin.fail() || cin.peek() != '\n') {
							throw logic_error("�� ������� �� �����!");
						}
						string encodedText1 = ReadFromFile(filename);
						string encoded1 = encodeScytale(encodedText1, diametr2);
						string cleanedEncoded2 = cleanOutput(encoded1);
						
						WriteIntoFile("decoded.txt", encoded1);
					}

				}
				else {
					throw logic_error("�������� ������ �����������");
				}
			}
			else if (pick == 2) {
				cout << "������� ������ �������������:" << endl;
				cin >> pass2;
				if (pass2 == password) {
					cout << "������� ������� �������: ";
					cin >> diametr2;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("�� ������� �� �����!");
					}
					string encodedText1 = ReadFromFile("decoded.txt");
					string decoded1 = decodeScytale(encodedText1, diametr2);
					string cleanedDecoded1 = cleanOutput(decoded1);
					WriteIntoFile("decoded1.txt", cleanedDecoded1);
					cout << "�������������� �����: " << cleanedDecoded1 << endl;
				}
				else {
					throw logic_error("�������� ������ �������������");
				}
			}
			else if (pick == 3) {
				system(SYSTEM_CLEAR);
				break;
			}
		}
		catch (const exception& e) {
			cerr << e.what() << endl;
			cin.clear();
			cin.ignore(256, '\n');
		}
	}
}