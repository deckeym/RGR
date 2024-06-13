#include <iostream>
#include <string>
#include <fstream>
#include "function.h"
extern const char* SYSTEM_CLEAR;
using namespace std;

string code(const string& text, int addKey, int multKey)
{
    string encoded;
    for (int i = 0; i < text.length(); i++)
    {
        encoded += static_cast<char>(((static_cast<int>(text[i]) * multKey + addKey) % 256));
    }
    return encoded;
}

string decode(const string& text, int addKey, int inv)
{
    string decoded;
    for (int i = 0; i < text.length(); i++)
    {
        decoded += static_cast<char>(((static_cast<int>(text[i]) - addKey + 256) * inv) % 256);
    }
    decoded = decoded.substr(0, decoded.length() - 1);
    return decoded;
}

void affin(string& password)
{
    int addKey, multKey, inv;
    string text, userpass, fname;
    int oper, vvod;
    while (true)
    {
        try {
            cout << "Choose an operation: 1 - encryption, 2 - decryption, 3 - clear console, 0 - exit" << endl;
            cout << "Enter operation number: ";
            cin >> oper;
            if (cin.peek() != '\n' || cin.fail())
            {
                throw logic_error("You entered a string");
                cout << "Enter operation number: ";
                cin >> oper;
            }
            if (oper == 0)
            {
                break;
            }
            else if (oper == 3)
            {
                system(SYSTEM_CLEAR);
            }
            else if (oper != 1 && oper != 2)
            {
                throw logic_error("This operation is not in the list!");
            }
            else if (oper == 1)
            {
                cout << "Enter password: ";
                cin >> userpass;
                if (userpass != password)
                {
                    throw logic_error("Invalid password");
                }
                cout << "Choose input: 1 - from console, 2 - from file" << endl;
                cout << "Enter operation number: ";
                cin >> vvod;
                if (cin.peek() != '\n' || cin.fail())
                {
                    throw logic_error("You entered a string");
                }
                cin.ignore(256, '\n');
                if (vvod == 1)
                {
                    cout << "Enter text: ";
                    getline(cin, text);

                    writeToFile("plaintext.txt", text);

                    cout << "Enter additive key: ";
                    cin >> addKey;
                    while (cin.fail())
                    {
                        throw logic_error("You entered a string");
                    }
                    cin.ignore(256,'\n');

                    if (addKey == 0)
                    {
                        cout << "No shift will be performed" << endl;
                        return;
                    }

                    if (addKey < 0)
                    {
                        addKey = addKey % 256;
                    }

                    bool a = true;
                    while (a)
                    {
                        cout << "Enter multiplicative key: ";
                        cin >> multKey;
                        while (cin.fail())
                        {
                            throw logic_error("You entered a string");
                        }
                        cin.ignore();

                        if (multKey < 0 || multKey >= 256)
                        {
                            multKey = multKey % 256;
                        }

                        for (int i = 0; i < 256; i++)
                        {
                            if (multKey * i % 256 == 1)
                            {
                                inv = i;
                                cout << "Multiplicative inverse: " << inv << endl;
                                a = false;
                                break;
                            }
                        }

                        if (a)
                        {
                            cout << "Cannot find inverse, try another key" << endl;
                        }
                    }

                    string encodedText = readFromFile("plaintext.txt");
                    string encoded = code(encodedText, addKey, multKey);

                    writeToFile("encrypted.txt", encoded);

                    cout << "Encrypted text has been written to encrypted.txt " << endl;
                }
                else if (vvod == 2)
                {
                    cin.ignore(256, '\n');
                    cout << "Enter file name: ";
                    cin >> fname;
                    cin.ignore(256, '\n');
                    string encodedText = readFromFile(fname);

                    cout << "Enter additive key: ";
                    cin >> addKey;
                    while (cin.fail())
                    {
                        throw logic_error("You entered a string");
                    }
                    cin.ignore();

                    if (addKey == 0)
                    {
                        cout << "No shift will be performed" << endl;
                        return;
                    }

                    if (addKey < 0)
                    {
                        addKey = addKey % 256;
                    }

                    bool a = true;
                    while (a)
                    {
                        cout << "Enter multiplicative key: ";
                        cin >> multKey;
                        while (cin.fail())
                        {
                            throw logic_error("You entered a string");
                        }
                        cin.ignore();
                       
                        if (multKey < 0 || multKey >= 256)
                        {
                            multKey = multKey % 256;
                        }

                        for (int i = 0; i < 256; i++)
                        {
                            if (multKey * i % 256 == 1)
                            {
                                inv = i;
                                cout << "Multiplicative inverse: " << inv << endl;
                                a = false;
                                break;
                            }
                        }

                        if (a)
                        {
                            cout << "Cannot find inverse, try another key" << endl;
                        }
                    }

                    
                    string encoded = code(encodedText, addKey, multKey);

                    writeToFile("encrypted.txt", encoded);

                    cout << "Encrypted text has been written to encrypted.txt " << endl;
                }
            }
           
            else if (oper == 2)
            {
                cout << "Enter password: ";
                cin >> userpass;
                if (userpass != password)
                {
                    throw logic_error("Invalid password");
                }

                string encodedText = readFromFile("encrypted.txt");
                string decoded = decode(encodedText, addKey, inv);
                writeToFile("decrypted.txt", decoded);

                cout << "Decrypted text has been written to decrypted.txt: " << decoded << endl;
            }
        }
        catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(256, '\n');
        }
    }
}
