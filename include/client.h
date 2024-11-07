#pragma once
#include <iostream>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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
    string hostname;
    string nickname;
    string realname;
    bool registered;
    sockaddr_in server_addr;

public:
    Client(string username);
    ~Client();
    void initialize();
    int setUserName(char *name);
    char *getUserName();
    int connectServer(char *ip_addr = "127.0.0.1", int port = 6667, string password);
    int disconnect();
    int sendMessage(char *msg);
};