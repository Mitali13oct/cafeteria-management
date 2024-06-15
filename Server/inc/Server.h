#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include "../inc/UserRepository.h"
#include "../inc/Utility.h"

#define BUFFER_SIZE 1024
class Server
{
private:
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

public:
    Server(int port);
    ~Server();
    void start();
    static void *handleClient(void *socket_desc);
    void sendMenuAndPrompt(int socket, const std::string &menu);
    int readOptionFromClient(int socket, char *buffer);
    bool readFromSocket(int socket, char *buffer, std::string &output);

    std::string processUserOption(const User &user, int option);
    void *handleAuthFailure(int socket);

    void closeSocket(int new_socket);
};
