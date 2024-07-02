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

bool Client::authenticate(std::map<std::string, std::string> details)
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

    sendOption(serializedDetails);
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
void handleAdminOptions(Client &client)
{
    std::string optionstr;

    std::cout << "Enter option (1-5): ";
    std::cin >> optionstr;
    client.sendOption(optionstr);
    int option = std::stoi(optionstr);
    if (option >= 1 && option <= 5)
    {

        if (option == 1)
        {
            std::string name, price, available, mealTypeStr;
            char buffer[BUFFER_SIZE] = {0};
            std::cout << "Item name: ";
            std::cin >> name;
            std::cout << "Price: ";
            std::cin >> price;
            std::cout << "Availability (Yes/No): ";
            std::cin >> available;
            std::cout << "Meal Type (Breakfast/Lunch/Dinner): ";
            std::cin >> mealTypeStr;
            std::map<std::string, std::string> itemdetail = {{"Name", name}, {"Price", price}, {"AvailabilityStatus", available}, {"MealType", mealTypeStr}};
            client.sendMulitpleDetails(itemdetail);
            client.readResponse(buffer);
        }
        else if (option == 2)
        {
            char buffer[BUFFER_SIZE] = {0};

            std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

            std::string mealStr;
            std::cin >> mealStr;
            client.sendOption(mealStr);

            client.readResponse(buffer);

            std::string id;
            std::cout << "Enter id to edit: ";
            std::cin >> id;

            std::string column;
            std::cout << "Enter column to edit: ";

            std::cin >> column;

            std::string value;
            std::cout << "Enter Value to edit: ";

            std::cin >> value;
            std::map<std::string, std::string> updateItemDeatils = {{"ItemID", id},
                                                                    {"ColumnName", column},
                                                                    {"Value", value}};

            client.sendMulitpleDetails(updateItemDeatils);
            client.readResponse(buffer);
        }
        else if (option == 3)
        {
            char buffer[BUFFER_SIZE] = {0};
            std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

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
            std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

            std::string mealType;
            std::cin >> mealType;

            client.sendOption(mealType);
            client.readResponse(buffer);
        }
        else if (option == 5)
        {
            char buffer[BUFFER_SIZE] = {0};
            std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

            std::string mealType;
            std::cin >> mealType;

            client.sendOption(mealType);
            client.readResponse(buffer);
            int deleteOption = Utility::discardItem();
            client.sendOption(std::to_string(deleteOption));
            if (deleteOption == 1)
            {
                std::cout << "Enter item ID to delete: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
            else if (deleteOption == 2)
            {
                std::cout << "Enter item ID to add Question for: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
        }
    }
}
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
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);
    }
    else if (option == 2)
    {
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);
        std::string number;
        std::cin >> number;
        client.sendOption(number);
        client.readResponse(buffer);
    }
    else if (option == 3)
    {
        char buffer[BUFFER_SIZE] = {0};

        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);
        std::string itemID;
        std::cout << "Enter Item IDs you want to prepare (comma-separated): ";
        std::cin.ignore();
        std::getline(std::cin, itemID);

        client.sendOption(itemID);
        client.readResponse(buffer);
    }
    else if (option == 4)
    {
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "Enter the meal type to view Discarded items (Breakfast/Lunch/Dinner): ";

        std::string mealType;
        std::cin >> mealType;

        client.sendOption(mealType);
        client.readResponse(buffer);
       int deleteOption = Utility::discardItem();
            client.sendOption(std::to_string(deleteOption));
            if (deleteOption == 1)
            {
                std::cout << "Enter item ID to delete: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
            else if (deleteOption == 2)
            {
                std::cout << "Enter item ID to add Question for: ";
                int id;
                std::cin >> id;
                client.sendOption(std::to_string(id));
                client.readResponse(buffer);
            }
    }
}
void handleEmployeeOptions(Client &client)
{
    std::string optionstr;

    std::cout << "Enter option (1-3): ";
    std::cin >> optionstr;
    client.sendOption(optionstr);
    int option = std::stoi(optionstr);

    if (option == 1)
    {
        char buffer[BUFFER_SIZE] = {0};

        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";
        std::string mealtype;
        std::cin >> mealtype;
        client.sendOption(mealtype);

        client.readResponse(buffer);

        std::string itemID;
        std::cout << "Enter Item IDs you want to vote for (comma-separated): ";
        std::cin.ignore();
        std::getline(std::cin, itemID);

        client.sendOption(itemID);

        client.readResponse(buffer);
    }
    if (option == 2)
    {
        char buffer[BUFFER_SIZE] = {0};
        client.readResponse(buffer);
        std::string typeOption;
        std::cin >> typeOption;

        client.sendOption(typeOption);
        client.readResponse(buffer);
    }
    if (option == 3)
    {
        char buffer[BUFFER_SIZE] = {0};
        std::cout << "Enter the meal type to view items (Breakfast/Lunch/Dinner): ";

        std::string mealTypeStr;
        std::cin >> mealTypeStr;
        client.sendOption(mealTypeStr);
        client.readResponse(buffer);

        std::string itemID, comment, rating;
        std::cout << "Enter item ID to give Feedback and rating on: ";
        std::cin >> itemID;
        std::cout << "Enter comment: ";
        std::cin.ignore();
        std::getline(std::cin, comment);
        std::cout << "Enter Rating: ";
        std::cin >> rating;
        std::map<std::string, std::string> feedback = {{"ItemId", itemID}, {"comment", comment}, {"rating", rating}};
        client.sendMulitpleDetails(feedback);
        client.readResponse(buffer);
    }
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
    std::map<std::string, std::string> loginstr = {{"username", username}, {"password", password}};
    if (client.authenticate(loginstr))
    {
        char buffer[BUFFER_SIZE] = {0};
        client.readResponse(buffer);
        std::string role = buffer;

        std::cout << "Role:" << role << "\n";
        if (role == "Admin\n")
        {
            std::cout << Utility::showMenu(role);
            handleAdminOptions(client);
        }
        else if (role == "Chef\n")
        {
            std::cout << Utility::showMenu(role);
            handleChefOptions(client);
        }
        else if (role == "Employee\n")
        {
            std::cout << Utility::showMenu(role);
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
