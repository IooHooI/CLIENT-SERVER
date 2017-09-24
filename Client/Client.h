//
// Created by bender on 14.09.17.
//

#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <csignal>
#include <fcntl.h>

struct Configuration
{
    struct hostent *host;
    uint16_t port;
    int bufferSize;
    char *fromFile;
};

class Client
{

public:
    Client(int argc, char **argv);
    void run();
private:
    struct Configuration configuration;

    void exchange(int from, int to);
    void error(const char *msg);

};

#endif //CLIENT_CLIENT_H