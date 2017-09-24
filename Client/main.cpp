#include "Client.h"

int main(int argc, char *argv[])
{
    Client client = Client(argc, argv);
    client.run();
    return 0;
}