#pragma once

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>
#include "UserRepository.h"
#include "Utility.h"
#include "BreakfastRepository.h"
#include "LunchRepository.h"
#include "DinnerRepository.h"
#include "NotificationService.h"
#include "RecommendationService.h"
#include "WordLoader.h"
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
    bool readMultipleFromSocket(int socket, char *buffer, std::map<std::string, std::string> &output);
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
    std::string handleAdmin(User *user, int socket, char *buffer);
     std::string handleChef(User *user, int socket, char *buffer);
     std::string handleEmployee(User *user, int socket, char *buffer);
    std::string processViewItemsOption(Admin *admin, int socket, char *buffer);
    void *handleAuthFailure(int socket);
    std::string getNotification(int socket, char *buffer);
    void closeSocket(int new_socket);
};
