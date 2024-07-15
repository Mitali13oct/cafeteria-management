
#include "Server.h"

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
bool Server::readMultipleFromSocket(int socket, char *buffer, std::map<std::string, std::string> &output)
{
    std::string data;
    if (!readFromSocket(socket, buffer, data))
    {
        return false;
    }

    std::istringstream stream(data);
    std::string pair;
    while (std::getline(stream, pair, ';'))
    {
        std::istringstream pairStream(pair);
        std::string key, value;
        if (std::getline(pairStream, key, ':') && std::getline(pairStream, value, ':'))
        {
            output[key] = value;
        }
    }
    return true;
}
std::string Server::handleChef(User *user, int socket, char *buffer)
{
    Chef *chef = dynamic_cast<Chef *>(user);
    int option = readOptionFromClient(socket, buffer);
    std::string result;
    if (option == 5)
    {
        closeSocket(socket);
    }
    if (option == 1)
    {
        std::string mealTypeStr;
        if (!readFromSocket(socket, buffer, mealTypeStr))
        {
            return "Failed to read meal type";
        }

        MenuRepository *menuRepository;

        if (mealTypeStr == "Breakfast")
        {
            menuRepository = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            menuRepository = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            menuRepository = (new DinnerRepository());
        }

        sendPrompt(socket, chef->getRecommendation(menuRepository));
    }
    else if (option == 2)
    {

        std::string mealTypeStr;
        if (!readFromSocket(socket, buffer, mealTypeStr))
        {
            return "Failed to read meal type";
        }
        MenuRepository *menuRepository;

        if (mealTypeStr == "Breakfast")
        {

            menuRepository = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            menuRepository = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            menuRepository = (new DinnerRepository());
        }
        std::string recommendations = chef->getRecommendation(menuRepository);

        if (recommendations.empty())
        {
            return "Recommendation not generated";
        }

        sendPrompt(socket, recommendations + "Enter number of items to rollOut: ");
        std::string numberStr;

        readFromSocket(socket, buffer, numberStr);
        int number = std::stoi(numberStr);
        chef->rollOutMenu(number, mealTypeStr);

        sendPrompt(socket, "Rolled out of recommendation");
    }
    else if (option == 3)
    {

        std::string mealTypeStr;
        if (!readFromSocket(socket, buffer, mealTypeStr))
        {
            return "Failed to read meal type";
        }

        sendPrompt(socket, chef->getVotedItems(mealTypeStr));

        std::string prepareItemIDs;
        if (!readFromSocket(socket, buffer, prepareItemIDs))
        {
            return "Failed to read item IDs";
        }

        std::vector<int> items;
        std::istringstream iss(prepareItemIDs);
        std::string id;
        while (std::getline(iss, id, ','))
        {
            items.push_back(std::stoi(id));
        }
        chef->chooseItemToPrepare(items);

        sendPrompt(socket, "Items Prepared");
    }
    else if (option == 4)
    {
        std::string mealTypeStr;
        readFromSocket(socket, buffer, mealTypeStr);
        MenuService service;
        if (mealTypeStr == "Breakfast")
        {

            service = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            service = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            service = (new DinnerRepository());
        }
        else
        {
        }
        chef->setService(service);

        sendPrompt(socket, chef->getDiscardedItems());

        std::string deleteOption;
        readFromSocket(socket, buffer, deleteOption);
        if (std::stoi(deleteOption) == 1)
        {
            std::string id;
            readFromSocket(socket, buffer, id);
            int itemToDelete = std::stoi(id);
            chef->deleteItem(itemToDelete);
            sendPrompt(socket, "Item Deleted");
        }
        else if (std::stoi(deleteOption) == 2)
        {
            std::string id;
            readFromSocket(socket, buffer, id);
            int itemToAddQuestion = std::stoi(id);
            chef->addQuestion(itemToAddQuestion);
            sendPrompt(socket, "Question added for detailed feedback");
        }
    }
    {
        result = "Invalid Option";
    }
    return result;
}

