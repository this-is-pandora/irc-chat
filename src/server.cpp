#include "../include/server.h"
#include <ws2tcpip.h>
#include <functional>

Server::Server(string name, string password)
{
    name = name;
    password = password; // TODO: hash password
}

Server::~Server()
{
    WSACleanup();
    if (server_fd)
        closesocket(server_fd);
}

void Server::startServer()
{
    int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (rc != NO_ERROR)
    {
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }

    if ((server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == 0)
    {
        closeServerFailure("Failed to open the socket");
    }

    ipv4_addr.sin_family = AF_INET; // use IPv4 addresses
    // InetPton(AF_INET, "127.0.0.1", &ipv4_addr.sin_addr.s_addr);
    ipv4_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ipv4_addr.sin_port = htons(6667);
    memset(&(ipv4_addr.sin_zero), '\0', 8);

    if (bind(server_fd, (SOCKADDR *)&ipv4_addr, sizeof(ipv4_addr)) == SOCKET_ERROR)
    {
        closeServerFailure("Socket binding failed");
    }
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR)
    {
        closeServerFailure("Listening failed");
    }
}

void Server::closeServerFailure(char *msg)
{
    perror(msg);
    if (server_fd)
        closesocket(server_fd);
    WSACleanup();
    exit(EXIT_FAILURE);
}

void Server::closeServer()
{
    closesocket(server_fd);
    WSACleanup();
    exit(EXIT_SUCCESS);
}