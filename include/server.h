#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// socket libraries
#if defined(_WIN32) || defined(_WIN64)
#include <winsock2.h>
#include <ws2tcpip.h>
#include <ws2spi.h>
/*
 * this part is missing from my gcc's winsock2 library for some reason
 * so I have to define it here after including winsock2
 * will look into later...
 */
typedef struct pollfd
{
    SOCKET fd;
    SHORT events;
    SHORT revents;
} WSAPOLLFD, *PWSAPOLLFD, FAR *LPWSAPOLLFD;
WINSOCK_API_LINKAGE int WSAAPI WSAPoll(LPWSAPOLLFD fdArray, ULONG fds, INT timeout);
#define POLLIN 0x001
#define POLLOUT 0x004
#define POLLERR 0x008
#define POLLHUP 0x010
#define POLLNVAL 0x020
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include "client.h"
#include "channel.h"
#include "commands.h"

#define MSG_SIZE 1024
#define REPLY_SIZE 65536

using namespace std;

struct client_fd
{
};

class Server
{
private:
    WSADATA wsaData;
    int wsaerr, port;
    SOCKET server_fd;
    sockaddr_in ipv4_addr;

    vector<pollfd> _pollfds;
    map<char *, Client *> _clients;
    map<char *, Channel *> _channels;

    // long rc;
    string password, name;
    // initializing the server
    int startWinsock();
    void closeServerFailure(char *msg);
    // dealing with clients
    int acceptClient();
    int getClientInfo();
    int disconnectClient();
    int authenticateClient();
    // registration stuff
    char *hashPassword(char *pass);
    void registerClient();
    // handling messages
    int handleMessage(int fd);
    string readMessage(int fd);
    void sendMessage(int fd);
    // handling channels
    void addChannel(int cid);
    void removeChannel(int cid);

public:
    Server(string name, string password);
    ~Server();
    int createServer();
    int start();
    int executeCommand(enum _COMMANDS command);
    void closeServer();
};