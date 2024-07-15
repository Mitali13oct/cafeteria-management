#pragma once

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include "Utility.h"
#include <map>
#define BUFFER_SIZE 1024

class Client
{
private:
    int sock;
    struct sockaddr_in serverAddr;

public:
    Client();
    ~Client();
    bool connectToServer(const char *ip, int port);
    bool authenticate(std::map<std::string, std::string>);
    bool sendMulitpleDetails(std::map<std::string, std::string> details);

    bool readResponse(char *);
    std::string getRoleFromServer();
    bool sendOption(std::string option);
    void closeConnection();
};