#include "Server.h"

int main(int argc, char *argv[])
{
    Server server = Server(argc, argv);
    server.run();
    return 0;
}