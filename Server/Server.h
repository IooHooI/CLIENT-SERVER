//
// Created by bender on 14.09.17.
//

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <csignal>
#include <fcntl.h>

struct Configuration
{
    uint16_t port;
    int bufferSize;
    char *toDirectory;
};

class Server
{
public:
    explicit Server(int argc, char *argv[]);
    void run();
private:
    struct Configuration configuration;
    int fileNameLength;
    int fileCounter;

    void exchange(int from, int to);
    void start(int listener);
    void handle(int from);

    int listeningOn(uint16_t port, int listener);
    int callFrom(int listener);
    int listener();
    uint16_t port();

    int to(int fileCounter);
};

#endif //SERVER_SERVER_H