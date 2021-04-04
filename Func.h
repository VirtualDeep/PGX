#pragma once
#include <fstream>
#include <string>

void outfreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string* commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long* positions);
void PauseInterface();
void testfreeze();
void writefreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string* commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long* positions);
void readfreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string** commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long** positions);
void getComm();
unsigned long getL(unsigned long from, unsigned long to);
void base(bool* UserStop);
void print(char* arr, unsigned int size);
void gen(char* string, unsigned long string_len, char* arr, unsigned int arr_size, unsigned int index = 0);
void GenPass(unsigned long by, unsigned long to, std::ofstream* file, bool useHigh, bool useLow, bool useSpec, bool useNum, bool RunComm, std::string* commands, unsigned long CommCount, bool setMax, unsigned long MaxSize, bool savefreeze, bool* userStop, unsigned long** poses = nullptr);