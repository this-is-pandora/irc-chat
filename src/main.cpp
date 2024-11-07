#include <iostream>
#include "../include/client.h"
#include "../include/server.h"

int main(int argc, char *argv[])
{
    // placeholder code for now
    Server *server = new Server("hello world", "example");
    Client *cli = new Client("example");
    server->createServer();
    cli->connectServer();
    server->closeServer();
    return 0;
}
