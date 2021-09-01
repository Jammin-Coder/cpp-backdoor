#include "Commands.cpp"


class ExecuteCommand
{
public:
	Commands execute = Commands();;
	
	std::string get_args(std::vector<std::string> cmd)
	{
		std::string args;
		for(int i = 1; i < cmd.size(); i++)
		{
			args += " " + cmd.at(i);
		}
		return args;
	}
	
	std::string exec(std::string input_cmd)
	{
		
		std::vector<std::string> cmd = split(input_cmd, " ");
		std::cout << "CMD '" << cmd.at(0) << "'" << std::endl;
		std::string args = get_args(cmd);
		std::cout << "ARGS " << args << std::endl;
		
		
		// Print working directory
		if (cmd.at(0) == "pwd")
		{
			// returns current working directory
			return execute.pwd();
		}
		
		if (cmd.at(0) == "cd")
		{
			return execute.cd(args);
		}
		
		if (cmd.at(0) == "ls")
		{
			return execute.ls(args);
		}
		
		return "[-] Unknown command: " + cmd.at(0) + "\n";
	}
};
