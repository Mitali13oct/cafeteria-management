#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include "Server/inc/AuthenticationService/UserRepository.h"
#include "../inc/Utility.h"
#include "Server/inc/MenuService/BreakfastRepository.h"
#include"Server/inc/NotificationService/NotificationService.h"
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
    void sendPrompt(int socket, const std::string &menu);
    int readOptionFromClient(int socket, char *buffer);

    bool readFromSocket(int socket, char *buffer, std::string &output)
    {
        int valread = read(socket, buffer, BUFFER_SIZE);
        if (valread <= 0)
            return false;
        output = std::string(buffer);
        memset(buffer, 0, BUFFER_SIZE);
        std::cout << output << std::endl;
        return true;
    }
    std::string processViewItemsOption(Admin *admin, int socket, char *buffer);
    bool addItem(int socket, char *buffer, Admin *admin);
    std::string processUserOption(User *user, int option, int socket, char *buffer);
    void *handleAuthFailure(int socket);

    void closeSocket(int new_socket);
};