std::string Server::handleAdmin(User *user, int socket, char *buffer)
{
    Admin *admin = dynamic_cast<Admin *>(user);
    int option = readOptionFromClient(socket, buffer);
    std::string result;
    if (option == 6)
    {
        closeSocket(socket);
        LogService logService;
        logService.addLogInfo(user->getId(), "Logged out");
    }
    else if (option == 1)
    {
        std::map<std::string, std::string> itemDetails;
        readMultipleFromSocket(socket, buffer, itemDetails);

        std::string name = itemDetails["Name"];
        std::string mealTypeStr = itemDetails["MealType"];
        std::string price = itemDetails["Price"];
        std::string available = itemDetails["AvailabilityStatus"];
        std::string dietaryType = itemDetails["DietaryType"];
        std::string spiceType = itemDetails["SpiceType"];
        std::string cuisineType = itemDetails["CuisineType"];
        std::string sweetTooth = itemDetails["SweetToothType"];
        MealType mealType = Utility::mealTypeFromString(mealTypeStr);
        MenuRepository *repo;
        if (mealType == MealType::Breakfast)
        {
            repo = (new BreakfastRepository());
        }
        else if (mealType == MealType::Lunch)
        {
            repo = (new LunchRepository());
        }
        else if (mealType == MealType::Dinner)
        {
            repo = (new DinnerRepository());
        }
        else
        {
            mealType = MealType::Breakfast;
        }

        double price1 = std::stod(price);
        bool a = (available == "Yes");
        bool sweetToothType = (sweetTooth == "Yes");
        MenuItem item(name, price1, mealType, a, dietaryType, spiceType, cuisineType, sweetToothType);

        MenuService service(repo);
        admin->setService(service);
        admin->addMenuItem(item);
        result = "Item added successfully.";
        LogService logService;
        logService.addLogInfo(user->getId(), "Added " + Utility::mealTypeToString(mealType) + " Item");
    }
    else if (option == 2)
    {
        processViewItemsOption(admin, socket, buffer);
        std::string extra;
        std::map<std::string, std::string> updateItemDetail;
        std::string id, column, value;
        readMultipleFromSocket(socket, buffer, updateItemDetail);
        id = updateItemDetail["ItemID"];
        column = updateItemDetail["ColumnName"];
        value = updateItemDetail["Value"];
        int id1 = std::stoi(id);
        admin->updateMenuItem(id1, column, value);

        result = "Item updated successfully.";

        LogService logService;
        logService.addLogInfo(user->getId(), "Updated Item");
    }
    else if (option == 3)
    {

        processViewItemsOption(admin, socket, buffer);
        std::string id;
        sendPrompt(socket, "Enter item id to delete: ");
        readFromSocket(socket, buffer, id);
        int id1 = std::stoi(id);
        admin->deleteItem(id1);
        result = "Deleted Menu Item";
        LogService logService;
        logService.addLogInfo(user->getId(), "Deleted Item");
    }
    else if (option == 4)
    {
        processViewItemsOption(admin, socket, buffer);
        LogService logService;
        logService.addLogInfo(user->getId(), "Viewed all Items");
    }
    else if (option == 5)
    {
        std::string mealTypeStr;
        readFromSocket(socket, buffer, mealTypeStr);
        MenuService service;
        if (mealTypeStr == "Breakfast")
        {

            service = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            service = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            service = (new DinnerRepository());
        }

        admin->setService(service);
        sendPrompt(socket, admin->getDiscardedItems());
        std::string deleteOption;
        readFromSocket(socket, buffer, deleteOption);

        if (std::stoi(deleteOption) == 1)
        {
            std::string id;
            readFromSocket(socket, buffer, id);
            int itemToDelete = std::stoi(id);
            admin->deleteItem(itemToDelete);
            sendPrompt(socket, "Item Deleted");
            LogService logService;
            logService.addLogInfo(user->getId(), "Discarded Item");
        }
        else if (std::stoi(deleteOption) == 2)
        {
            std::string id;
            readFromSocket(socket, buffer, id);
            int itemToAddQuestion = std::stoi(id);
            admin->addQuestion(itemToAddQuestion);
            sendPrompt(socket, "Question added for detailed feedback");
            LogService logService;
            logService.addLogInfo(user->getId(), "Requested Detailed Feedback for Item");
        }
    }
    else
    {
        result = "Invalid Option";
    }
    return result;
}
std::string Server::handleEmployee(User *user, int socket, char *buffer)
{
    Employee *emp = dynamic_cast<Employee *>(user);
    int option = readOptionFromClient(socket, buffer);
    std::string result;
    if (option == 5)
    {
        closeSocket(socket);
    }
    else if (option == 1)
    {

        std::string mealTypeStr;
        if (!readFromSocket(socket, buffer, mealTypeStr))
        {
            return "Failed to read meal type";
        }
        MenuRepository *menuRepository;
        MenuService service;

        if (mealTypeStr == "Breakfast")
        {
            menuRepository = (new BreakfastRepository());
            service = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            menuRepository = (new LunchRepository());
            service = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            menuRepository = (new DinnerRepository());
            service = (new DinnerRepository());
        }
        emp->setService(service);
        std::string recommendationResponse = emp->getRolledOutItems(menuRepository);

        if (recommendationResponse == "Recommendation not rolled out for today")
        {
            return "Recommendation not rolled out for today\n";
        }
        sendPrompt(socket, recommendationResponse);

        std::string selectedIDs;
        if (!readFromSocket(socket, buffer, selectedIDs))
        {
            return "Failed to read item IDs";
        }

        std::vector<int> selectedItems;
        std::istringstream iss(selectedIDs);
        std::string id;
        while (std::getline(iss, id, ','))
        {
            selectedItems.push_back(std::stoi(id));
        }
        emp->voteOnItem(selectedItems);
        sendPrompt(socket, "Voted on items");
    }
    else if (option == 2)
    {

        std::string notificationTypeStr;
        sendPrompt(socket, "Enter the Notification type to view Notification(AvailabilityChange/ ItemAdded/ Recommendation )");
        readFromSocket(socket, buffer, notificationTypeStr);
        NotificationService nservice = new NotificationRepository();
        NotificationType type;

        if (notificationTypeStr == "Recommendation")
        {

            type = NotificationType::Recommendation;
        }
        else if (notificationTypeStr == "ItemAdded")
        {
            type = NotificationType::ItemAdded;
        }
        else if (notificationTypeStr == "ItemUpdated")
        {
            type = NotificationType::ItemUpdated;
        }
        else if (notificationTypeStr == "ItemDeleted")
        {
            type = NotificationType::ItemDeleted;
        }
        emp->setNotificationService(nservice);
        return emp->viewNotifications(type);
    }
    else if (option == 3)
    {

        std::string mealTypeStr;
        if (!readFromSocket(socket, buffer, mealTypeStr))
        {
            return "failed to read meal type";
        }
        MenuService service;
        if (mealTypeStr == "Breakfast")
        {
            service = (new BreakfastRepository());
        }
        else if (mealTypeStr == "Lunch")
        {
            service = (new LunchRepository());
        }
        else if (mealTypeStr == "Dinner")
        {
            service = (new DinnerRepository());
        }
        else
        {
        }

        emp->setService(service);

        sendPrompt(socket, emp->getAllMenuItem());

        std::map<std::string, std::string> feedback;

        readMultipleFromSocket(socket, buffer, feedback);
        std::string id, comment, rating;
        id = feedback["ItemId"];
        comment = feedback["comment"];
        rating = feedback["rating"];
        emp->provideFeedback(std::stoi(id), comment, std::stod(rating));

        result = "Added feedback successfully\n";
    }
    else if (option == 4)
    {
        std::map<std::string, std::string> preferenceDetail;
        readMultipleFromSocket(socket, buffer, preferenceDetail);
        std::string dietary = preferenceDetail["Dietary Preference"];
        std::string spiceLevel = preferenceDetail["Spice Level"];
        std::string cuisine = preferenceDetail["Cuisine Preference"];
        std::string sweetToothStr = preferenceDetail["Sweet Tooth"];
        bool sweetTooth;
        if (sweetToothStr == "Yes")
        {
            sweetTooth = true;
        }
        else
        {
            sweetTooth = false;
        }
        Preference preference(emp->getId(), dietary, spiceLevel, cuisine, sweetTooth);
        emp->updateProfile(preference);
        sendPrompt(socket, "Preference updated");
    }
    else
    {
        result = "Invalid Option";
    }
    return result;
}

