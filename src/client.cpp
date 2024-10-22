#include "../include/client.h"

Client::Client(string username)
{
    username = username;
}

Client::~Client()
{
    closesocket(client_fd);
    WSACleanup();
}

void Client::initialize()
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

int Client::connectServer(char *ip_addr, int port, string password)
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_addr);
    server_addr.sin_port = htons(port);
    if (connect(client_fd, (SOCKADDR *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        perror("Failed to connect to server");
        // WSACleanup();
        // exit(EXIT_FAILURE);
        return 1;
    }
    return 0;
}

int Client::disconnect()
{
    if ((shutdown(client_fd, SD_SEND)) == SOCKET_ERROR)
    {
        perror("Shutdown failed");
        closesocket(client_fd);
        WSACleanup();
        return 1;
    }
    return 0;
}

int Client::sendMessage(char *msg)
{
    if ((send(client_fd, msg, (int)strlen(msg), 0)) == SOCKET_ERROR)
    {
        perror("Failed to send message");
        return 1;
    }

    return 0;
}