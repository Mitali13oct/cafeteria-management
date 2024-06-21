#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include"Utility.h"
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
    bool authenticate(const std::string &username, const std::string &password);
    bool readResponse(char *);
    std::string getRoleFromServer();
    bool sendOption(std::string option);
    void closeConnection();
};