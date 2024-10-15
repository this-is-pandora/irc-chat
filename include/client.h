#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// socket libraries
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

using namespace std;

class Client
{
private:
    WSADATA wsaData;
    int wsaerr;
    SOCKET client_fd;
    string username;

public:
    Client(string username);
    ~Client();
    void initializeClient();
    void connectToServer(char *ip_addr, int port, string password);
    void closeConnection();
    void sendMessage(char *msg);
};