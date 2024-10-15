#include "../include/client.h"

Client::Client(string username)
{
    username = username;
}

void Client::initializeClient()
{
    wsaerr = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaerr != NO_ERROR)
    {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    if ((client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR)
    {
        perror("Failed creating the client socket");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void Client::connectToServer(char *ip_addr, int port, string password)
{
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    server_addr.sin_port = htons(port);
    if (connect(client_fd, (SOCKADDR *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        perror("Failed to connect to server");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}