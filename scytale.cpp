#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "function.h"

using namespace std;
extern const char* SYSTEM_CLEAR;



// Функция проверки существования файла
bool exist(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Функция записи текста в файл
void WriteIntoFile(const string& filename, const string& content) {
    ofstream file(filename);
    if (file.is_open()) {
        file << content;
        file.close();
        cout << "Текст успешно записан в файл " << filename << endl;
    } else {
        throw logic_error("Невозможно открыть файл для записи: " + filename);
    }
}

// Функция чтения текста из файла
string ReadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
        file.close();
        return content;
    } else {
        throw logic_error("Невозможно открыть файл для чтения: " + filename);
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
    cout << "Введите пароль: ";
    cin >> userpass;
    if (password == userpass)
    {   
        break;
    }
    else {
        cout << endl << "Неверный пароль!" << endl;
    }

    } while(true);
    
	system("chcp 1251 > nul");
	int pick, diametr1, diametr2, pickencode;
	string pass1, pass2, message, filename;
	while (true) {
		try {
			cout << "Шифр Скитала" << endl
				<< "Выберите действие:" << endl
				<< "1.Зашифровать" << endl
				<< "2.Дешифровать" << endl
				<< "3.Выход в главное меню" << endl;
			cin >> pick;
			while (cin.fail() || cin.peek()!='\n') {
				throw logic_error("Ошибка ввода!");
				cin >> pick;
			}
			if (pick!= 1 && pick != 2 && pick != 3) {
				throw logic_error("Вы ввели неверную команду!");
			}
			if (pick == 1) {
				cout << "Введите пароль кодирования" << endl;
				cin >> pass1;
				if (pass1 == password) {
					cout << "Выберите действие:" << endl
						<< "1.Ввести текст с консоли" << endl
						<< "2.Считать текст из файла" << endl;
					cin >> pickencode;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("ошибка ввода!");
					}
					if (pickencode != 1 && pickencode != 2) {
						throw logic_error("Вы ввели неверную команду!");
					}
					if (pickencode == 1) {
						cout << "Введите текст: ";
						cin.ignore();
						getline(cin, message);
						cout << "Введите диаметр скитала: ";
						cin >> diametr1;
						if (cin.fail() || cin.peek() != '\n') {
							throw logic_error("Вы вводите не цифру!");
						}
						WriteIntoFile("sсytale.txt", message);
						string encodedText2 = ReadFromFile("scytale.txt");
						string encoded2 = encodeScytale(encodedText2, diametr1);
						string cleanedEncoded2 = cleanOutput(encoded2);
						
						WriteIntoFile("decoded.txt", encoded2);
					}
					if (pickencode == 2) {
						cout << "Введите название файла с расширением:";
						cin >> filename;
						if (exist(filename) == false)
							throw logic_error("Такого файла не существует или его невозможно открыть!");
						cout << "Введите диаметр скитала: ";
						cin >> diametr2;
						if (cin.fail() || cin.peek() != '\n') {
							throw logic_error("Вы вводите не цифру!");
						}
						string encodedText1 = ReadFromFile(filename);
						string encoded1 = encodeScytale(encodedText1, diametr2);
						string cleanedEncoded2 = cleanOutput(encoded1);
						
						WriteIntoFile("decoded.txt", encoded1);
					}

				}
				else {
					throw logic_error("Неверный пароль кодирования");
				}
			}
			else if (pick == 2) {
				cout << "Введите пароль декодирования:" << endl;
				cin >> pass2;
				if (pass2 == password) {
					cout << "Введите диаметр скитала: ";
					cin >> diametr2;
					if (cin.fail() || cin.peek() != '\n') {
						throw logic_error("Вы вводите не цифру!");
					}
					string encodedText1 = ReadFromFile("decoded.txt");
					string decoded1 = decodeScytale(encodedText1, diametr2);
					string cleanedDecoded1 = cleanOutput(decoded1);
					WriteIntoFile("decoded1.txt", cleanedDecoded1);
					cout << "Расшифрованный текст: " << cleanedDecoded1 << endl;
				}
				else {
					throw logic_error("Неверный пароль декодирования");
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