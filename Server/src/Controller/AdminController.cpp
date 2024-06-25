
#include "AdminController.h"

    std::string AdminController::processOption(Admin* admin, int option, int socket, char* buffer){
        std::string result;
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
            processViewItemsOption(admin, socket, buffer);
            std::string extra;

            std::string id, column, value;
            sendPrompt(socket, "Enter item id to edit: ");
            readFromSocket(socket, buffer, id);

            sendPrompt(socket, "Enter column name to edit: ");
            readFromSocket(socket, buffer, column);

            sendPrompt(socket, "Enter value to update: ");
            readFromSocket(socket, buffer, value);
            int id1 = std::stoi(id);
            admin->updateMenuItem(id1, column, value);

            result = "Item updated successfully.";
        }
        else if (option == 3)
        {
            result = "Delete Menu Item";
            processViewItemsOption(admin, socket, buffer);
            std::string id;
            sendPrompt(socket, "Enter item id to delete: ");
            readFromSocket(socket, buffer, id);
            int id1 = std::stoi(id);
            admin->deleteItem(id1);
        }
        else if (option == 4)
        {
            processViewItemsOption(admin, socket, buffer);
        }
        else
        {
            result = "Invalid Option";
        }
    }
    std::string AdminController::processViewItemsOption(Admin *admin, int socket, char *buffer)
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

