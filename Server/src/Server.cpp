
#include "Server/inc/Server.h"

Server::Server(int port)
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << std::endl;
}

Server::~Server()
{
    close(server_fd);
}

void *Server::handleClient(void *socket_desc)
{
    char buffer[BUFFER_SIZE] = {0};
    std::string username, password;
    Server *server = (Server *)(socket_desc);
    int new_socket = server->server_fd;
    if (!server->readFromSocket(new_socket, buffer, username))
        return server->handleAuthFailure(new_socket);

    if (!server->readFromSocket(new_socket, buffer, password))
        return server->handleAuthFailure(new_socket);

    UserRepository userRepo;
    if (!userRepo.authenticateUser(username, password))
    {
        return server->handleAuthFailure(new_socket);
    }

    User *user = userRepo.getUserByUsername(username);
    std::string userRole = userRepo.getUserRole(username);
    std::string menu = Utility::showMenu(userRole);
    server->sendPrompt(new_socket, menu);
    while (true)
    {
        int option = server->readOptionFromClient(new_socket, buffer);
        std::string result = server->processUserOption(user, option, new_socket, buffer);
        send(new_socket, result.c_str(), result.size(), 0);
        if (option <= 0)
            break;
    }

    server->closeSocket(new_socket);
    delete (int *)socket_desc;
    return NULL;
}

void *Server::handleAuthFailure(int socket)
{
    const char *authFail = "Authentication failed";
    send(socket, authFail, strlen(authFail), 0);
    close(socket);
    return NULL;
}

void Server::sendPrompt(int socket, const std::string &menu)
{
    std::string response =  menu + "\n";
    std::cout << "Send server" << std::endl;
    send(socket, response.c_str(), response.length(), 0);
    
}

int Server::readOptionFromClient(int socket, char *buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    int valread = read(socket, buffer, BUFFER_SIZE);
    if (valread <= 0)
    {
        return -1;
    }
    std::cout << "read server" << std::endl;
    return std::stoi(buffer);
}

std::string Server::processUserOption(User *user, int option, int socket, char *buffer)
{
    std::string result;
    if (user->getRole() == "Admin")
    {
        Admin *admin = dynamic_cast<Admin *>(user);
       
        std::cout << "Admin" << std::endl;
        if (option == 1)
        {
            std::string name;
            std::string mealTypeStr;
            std::string price = "";
            std::string available = "";
            sendPrompt(socket, Utility::menuItemString());
            if (!readFromSocket(socket, buffer, name))
                return "Failed to read item name";

            if (!readFromSocket(socket, buffer, price))
                return "Failed to read price";

            if (!readFromSocket(socket, buffer, available))
                return "Failed to read availability";

            if (!readFromSocket(socket, buffer, mealTypeStr))
                return "Failed to read meal type";
            MealType mealType;
            MenuService service;
            if (mealTypeStr == "Breakfast")
            {
                mealType = MealType::Breakfast;
                service = (new BreakfastRepository());
            }
            else if (mealTypeStr == "Lunch")
            {
                mealType = MealType::Lunch;
            }
            else if (mealTypeStr == "Dinner")
            {
                mealType = MealType::Dinner;
            }
            else
            {
                mealType = MealType::Breakfast;
            }

            double price1 = std::stod(price);
            bool a;
            if (available == "Yes")
            {
                a = true;
            }
            else
            {
                a = false;
            }
            MenuItem item(name, price1, mealType, a);

            admin->setService(service);
            admin->addMenuItem(item);
            result = "Item added successfully.";
        }

        else if (option == 2)
        {
            processViewItemsOption(admin, socket, buffer);std::string extra;
           
            std::string id, column, value;
            sendPrompt(socket, "Enter item id to edit: ");
            readFromSocket(socket, buffer, id);

            sendPrompt(socket, "Enter column name to edit: ");
            readFromSocket(socket, buffer, column);

            sendPrompt(socket, "Enter value to update: ");
            readFromSocket(socket, buffer, value);
            int id1 = std::stoi(id);
            admin->updateMenuItem(id1,column,value);

            result = "Item updated successfully.";
        }
        else if (option == 3)
        {
            result = "Delete Menu Item";
            processViewItemsOption(admin,socket,buffer);
            std::string id;
            sendPrompt(socket, "Enter item id to delete: ");
            readFromSocket(socket,buffer,id);
            int id1 = std::stoi(id);
            admin->deleteItem(id1);

        }
        else if (option == 4)
        {
            processViewItemsOption(admin,socket,buffer);
        }
        else
        {
            result = "Invalid Option";
        }
    }
    else if (user->getRole() == "Chef")
    {
        switch (option)
        {
        case 1:
            result = "View Menu Items";
            break;
        case 2:
            result = "Generate Monthly Report";
            break;
        case 3:
            result = "Send Notification";
            break;
        default:
            result = "Invalid Option";
            break;
        }
    }
    else if (user->getRole() == "Employee")
    {
        switch (option)
        {
        case 1:
            result = "Choose Menu Item";
            break;
        case 2:
            result = "Provide Feedback";
            break;
        case 3:
            result = "View Notifications";
            break;
        default:
            result = "Invalid Option";
            break;
        }
    }
    return result;
}
std::string Server::processViewItemsOption(Admin *admin, int socket, char *buffer)
{
    std::string mealTypeStr;
    sendPrompt(socket, "Enter the meal type to view items (Breakfast/Lunch/Dinner): ");
    if (!readFromSocket(socket, buffer, mealTypeStr))
        return "";

    MealType mealType;
    MenuService service;
    if (mealTypeStr == "Breakfast")
    {
        mealType = MealType::Breakfast;
        service = (new BreakfastRepository());
    }
    else if (mealTypeStr == "Lunch")
    {
        mealType = MealType::Lunch;
    }
    else if (mealTypeStr == "Dinner")
    {
        mealType = MealType::Dinner;
    }
    else
    {
        return "Invalid meal type entered.";
    }
    admin->setService(service);
    sendPrompt(socket, admin->getAllMenuItem());

    return admin->getAllMenuItem();
}

void Server::closeSocket(int socket)
{
    close(socket);
}

void Server::start()
{
    while (true)
    {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (new_socket < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::cout << "New connection accepted" << std::endl;

        pthread_t client_thread;
        int *new_sock = new int;
        *new_sock = new_socket;
        if (pthread_create(&client_thread, NULL, handleClient, (void *)new_sock) < 0)
        {
            perror("could not create thread");
            delete new_sock;
            return;
        }

        pthread_detach(client_thread);
    }
}

int main()
{
    int port;
    std::cout << "Enter port: ";
    std::cin >> port;

    Server server(port);
    server.start();

    return 0;
}
