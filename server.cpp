/*
*   The socket programming is from Sloan Kelly's Youtube Video:
*   https://www.youtube.com/watch?v=cNdlrbZSkyQ
*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>


template<typename T>
void log(T mess)
{
    std::cout << mess << std::endl;
}

int PORT = 54000;
const char* IP = "0.0.0.0";

int main()
{
    // Create socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        std::cout << "[-] Can't create socket" << std::endl;
        return -1;
    }
    
    // Bind socket to port / IP
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, IP, (sockaddr*)&hint.sin_addr);
    
    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1)
    {
        std::cout << "[-] Can't bind to IP/port" << std::endl;
        return -2;
    }
    
    if (listen(listening, SOMAXCONN) == -1)
    {
        std::cout << "[-] Can't listen" << std::endl;
        return -3;
    }
    
    
    /*********************  LET CLIENT CONNECT  *********************/
    
    // Accept call
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char srv[NI_MAXSERV];
    
    // The program halts here and waits for a client to connect
    std::cout << "[+] Listening on " << IP << " on port " << PORT << std::endl; 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
    
    // Something went wrong.
    if (clientSocket == -1){
        std::cout << "[-] Problem with client" << std::endl;
        return -4;
    }
    
    // Close socket
    close(listening);
    /*****************************************************************/
    // If this point is reached, the client is now connected.
    
    memset(host, 0, NI_MAXHOST);
    memset(srv, 0, NI_MAXSERV);
    
    int result = getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, srv, NI_MAXSERV, 0);
    
    if (result)
    {
        std::cout << "[+] " << host << " connected on " << srv << std::endl;
    } else 
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on " << ntohs(client.sin_port) << std::endl;    
    }
    
    int bufSize = 4096;
    char buffer[bufSize];
    while (true)
    {
        memset(buffer, 0, bufSize);
        
        std::string command;
        std::cout << "> ";
        getline(std::cin, command);
        
        // Send command
        int sendRes = send(clientSocket, command.c_str(), command.size() + 1, 0);
        
        // Reveive results
        int bytesReceived = recv(clientSocket, buffer, bufSize, 0);
        
        
        if (bytesReceived == -1)
        {
            std::cout << "[-] Connection issue" << std::endl;
            break;
        }
        
        // Display message
        if (bytesReceived == 0)
        {
            std::cout << "[+] Client disconnected" << std::endl;
            break;
        }
        
        std::string cmd_result = std::string(buffer, bytesReceived);
        std::cout << cmd_result << std::endl;
    }
    
}



