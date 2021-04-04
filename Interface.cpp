#include <iostream>
#include <string>
#include <thread>
#include "Func.h"

bool UseNum = false;
bool UseHigh = false;
bool UseLow = false;
bool UseSpec = false;

bool setmax = false;
unsigned long maxsizeoffile = 0;

bool CreateFreeze = false;

unsigned long LenFrom = 0;
unsigned long LenTo = 0;

unsigned long count_of_commands = 0;
std::string* comm_list = nullptr;
bool run_comm = false;

unsigned long* positions = nullptr;
bool get_work = false;

unsigned long NowSize_m = 0;

void getComm()
{
	std::cout << "To stop writing commands, enter \"-end\"" << std::endl;
	std::string base_string;
	std::string int_string;

	for (bool isEnd = false; !isEnd; count_of_commands++)
	{
		std::cout << "Command " << (count_of_commands + 1) << "> " << std::flush;
		std::getline(std::cin, int_string);
		if (int_string != "-end")
		{
			base_string += int_string;
			base_string += '\n';
		}
		else
			isEnd = true;
	}
	--count_of_commands;
	if (count_of_commands > 0)
		comm_list = new std::string[count_of_commands];
	else
	{
		comm_list = nullptr;
		return;
	}

	unsigned long ridden = 0;

	for (unsigned long i = 0; i < count_of_commands; i++)
	{
		for (; base_string[ridden] != '\n' ; ridden++)
		{
				comm_list[i] += base_string[ridden];
		}
		ridden++;
	}
}

unsigned long getL(unsigned long from, unsigned long to)
{
	unsigned long result = 0;
L1:
	std::cin >> result;
	if (std::cin.fail())
	{
		std::cout << "Invalid input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto L1;
	}
	if (result < from || result > to)
	{
		std::cout << "Incorrect input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto L1;
	}
	std::cin.ignore(32767, '\n');
	if (std::cin.gcount() > 1)
	{
		std::cout << "Incorrect input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto L1;
	}

	return result;
}

bool getB()
{
	bool result = false;
	char input = ' ';
B1:
	std::cin.get(input);
	if (std::cin.fail())
	{
		std::cout << "Invalid input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto B1;
	}

	std::cin.ignore(32767, '\n');
	if (std::cin.gcount() > 1)
	{
		std::cout << "Incorrect input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto B1;
	}

	if (input == '1' || input == 'y' || input == 'Y') {
		result = true;
	}
	else if (input == '0' || input == 'n' || input == 'N') {
		result = false;
	}
	else
	{
		std::cout << "Incorrect input. Please, try again" << std::endl;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
		goto B1;
	}

	return result;
}

void base(bool* UserStop)
{
	std::ofstream genPass("out.txt", std::ios::out | std::ios::trunc);
	if (!genPass)
		throw "Unable to open \"out.txt\"";
	std::cout << "Select the option:\n[1] Create new file\n[2] Load freeze-file\n[3] Exit" << std::endl;
	int DO = getL(1, 3);
	if (DO == 3)
		exit(0);
	if (DO == 1)
	{
		std::cout << "Use numbers? [y/n]: " << std::flush;
		UseNum = getB();
		std::cout << "Use high characters? [y/n]: " << std::flush;
		UseHigh = getB();
		std::cout << "Use low characters? [y/n]: " << std::flush;
		UseLow = getB();
		std::cout << "Use special characters? [y/n]: " << std::flush;
		UseSpec = getB();

		std::cout << "Enter minimum length of password (between 1 and 256): " << std::flush;
		LenFrom = getL(1, 256);
		std::cout << "Enter maximum length of password (between 1 and 256): " << std::flush;
		LenTo = getL(1, 256);

		std::cout << "Run commands after generating? [y/n]: " << std::flush;
		run_comm = getB();
		if (run_comm == true)
		{
			getComm();
		}

		std::cout << "Set max size of file? [y/n]: " << std::flush;
		setmax = getB();
		if (setmax == true)
		{
			std::cout << "Select a unit of measurement:\n[1] Byte\n[2] KByte\n[3] MByte\n[4] GByte" << std::endl;
			unsigned long Type = getL(1, 4);
			std::cout << "Enter the value (between 1 and 1000 000): " << std::flush;
			maxsizeoffile = getL(1, 1000000);
			switch (Type)
			{
			case 1:
				break;
			case 2:
				maxsizeoffile = maxsizeoffile * 1024;
				break;
			case 3:
				maxsizeoffile = maxsizeoffile * 1048576;
				break;
			case 4:
				maxsizeoffile = maxsizeoffile * 1073741824;
				break;
			}
		}

		std::cout << "Create new freeze-file? [y/n]: " << std::flush;
		CreateFreeze = getB();

		std::cout << "Continue? [y/n]: " << std::flush;
		bool con = getB();
		if (con == false)
			exit(0);
		if (CreateFreeze == true)
		{
			unsigned long lll = 0;
			writefreeze(&UseNum, &UseHigh, &UseLow, &UseSpec, &count_of_commands, comm_list, &setmax, &maxsizeoffile, &LenFrom, &LenTo, &lll, nullptr);
		}
		GenPass(LenFrom, LenTo, &genPass, UseHigh, UseLow, UseSpec, UseNum, run_comm, comm_list, count_of_commands, setmax, maxsizeoffile, CreateFreeze, UserStop);
		get_work = false;
	}
	if (DO == 2)
	{
		readfreeze(&UseNum, &UseHigh, &UseLow, &UseSpec, &count_of_commands, &comm_list, &setmax, &maxsizeoffile, &LenFrom, &LenTo, &NowSize_m, &positions);
		if (count_of_commands > 0)
			run_comm = true;
		CreateFreeze = true;
		GenPass(NowSize_m, LenTo, &genPass, UseHigh, UseLow, UseSpec, UseNum, run_comm, comm_list, count_of_commands, setmax, maxsizeoffile, CreateFreeze, UserStop, &positions);
		get_work = false;
	}
	
}