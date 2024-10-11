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

class Server
{
private:
    WSADATA wsaData;
    int wsaerr, port;
    WORD wVersion;
    SOCKET server;
    sockaddr_in ipv4_addr;
    // TODO: implement Client & Channel class
    std::map<std::string, int *> clients;
    std::map<std::string, int *> channels;
    long rc;
    std::string password; // hash of the password
    int startWinsock();

public:
    Server();
    void startServer();
    void closeServer();
};