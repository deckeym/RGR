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

uint64_t mod(uint64_t g, uint64_t x, uint64_t p, uint64_t y);

uint64_t nod(uint64_t p, uint64_t g);

bool prost(uint64_t x);

bool getValidLongLongInput(uint64_t &value);

void encryptDecryptMessage();

void clearConsole();

void elgamal(string& password);
// эль - гамаля

void scytale(string& password);

void affin(string& password);

void elgamal(string& password);

void writeToFile(const string& filename, const string& content);

string readFromFile(const string& filename);