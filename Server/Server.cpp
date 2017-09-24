//
// Created by bender on 14.09.17.
//
#include "Server.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

#define ERROR (-1)
#define SUCCESS 0
#define SERVER_IS_UP true

Server::Server(int argc, char **argv) {
    signal(SIGCHLD, SIG_IGN);
    if (argc < 4) {
        fprintf(stderr,"ERROR: no port, buffer size or directory address provided.\n");
        exit(1);
    }
    this->configuration.port = static_cast<uint16_t>(atoi(argv[1]));
    this->configuration.bufferSize = atoi(argv[3]);
    this->configuration.toDirectory = argv[2];
    this->fileNameLength = 256;
    this->fileCounter = 0;
}

void Server::run() {
    start(listeningOn(port(), listener()));
}

void Server::start(int listener) {
    listen(listener, 1);
    while(SERVER_IS_UP) {
        handle(callFrom(listener));
    }
}

int Server::listeningOn(uint16_t port, int listener) {
    struct sockaddr_in sockaddr_in{};
    sockaddr_in.sin_family = AF_INET;
    sockaddr_in.sin_port = htons(port);
    sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    if(bind(listener, (struct sockaddr *)&sockaddr_in, sizeof(sockaddr_in)) < 0) {
        perror("bind");
        exit(2);
    } else {
        printf("bind: SUCCESS!\n");
    }
    return listener;
}

uint16_t Server::port() {
    return configuration.port;
}

int Server::listener() {
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0) {
        perror("socket");
        exit(1);
    }
    return listener;
}

void Server::handle(int from) {
    fileCounter += 1;
    int pid  = fork();
    switch(pid) {
        case ERROR: {
            perror("fork");
        }
            break;
        case SUCCESS: {
            exchange(from, to(fileCounter));
            exit(0);
        }
        default: break;
    }
}

int Server::callFrom(int listener) {
    int socket = accept(listener, nullptr, nullptr);
    if(socket < 0) {
        perror("accept");
        exit(3);
    } else {
        printf("accept: SUCCESS: socket: %i\n", socket);
    }
    return socket;
}

void Server::exchange(int from, int to) {
    char buffer[configuration.bufferSize];
    int nread, nwrite;
    do {
        //Get one chunk of the file from net.
        nread = static_cast<int>(read(from, buffer, static_cast<size_t>(configuration.bufferSize)));
//        printf("Bytes read from socket: %i.\n", nread);
        if (nread == 0) {
            //All done; close the file and the socket descriptors.
            close(from);
            close(to);
            break;
        }
        nwrite = static_cast<int>(write(to, buffer, static_cast<size_t>(nread)));
        if (nwrite < 0) {
            perror("write failed");
        }
//        printf("Bytes written to file: %i.\n", nwrite);
    } while (nread > 0);
}

int Server::to(int fileCounter) {
    auto *fileName = new char[fileNameLength];
    sprintf(fileName, strcat(configuration.toDirectory, "/ServerFile_%i\n"), fileCounter);
    printf(fileName);
    int to = open(fileName, O_WRONLY | O_CREAT, 0600);
    if (to < 0) {
        perror("open failed");
        exit(0);
    }
    return to;
}

#pragma clang diagnostic pop