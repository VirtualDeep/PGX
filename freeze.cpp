#include "Func.h"
#include <fstream>
#include <string>
#include <iostream>

void testfreeze()
{
	std::ifstream file("freeze.txt");
	if (!file)
	{
		file.close();
		std::ofstream crfile("freeze.txt", std::ios::out);
		if (!crfile)
		{
			throw "Unable to create \"freeze.txt\"";
		}
		crfile.close();
	}
	file.close();
}

#include <sstream>

template <typename T>
inline bool FromString(const std::string& sString, T& tX)
{
    std::istringstream iStream(sString);
    return (iStream >> tX) ? true : false;
}

void outfreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string* commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long* positions)
{

    const char n{ '\n' };
    std::cout << (*UseNum) << n << (*UseHigh) << n << (*UseLow) << n << (*UseSpec) << n << (*count_of_commands) << n;
    for (unsigned long i = 0; i < (*count_of_commands); ++i)
        std::cout << commands[i] << n;

    std::cout << (*SetMaxSize) << n;
    if ((*SetMaxSize) == true)
        std::cout << (*maxSize) << n;

    std::cout << (*LenBy) << n << (*LenTo) << n << (*Size) << n;
    for (unsigned long i = 0; i < (*Size); ++i)
        std::cout << positions[i] << n;

    return;
}

void writefreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string* commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long* positions)
{
    std::ofstream freeze("freeze.txt", std::ios::out | std::ios::trunc);
    if (!freeze)
        throw "Unable to open \"freeze.txt\"";

    const char n{ '\n' };
    freeze << (*UseNum) << n << (*UseHigh) << n << (*UseLow) << n << (*UseSpec) << n << (*count_of_commands) << n;
    for (unsigned long i = 0; i < (*count_of_commands); ++i)
        freeze << commands[i] << n;

    freeze << (*SetMaxSize) << n;
    if ((*SetMaxSize) == true)
        freeze << (*maxSize) << n;

    freeze << (*LenBy) << n << (*LenTo) << n << (*Size) << n;
    for (unsigned long i = 0; i < (*Size); ++i)
        freeze << positions[i] << n;
    freeze.close();
    return;
}

void readfreeze(bool* UseNum, bool* UseHigh, bool* UseLow, bool* UseSpec, unsigned long* count_of_commands, std::string** commands, bool* SetMaxSize, unsigned long* maxSize, unsigned long* LenBy, unsigned long* LenTo, unsigned long* Size, unsigned long** positions)
{
    std::ifstream freeze("freeze.txt", std::ios::in);
    if (!freeze)
        throw "Unable to open \"freeze.txt\"";

    std::string str;
    std::getline(freeze, str);

    if (!FromString(str, (*UseNum)))
        throw "Error of convertation";

    std::getline(freeze, str);

    if (!FromString(str, (*UseHigh)))
        throw "Error of convertation";

    std::getline(freeze, str);

    if (!FromString(str, (*UseLow)))
        throw "Error of convertation";

    std::getline(freeze, str);

    if (!FromString(str, (*UseSpec)))
        throw "Error of convertation";

    std::getline(freeze, str);

    if (!FromString(str, (*count_of_commands)))
        throw "Error of convertation";

    (*commands) = new std::string[(*count_of_commands)];
    for (unsigned long i = 0; i < (*count_of_commands); ++i)
    {
        std::getline(freeze, ((*commands)[i]));
    }


    std::getline(freeze, str);

    if (!FromString(str, (*SetMaxSize))) {
        delete[] (*commands);
        throw "Error of convertation";
    }


    if ((*SetMaxSize) == true)
    {
        std::getline(freeze, str);

        if (!FromString(str, (*maxSize))) {
            delete[] (*commands);
            throw "Error of convertation";
        }

    }


    std::getline(freeze, str);

    if (!FromString(str, (*LenBy))) {
        delete[] (*commands);
        throw "Error of convertation";
    }

    std::getline(freeze, str);

    if (!FromString(str, (*LenTo))) {
        delete[] (*commands);
        throw "Error of convertation";
    }

    std::getline(freeze, str);

    if (!FromString(str, (*Size))) {
        delete[] (*commands);
        throw "Error of convertation";
    }
    (*positions) = new unsigned long[(*Size)];
    for (unsigned long i = 0; i < (*Size); ++i)
    {
        std::getline(freeze, str);

        if (!FromString(str, (*positions)[i])) {
            delete[] (*commands); 
            delete[] (*positions);
            throw "Error of convertation";
        }
    }
    freeze.close();
}