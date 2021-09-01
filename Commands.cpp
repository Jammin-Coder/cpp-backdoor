#include "utils.hpp"


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


class Commands
{
public:
	std::string m_cwd;
	
	Commands()
	{
		std::cout << "[+] Initialized working directory." << std::endl;
		m_cwd = cmd_output("pwd");
	}
	
	std::string pwd()
	{
		return m_cwd;
	}
	
	std::string cd(std::string path)
	{
		if (path != "")
		{
			if (path[0] == '/')
			{
				m_cwd = path;
			}
			else
			{
				m_cwd += "/" + path;
			}
			
			std::string command = "cd" + m_cwd;
			
			cmd_output(command);
			return "[+] Changed directory to " + m_cwd + "\n";
		}
		else 
		{
			return "[-] No directory specified\n";
		}
	}
	
	std::string ls(std::string args)
	{
		return cmd_output("ls" + args);
	}
	
};




