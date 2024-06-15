
#include"../inc/Server.h"

Server::Server(int port)
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Bind the socket to the network address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
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
    // Read username from client
    if (!server->readFromSocket(new_socket, buffer, username))
        return server->handleAuthFailure(new_socket);

    // Read password from client
    if (!server->readFromSocket(new_socket, buffer, password))
        return server->handleAuthFailure(new_socket);

    UserRepository userRepo;
    if (!userRepo.authenticateUser(username, password))
        return server->handleAuthFailure(new_socket);

    User *user = userRepo.getUserByUsername(username);
    std::string menu = Utility::showMenu(*user);
    server->sendMenuAndPrompt(new_socket, menu);

    // Handle client options
    while (true)
    {
        int option = server->readOptionFromClient(new_socket, buffer);
        std::string result = server->processUserOption(*user, option);
        send(new_socket, result.c_str(), result.size(), 0);
        if (option <= 0)
            break;
    }

    server->closeSocket(new_socket);
    delete (int *)socket_desc;
    return NULL;
}
bool Server::readFromSocket(int socket, char *buffer, std::string &output)
{
    int valread = read(socket, buffer, BUFFER_SIZE);
    if (valread <= 0)
        return false;
    output = std::string(buffer);
    memset(buffer, 0, BUFFER_SIZE);
    return true;
}

void *Server::handleAuthFailure(int socket)
{
    const char *authFail = "Authentication failed";
    send(socket, authFail, strlen(authFail), 0);
    close(socket);
    return NULL;
}

void Server::sendMenuAndPrompt(int socket, const std::string &menu)
{
    std::string response = "Authentication successful\n" + menu;
    send(socket, response.c_str(), response.size(), 0);
    send(socket, "Enter Option: ", 14, 0);
}

int Server::readOptionFromClient(int socket, char *buffer)
{
    memset(buffer, 0, BUFFER_SIZE);
    int valread = read(socket, buffer, BUFFER_SIZE);
    if (valread <= 0)
        return -1;
    return std::stoi(buffer);
}

std::string Server::processUserOption(const User &user, int option)
{
    std::string result;
    if (user.getRole() == "Admin")
    {
        switch (option)
        {
        case 1:
            result = "Add Menu Item";
            break;
        case 2:
            result = "Update Menu Item";
            break;
        case 3:
            result = "Delete Menu Item";
            break;
        case 4:
            result = "View All Menu Items";
            break;
        default:
            result = "Invalid Option";
            break;
        }
    }
    else if (user.getRole() == "Chef")
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
    else if (user.getRole() == "Employee")
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

void Server::closeSocket(int socket) {
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

        // Create a new thread for each client connection
        pthread_t client_thread;
        int *new_sock = new int;
        *new_sock = new_socket;
        if (pthread_create(&client_thread, NULL, handleClient, (void *)new_sock) < 0)
        {
            perror("could not create thread");
            delete new_sock;
            return;
        }

        // Optionally, detach the thread so that it cleans up after itself
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
