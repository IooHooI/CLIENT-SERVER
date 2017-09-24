//
// Created by bender on 14.09.17.
//

#include "Client.h"

Client::Client(int argc, char **argv) {
    if (argc < 5) {
        fprintf(stderr, "");
        exit(0);
    }
    this->configuration.host = gethostbyname(argv[1]);
    if (this->configuration.host == nullptr) {
        fprintf(stderr,"ERROR: no such host\n");
        exit(0);
    }
    this->configuration.port = static_cast<uint16_t>(atoi(argv[2]));
    this->configuration.fromFile = argv[3];
    this->configuration.bufferSize = atoi(argv[4]);
}

void Client::run() {
    int sockfd;
    struct sockaddr_in serv_addr{};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(configuration.host->h_addr, (char *)&serv_addr.sin_addr.s_addr, static_cast<size_t>(configuration.host->h_length));

    serv_addr.sin_port = htons(static_cast<uint16_t>(this->configuration.port));

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
    }

    /* Open the file */
    int fd = open(this->configuration.fromFile, O_RDONLY);
    if (fd < 0) {
        error("open failed");
    }
    exchange(fd, sockfd);
}

void Client::error(const char *msg) {
    perror(msg);
    exit(0);
}

void Client::exchange(int from, int to) {
    char buffer[this->configuration.bufferSize];
    int n_read, n_write, k;
    do {
        //Get one chunk of the file from disk
        n_read = static_cast<int>(read(from, buffer, static_cast<size_t>(this->configuration.bufferSize)));
        printf("Bytes read from file: %i.\n", n_read);
        if (n_read == 0) {
            //All done; close the file and the socket.
            close(from);
            close(to);
            break;
        }
        //Send the chunk
        k = 0;
        for (int i = 0; i < n_read; i += n_write) {
            // write might not take it all in one call,
            //so we have to try until it's all written
            n_write = static_cast<int>(write(to, buffer + i, static_cast<size_t>(n_read - i)));
            printf("Bytes sent to socket: %i. Iteration: %i.\n", n_write, k);
            if (n_write < 0) {
                error("write failed");
            }
            k++;
        }
    } while (n_read > 0);
}