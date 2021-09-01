#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <array>


std::string cmd_output(std::string command)
{
	/*
	This function is credited to Stack-overflow user John Smith.
	Here's his code https://stackoverflow.com/a/44611186
	*/
	std::array<char, sizeof(command)> buffer;
	std::string result;
	FILE* pipe = popen(command.c_str(), "r");

	if (!pipe)
    {
        std::cerr << "Couldn't start command." << std::endl;
        return 0;
    }

	while (fgets(buffer.data(), sizeof(command), pipe) != NULL)
	{
    //	std::cout << "DATA >> " << "'" << buffer.data() << "'" << std::endl;
        result += buffer.data();
    }
    pclose(pipe);
    return result;
}


