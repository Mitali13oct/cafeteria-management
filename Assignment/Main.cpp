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

bool Client::authenticate(const std::string &username, const std::string &password)
{
    char buffer[BUFFER_SIZE] = {0};

    std::string LoginStr = "LOGIN;" + username + ";" + password;
    sleep(1);
    sendOption(LoginStr);
    readResponse(buffer);
    if (buffer == "admin " || buffer == "chef " || buffer == "employee")
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

    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread <= 0)
    {
        std::cout << "120" << "\n";

        return false;
    }
    std::cout << "Server Response:\n"
              << buffer;
    memset(buffer, 0, BUFFER_SIZE);

    return true;
}
std::string Client::getRoleFromServer()
{
    char buffer[BUFFER_SIZE];
    read(sock, buffer, BUFFER_SIZE);
    return std::string(buffer);
}
// void handleAdminOptions(Client &client);
void handleChefOptions(Client &client)
{
    std::string optionstr;

    std::cout << "Enter option (1-3): ";
    std::cin >> optionstr;
    client.sendOption(optionstr);
    int option = std::stoi(optionstr);
    if (option == 1)
    {
        char buffer[BUFFER_SIZE] = {0};
        client.readResponse(buffer);
        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);
    }
}
void handleEmployeeOptions(Client &client)
{
    std::string optionstr;

    std::cout << "Enter option (1-3): ";
    std::cin >> optionstr;
    client.sendOption(optionstr);
    int option = std::stoi(optionstr);

    if (option == 2)
    {
        char buffer[BUFFER_SIZE] = {0};

        // client.readResponse(buffer);

        client.readResponse(buffer);
        std::string mealtype;
        std::cin >> mealtype;
        client.sendOption(mealtype);

        client.readResponse(buffer);
    }
    if (option == 3)
    {
        char buffer[BUFFER_SIZE] = {0};
        client.readResponse(buffer);
        std::string typeOption;
        std::cin >> typeOption;

        client.sendOption(typeOption);
        client.readResponse(buffer);
    }
}
std::string Client::addItem(std::string name, std::string price, std::string availability, std::string mealTypeId)
{
    char buffer[BUFFER_SIZE] = {0};
    sendOption("admin_addMenuItem;" + name + ";" + price + ";" + availability + ";" + mealTypeId);
    read(sock, buffer, BUFFER_SIZE);
    return buffer;
}
int main()
{
    const char *serverIP = "172.16.1.100";
    int serverPort = 3000;

    Client client;

    if (!client.connectToServer(serverIP, serverPort))
    {
        std::cerr << "Failed to connect to server" << std::endl;
        return -1;
    }

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    std::string LoginStr = "LOGIN;" + username + ";" + password;
    sleep(1);
    client.sendOption(LoginStr);
    std::string role = client.getRoleFromServer();
    char buffer[BUFFER_SIZE] = {0};

    std::cout << "Role:" << role;
    if (role == "admin")
    {
        std::cout << Utility::showMenu(role);

        int option;
        std::cout << "Enter option:" << "\n";
        std::cin >> option;
        if (option >= 1 && option <= 4)
        {

            if (option == 1)
            {
                std::string name, price,a,id;
                std::cout << "Enter Name: ";
                std::getline(std::cin>>std::ws,name);
                std::cout << "Enter price: ";
                std::cin >> price;
                std::cout << "Enter availability: ";
                std::cin >> a;
                std::cout << "Enter mealTypeId: ";
                std::cin >> id;
               std::cout<< client.addItem(name, price, a, id);
            }
            else if (option == 2)
            {
                char buffer[BUFFER_SIZE] = {0};

                client.readResponse(buffer);
                std::string mealStr;
                std::cin >> mealStr;
                client.sendOption(mealStr);

                client.readResponse(buffer);

                client.readResponse(buffer);
                std::string id;
                std::cin >> id;
                client.sendOption(id);

                client.readResponse(buffer);
                std::string column;
                std::cin >> column;
                client.sendOption(column);

                client.readResponse(buffer);
                std::string value;
                std::cin >> value;
                client.sendOption(value);
            }
            else if (option == 3)
            {
                char buffer[BUFFER_SIZE] = {0};
                client.readResponse(buffer);
                std::string mealType;
                std::cin >> mealType;

                client.sendOption(mealType);
                client.readResponse(buffer);
                client.readResponse(buffer);
                std::string id;
                std::cin >> id;
                client.sendOption(id);
            }
            else if (option == 4)
            {
                char buffer[BUFFER_SIZE] = {0};
                client.readResponse(buffer);
                std::string mealType;
                std::cin >> mealType;

                client.sendOption(mealType);
                client.readResponse(buffer);
            }
        }
    }
    else if (role == "chef")
    {
        std::cout << Utility::showMenu(role);
        handleChefOptions(client);
    }
    else if (role == "employee")
    {
        std::cout << Utility::showMenu(role);
        handleEmployeeOptions(client);
    }
    else
    {
        std::cout << "Invalid option" << std::endl;
    }

    client.closeConnection();

    return 0;
}
