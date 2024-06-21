#include "../inc/Client.h"

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

    sendOption(username);
    sleep(1);
    sendOption(password);
    readResponse(buffer);

    if (strcmp(buffer, "Authentication Successful") == 0)
    {
        std::cout << "48\n";
        return false;
    }

    return true;
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
            std::cout<<"120"<<"\n";

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
// void handleChefOptions(Client &client);
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
int main()
{
    const char *serverIP = "127.0.0.1";
    int serverPort = 8080;

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

    if (client.authenticate(username, password))
    {
        std::cout << "130\n";
        std::string role = client.getRoleFromServer();
        std::cout << "131\n";
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "132\n";
        // client.readResponse(buffer);

        std::cout << "Role:" << role << "<-\n";
        if (role == "Admin\n")
        {
            std::cout << Utility::showMenu(role);
            std::string optionstr;
            std::cout << "Enter option (1-4): ";
            std::cin >> optionstr;
            client.sendOption(optionstr);
            int option = std::stoi(optionstr);
            if (option >= 1 && option <= 4)
            {

                if (option == 1)
                {
                    std::string name, price, available, mealTypeStr;
                    char buffer[BUFFER_SIZE] = {0};
                    client.readResponse(buffer);
                    std::cout << "Item name: ";
                    std::cin >> name;
                    client.sendOption(name);
                    std::cout << "Price: ";
                    std::cin >> price;
                    client.sendOption(price);
                    std::cout << "Availability (Yes/No): ";
                    std::cin >> available;
                    client.sendOption(available);
                    std::cout << "Meal Type (Breakfast/Lunch/Dinner): ";
                    std::cin >> mealTypeStr;
                    client.sendOption(mealTypeStr);
                    client.readResponse(buffer);
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
        else if (role == "Employee\n")
        {
            Utility::showMenu(role);
            handleEmployeeOptions(client);
        }
        else
        {
            std::cout << "Invalid option" << std::endl;
        }
    }
    else
    {
        std::cout << "Authentication failed" << std::endl;
    }

    client.closeConnection();

    return 0;
}
