#include <iostream>
#include "../include/client.h"
#include "../include/server.h"

int main(int argc, char *argv[])
{
    // placeholder code for now
    Server *server = new Server("hello world", "example");
    server->createServer();
    server->closeServer();
    return 0;
}
