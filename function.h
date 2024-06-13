#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <fstream>


void scytale(string& password);
void affin(string& password);
void elgamal(string& password);
void writeToFile(const string& filename, const string& content);
string readFromFile(const string& filename);