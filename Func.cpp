#include "Func.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <future>

// debug
unsigned long* pos_el_1 = nullptr;
unsigned long* pos_el_2 = nullptr;
//

extern const char HighCh[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
extern const char LowCh[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
extern const char SpecCh[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', ';', ':', ',', '.', '/', '?', '\\', '|', '`', '~', '[', ']', '{', '}' };
extern const char NumCh[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

bool* UserStop = nullptr;

static unsigned long max_to_write_b = 0xFFFFFFFF;
static unsigned long writen_b = 0;
unsigned long* pos = nullptr;
std::ofstream* m_file = nullptr;

unsigned long LenBY = 0;
unsigned long LenTO = 0;

bool UseNum_m = false;
bool UseHigh_m = false;
bool UseLow_m = false;
bool UseSpec_m = false;

bool SetMax = false;

unsigned long count_of_commands_m = 0;
std::string* comm_list_m = nullptr;
bool run_comm_m = false;
bool SaveFreeze_m = false;

unsigned long STRINGLEN = 0;

void PauseInterface()
{
	(*m_file).close();
	if (SaveFreeze_m == true)
		writefreeze(&UseNum_m, &UseHigh_m, &UseLow_m, &UseSpec_m, &count_of_commands_m, comm_list_m, &SetMax, &max_to_write_b, &LenBY, &LenTO, &STRINGLEN, pos);
	for (unsigned long i = 0; i < count_of_commands_m; ++i)
		system(comm_list_m[i].c_str());
	(*m_file).open("out.txt", std::ios::out | std::ios::trunc);
	if (!m_file->is_open())
		throw "Haha";
}

void PauseInterface(int o)
{
	(*m_file).close();
	for (unsigned long i = 0; i < count_of_commands_m; ++i)
		system(comm_list_m[i].c_str());
}

void print(char* arr, unsigned  int size)
{
	for (unsigned int i = 0; i < size; ++i)
		(*m_file) << arr[i];
	(*m_file) << std::endl;

	writen_b = m_file->tellp();
	if (writen_b >= max_to_write_b)
	{
		PauseInterface();
		writen_b -= max_to_write_b;
	}

	if ((*UserStop) == true)
		exit(0);
}

void gen(char* string, unsigned long string_len, char* arr, unsigned int arr_size, unsigned int index)
{
	for (; pos[index] < arr_size; pos[index]++)
	{
		string[index] = arr[pos[index]];
		if ((index + 1) < string_len)
			gen(string, string_len, arr, arr_size, (index + 1));
		else
		{
			print(string, string_len);
		}
	}
	pos[index] = 0;
}

void GenPass(unsigned long by, unsigned long to, std::ofstream* file, bool useHigh, bool useLow, bool useSpec, bool useNum, bool RunComm, std::string* commands, unsigned long CommCount, bool setMax, unsigned long MaxSize, bool savefreeze, bool* userStop, unsigned long** poses)
{

	if (RunComm == true)
	{
		count_of_commands_m = CommCount;
		comm_list_m = new std::string[count_of_commands_m];
		for(unsigned long i = 0; i < count_of_commands_m;  ++i)
			comm_list_m[i] = commands[i];
	}

	UserStop = userStop;


	LenBY = by;
	LenTO = to;

	UseHigh_m = useHigh;
	UseLow_m = useLow;
	UseNum_m = useNum;
	UseSpec_m = useSpec;

	SaveFreeze_m = savefreeze;
	SetMax = setMax;
	if(setMax == true)
		max_to_write_b = MaxSize;
	writen_b = 0;
	m_file = file;

	// Çäåñü ñîçäà¸òñÿ char* List, cîäåðæàùèé ñèìâîëû; size ñîäåðæèò ðàçìåð
	unsigned long size(0);

	if (useHigh == true)
		size += 26;
	if (useLow == true)
		size += 26;
	if (useSpec == true)
		size += 28;
	if (useNum == true)
		size += 10;

	char* List = new char[size];

	unsigned long iii = 0;

	if (useNum == true)
	{
		for (unsigned long i = 0; i < 10; ++i, ++iii)
			List[iii] = NumCh[i];
	}
	if (useHigh == true)
	{
		for (unsigned long i = 0; i < 26; ++i, ++iii)
			List[iii] = HighCh[i];
		
	}
	if (useLow == true)
	{
		for (unsigned long i = 0; i < 26; ++i, ++iii)
			List[iii] = LowCh[i];
	}
	if (useSpec == true)
	{
		for (unsigned long i = 0; i < 28; ++i, ++iii)
			List[iii] = SpecCh[i];
	}
	// ...
	
	// by < to
	if (by > to)
	{
		by = by ^ to;
		to = by ^ to;
		by = by ^ to;
	}
	// ...


	char* string = new char[to];
	

	for (unsigned long i = 0; i < to; i++)
	{
		string[i] = 0x00;
	}

	pos = new unsigned long[by];
	if (poses != nullptr)
		for (unsigned long i = 0; i < by; ++i)
			pos[i] = (*poses)[i];
	else
		for (unsigned long i = 0; i < by; ++i)
			pos[i] = 0;
	for (unsigned long i = by; i <= to; ++i)
	{
		STRINGLEN = i;
		gen(string, i, List, size);

		delete[] pos;
		pos = new unsigned long[i + 1];

		for (unsigned long iii = 0; iii < (i + 1); ++iii)
			pos[iii] = 0;
	}

	PauseInterface(1);
	std::remove("out.txt");

	delete[] string;
	delete[] List;
}
