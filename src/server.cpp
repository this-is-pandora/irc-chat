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

int Server::createServer()
{
    int rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    u_long mode = 1;
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
    ipv4_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    ipv4_addr.sin_port = htons(6667);
    memset(&(ipv4_addr.sin_zero), '\0', 8);
    if (ioctlsocket(server_fd, FIONBIO, &mode) == SOCKET_ERROR)
    {
        closeServerFailure("Failed to set socket mode to non-blocking");
    }
    if (bind(server_fd, (SOCKADDR *)&ipv4_addr, sizeof(ipv4_addr)) == SOCKET_ERROR)
    {
        closeServerFailure("Socket binding failed");
    }
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR)
    {
        closeServerFailure("Listening failed");
    }
    else
    {
        cout << "Socket is listening..." << endl;
    }
    return 0;
}

int Server::acceptClient()
{
    SOCKET client_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in cli_addr;
    int cli_len;
    cli_len = sizeof(cli_addr);
    if ((client_fd = accept(server_fd, (sockaddr *)&cli_addr, &cli_len)) == INVALID_SOCKET)
    {
        // TODO
        perror("Invalid client socket");
        return 1;
    }
    pollfd client_poll = {client_fd, POLLIN, 0};
    _pollfds.push_back(client_poll);
    // TODO: create a collection of connected client sockets
    clients["name"] = client_fd;

    // TODO: send an MOTD response to the client and user count
    return 0;
}

int Server::start()
{
    pollfd serverfd = {server_fd, POLLIN, 0};
    _pollfds.push_back(serverfd);
    char buff[1024];
    // TODO: main server loop
    while (true)
    {
        if (WSAPoll(_pollfds.data(), _pollfds.size(), -1) == -1)
        {
            perror("WSAPoll error");
        }
        for (auto it = _pollfds.begin(); it != _pollfds.end(); ++it)
        {
            if (it->revents == 0)
                continue;
            // check for a POLLIN event, i.e. a client connection request
            if (it->revents & POLLIN)
            {
                // TODO: complete and test
                acceptClient();
                break;
            }
            else
            {
                // TODO: Error
            }
        }
        /*
        memset(buff, 0, sizeof(buff));
        recv(clients["name"], buff, sizeof(buff), 0); */
    }
    return 0;
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

// TODO: commands
int Server::executeCommand(int command)
{
    switch (command)
    {
    case 0:
        break;
    case 1:
        break;
    default:
        break;
    }
    return 0;
}