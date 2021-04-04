#include "Func.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	bool UserStop = false;
	base(&UserStop);
	std::cout << "\nFinish\n" << std::flush;
	return 0;
}