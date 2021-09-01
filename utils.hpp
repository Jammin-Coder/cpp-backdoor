#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <array>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


std::vector<std::string> split(std::string str, std::string delimiter)
{
	std::vector<std::string> words;
	// Parsing code from Stackover flow user Vincenzo Pii
	size_t pos = 0;
	std::string token;
	while((pos = str.find(delimiter)) != std::string::npos)
	{
		token = str.substr(0, pos);
		words.push_back(token);
		str.erase(0, pos + delimiter.length());
	}
	
	words.push_back(str);
	return words;
}



