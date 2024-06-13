#include "elgamal.h"

long long int mod(long long int g, long long x, long long p, long long y) {
    long long res = 1;
    if (g % p == 0) {
        return 0;
    }

    x = x % y;

    if (x % y == 0) {
        return 1;
    } else {
        for (int i = 1; i <= x; i++) {
            res = (res * g) % p;
        }
    }
    return res;
}

long long nod(long long p, long long g) {
    while (p > 0 && g > 0) {
        if (p > g)
            p %= g;
        else
            g %= p;
    }
    return p + g;
}

bool prost(long long x) {
    if (x < 2) {
        return false;
    }
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            return false;
        }
    }
    return true;
}

bool getValidLongLongInput(long long &value) {
    string input;
    cin >> input;
    try {
        value = stoll(input);
    } catch (invalid_argument &e) {
        cout << "Ошибка: Введите целое число.\n";
        return false;
    } catch (out_of_range &e) {
        cout << "Ошибка: Введенное число вне допустимого диапазона.\n";
        return false;
    }
    return true;
}

void encryptDecryptMessage() {
    long long p, g, xa, xb;
    long long Ya, Yb, r, e, m;
    srand(time(0));
    p = 1 + rand() % 100000000;
    g = 1 + rand() % (p - 1);
    while (!prost(p) || !prost(g) || nod(p, g) != 1) {
        p = 1 + rand() % 100000000;
        g = 1 + rand() % (p - 1);
    }
    cout << "G = " << g << " P = " << p << endl;

    while (true) {
        cout << "Введите ключ A: ";
        if (getValidLongLongInput(xa)) {
            break;
        }
    }

    while (true) {
        cout << "Введите ключ B: ";
        if (getValidLongLongInput(xb)) {
            break;
        }
    }

    Ya = mod(g, xa, p, p - 1); // вычисление открытого ключа
    cout << "Открытый ключ A: " << Ya << endl;

    Yb = mod(g, xb, p, p - 1); // вычисление открытого ключа
    cout << "Открытый ключ B: " << Yb << endl;

    string M, filename;
    cout << "Введите сообщение (английские буквы или цифры): ";
    cin.ignore();
    getline(cin, M);

    vector<int> shif;
    vector<int> deshif;

    for (char c : M) {
        shif.push_back(static_cast<int>(c));
    }

    long long K;
    for (long long i = 2; i < p - 1; i++) {
        if (nod(i, p - 1) == 1) {
            K = i;
            break;
        }
    }
    r = mod(g, K, p, p - 1);
    cout << "r = " << r << endl;

    for (int i = 0; i < shif.size(); i++) { // шифрование
        e = ((shif[i] % p) * (mod(Yb, K, p, p - 1))) % p;
        deshif.push_back(e);
    }

    filename = "encrypted_message.txt";
    ofstream file(filename);
    if (file.is_open()) {
        for (int i : deshif) {
            file << i << " ";
        }
        file.close();
        cout << "Зашифрованное сообщение записано в " << filename << endl;
    } else {
        cout << "Не удалось открыть файл для записи.\n";
        return;
    }

    string encrypted_message;
    ifstream infile(filename);
    if (infile.is_open()) {
        getline(infile, encrypted_message, '\0');
        infile.close();
    } else {
        cout << "Не удалось открыть файл для чтения.\n";
        return;
    }

    deshif.clear();
    size_t pos = 0;
    while ((pos = encrypted_message.find(" ")) != string::npos) {
        deshif.push_back(stoi(encrypted_message.substr(0, pos)));
        encrypted_message.erase(0, pos + 1);
    }
    if (!encrypted_message.empty()) {
        deshif.push_back(stoi(encrypted_message));
    }

    filename = "decrypted_message.txt";
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (int i = 0; i < deshif.size(); i++) { // дешифрование
            m = ((deshif[i] % p) * mod(r, (p - 1 - xb), p, p - 1)) % p;
            outfile << static_cast<char>(m);
        }
        outfile.close();
        cout << "Расшифрованное сообщение записано в " << filename << endl;
    } else {
        cout << "Не удалось открыть файл для записи.\n";
    }
}

void clearConsole() {
    cout << "\x1B[2J\x1B[H";
}

void elgamal(string& password) {
    string userpass;
    do{
    cout << "Введите пароль: ";
    cin >> userpass;
    if (password == userpass)
    {   
        clearConsole();
        break;
    }
    else {
        cout << endl << "Неверный пароль!" << endl;
    }

    } while(true);
    
        int choice;
        do {
            cout << "Выберите операцию:\n";
            cout << "1. Реализация алгоритма\n";
            cout << "2. Очистить консоль\n";
            cout << "3. Выход\n";
            cout << "Ваш выбор: ";
            cin >> choice;

            switch (choice) {
            case 1:
                encryptDecryptMessage();
                break;
            case 2:
                clearConsole();
                break;
            case 3:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
                break;
            }
        } while (choice != 3);
}