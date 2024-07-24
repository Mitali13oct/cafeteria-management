#include "Client.h"

Client::Client() : sock(0)
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
    }
}

Client::~Client()
{
    close(sock);
}

bool Client::connectToServer(const char *ip, int port)
{
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return false;
    }

    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << "Connection Failed" << std::endl;
        return false;
    }

    std::cout << "Connected to server" << std::endl;
    return true;
}

bool Client::authenticate(std::map<std::string, std::string> details)
{
    char buffer[BUFFER_SIZE] = {0};

    sendMulitpleDetails(details);
    readResponse(buffer);
    if (strcmp(buffer, "Authentication Successful\n") == 0)
    {
        return true;
    }

    return false;
}

bool Client::sendOption(std::string option)
{
    char buffer[BUFFER_SIZE] = {0};

    if (send(sock, option.c_str(), option.length(), 0) == -1)
    {
        std::cerr << "Failed to send data to server" << std::endl;
        return false;
    }
    std::cout << "sent client" << std::endl;
    return true;
}

void Client::closeConnection()
{
    close(sock);
}
bool Client::readResponse(char *buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread <= 0)
    {
        std::cout << "120" << "\n";

        return false;
    }
    std::cout << "Server Response:\n"
              << buffer;

    return true;
}
std::string Client::getRoleFromServer()
{

    char buffer1[BUFFER_SIZE];
    read(sock, buffer1, BUFFER_SIZE);
    return std::string(buffer1);
}
bool Client::sendMulitpleDetails(std::map<std::string, std::string> details)
{
    char buffer[BUFFER_SIZE] = {0};

    std::string serializedDetails;
    for (const auto &pair : details)
    {
        serializedDetails += pair.first + ":" + pair.second + ";";
    }

    if (!serializedDetails.empty())
    {
        serializedDetails.pop_back();
    }
    if (sendOption(serializedDetails))
    {
        return true;
    }
    return false;
}

#include "Client.h"


int main()
{
    const char *serverIP = "127.0.0.1";
    int serverPort = 8080;

    Client client;

    if (!client.connectToServer(serverIP, serverPort))
    {
        std::cerr << "Failed to connect to server" << std::endl;
        return 0;
    }

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::map<std::string, std::string> loginDetails = {{"username", username}, {"password", password}};
    if (client.authenticate(loginDetails))
    {
        char buffer[BUFFER_SIZE] = {0};
        client.readResponse(buffer);
        std::string role = buffer;

        std::unique_ptr<RoleHandler> roleHandler;
        if (role == "Admin\n")
        {
            roleHandler = std::make_unique<AdminHandler>();
        }
        else if (role == "Chef\n")
        {
            roleHandler = std::make_unique<ChefHandler>();
        }
        else if (role == "Employee\n")
        {
            roleHandler = std::make_unique<EmployeeHandler>();
        }
        else
        {
            std::cerr << "Invalid role" << std::endl;
            return 0;
        }

        bool exit = false;
        while (!exit)
        {
            exit = roleHandler->handleOptions(client);
        }
    }
    else
    {
        std::cout << "Authentication failed" << std::endl;
    }

    client.closeConnection();

    return 0;
}
