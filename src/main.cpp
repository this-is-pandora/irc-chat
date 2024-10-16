#include <iostream>
#include "../include/client.h"
#include "../include/server.h"

int main(int argc, char *argv[])
{
    Server *server = new Server("hello world", "example");
    server->startServer();
    server->closeServer();
    return 0;
}
