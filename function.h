#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <sstream>
#include <stdexcept>

using namespace std;


extern const char* SYSTEM_CLEAR;

string cleanOutput(const string& output);

string encodeScytale(string& message, int diameter);

string decodeScytale(string& encodedMessage, int diameter);

void sсytale(string& password);

bool exist(const string& filename);

void WriteIntoFile(const string& filename, const string& content);

string ReadFromFile(const string& filename);

//Скитала

long long int mod(long long int g, long long x, long long p, long long y);

long long nod(long long p, long long g);

bool prost(long long x);

bool getValidLongLongInput(long long &value);

void encryptDecryptMessage();

void clearConsole();

void elgamal(string& password);
// ель - гамаля

void scytale(string& password);

void affin(string& password);

void elgamal(string& password);

void writeToFile(const string& filename, const string& content);

string readFromFile(const string& filename);