void *Server::handleClient(void *socket_desc)
{
    char buffer[BUFFER_SIZE] = {0};
    Server *server = (Server *)(socket_desc);
    int new_socket = server->server_fd;
    std::map<std::string, std::string> details;

    if (!server->readMultipleFromSocket(new_socket, buffer, details))
    {
        return server->handleAuthFailure(new_socket);
    }
    std::string username = details["username"];
    std::string password = details["password"];
    UserRepository userRepo;
    if (!userRepo.authenticateUser(username, password))
    {
        return server->handleAuthFailure(new_socket);
    }
    else
    {
        server->sendPrompt(new_socket, "Authentication Successful");
    }

    User *user = userRepo.getUserByUsername(username);
    std::string userRole = userRepo.getUserRole(username);
    server->sendPrompt(new_socket, userRole);
    LogService logService;
    logService.addLogInfo(user->getId(), "Logged in");
    std::string result;
    while (true)
    {
        if (userRole == "Admin")
        {
            result = server->handleAdmin(user, new_socket, buffer);
        }
        else if (userRole == "Chef")
        {
            result = server->handleChef(user, new_socket, buffer);
        }
        else if (userRole == "Employee")
        {
            result = server->handleEmployee(user, new_socket, buffer);
        }
        send(new_socket, result.c_str(), result.size(), 0);
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
    std::string response = menu + "\n";
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
    std::cout << buffer << std::endl;
    return std::stoi(buffer);
}

std::string Server::processViewItemsOption(Admin *admin, int socket, char *buffer)
{
    std::string mealTypeStr;
    if (!readFromSocket(socket, buffer, mealTypeStr))
        return "";

    MenuService service;
    if (mealTypeStr == "Breakfast")
    {

        service = (new BreakfastRepository());
    }
    else if (mealTypeStr == "Lunch")
    {
        service = (new LunchRepository());
    }
    else if (mealTypeStr == "Dinner")
    {
        service = (new DinnerRepository());
    }
    else
    {
        return "Invalid meal type entered.";
    }
    admin->setService(service);
    sendPrompt(socket, admin->getAllMenuItem());
}

void Server::closeSocket(int socket)
{
    close(socket);
    std::cout << "Connection disconnected" << std::endl;
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
