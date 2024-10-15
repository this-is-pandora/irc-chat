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

#define MSG_SIZE 1024
#define REPLY_SIZE 65536

using namespace std;

class Server
{
private:
    WSADATA wsaData;
    int wsaerr, port;
    WORD wVersion;
    SOCKET server_fd;
    sockaddr_in ipv4_addr;

    map<string, int *> clients;
    map<string, int *> channels;

    // long rc;
    string password, name;
    int startWinsock();
    void closeServerFailure(char *msg);
    void handleIncomingClient();
    void authenticateUser();

public:
    Server(string name, string password);
    ~Server();
    void startServer();
    void closeServer();
};