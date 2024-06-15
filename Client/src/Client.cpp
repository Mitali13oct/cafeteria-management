#include"../inc/Client.h"

Client::Client() : sock(0) {
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error" << std::endl;
    }
}

Client::~Client() {
    close(sock);
}

bool Client::connectToServer(const char *ip, int port) {
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, ip, &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return false;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection Failed" << std::endl;
        return false;
    }

    std::cout << "Connected to server" << std::endl;
    return true;
}

bool Client::authenticate(const std::string &username, const std::string &password) {
    char buffer[BUFFER_SIZE] = {0};

    // Send username and password to server for authentication
    send(sock, username.c_str(), username.length(), 0);
    sleep(1); // Give server time to process the first part
    send(sock, password.c_str(), password.length(), 0);

    // Read response from server
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread > 0) {
        std::cout << "Message from server: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive response from server" << std::endl;
        return false;
    }

    // Return true if authentication successful, otherwise false
    return strstr(buffer, "Authentication successful") != nullptr;
}

bool Client::sendOption(int option) {
    char buffer[BUFFER_SIZE] = {0};

    // Send option to server
    send(sock, std::to_string(option).c_str(), std::to_string(option).length(), 0);

    // Read response from server
    int valread = read(sock, buffer, BUFFER_SIZE);
    if (valread > 0) {
        std::cout << "Server response: " << buffer << std::endl;
    } else {
        std::cerr << "Failed to receive response from server" << std::endl;
    }

    return true;
}

void Client::closeConnection() {
    close(sock);
}

// Example usage of Client class
int main() {
    const char *serverIP = "127.0.0.1";
    int serverPort = 8080;

    Client client;

    if (!client.connectToServer(serverIP, serverPort)) {
        std::cerr << "Failed to connect to server" << std::endl;
        return -1;
    }

    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    if (client.authenticate(username, password)) {
        std::cout << "Authentication successful" << std::endl;
        
        // Simulate admin operations
        int option;
        std::cout << "Enter option (1-4): ";
        std::cin >> option;

        if (option >= 1 && option <= 4) {
            client.sendOption(option);
        } else {
            std::cout << "Invalid option" << std::endl;
        }
    } else {
        std::cout << "Authentication failed" << std::endl;
    }

    client.closeConnection();

    return 0;
}


