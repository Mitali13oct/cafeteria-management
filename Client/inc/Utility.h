#include <iostream>
#include <vector>
// #include "User.h"
// #include "MenuItem.h"
#include "sstream"
class Utility
{

public:
    static std::string showMenu(std::string role)
    {
        std::vector<std::string> options;
        if (role== "Admin\n")
        {
            options = showAdminMenu();
        }
        else if (role== "Chef\n")
        {
            options = showChefMenu();
        }
        else if (role == "Employee\n")
        {
            options = showEmployeeMenu();
        }
        else
        {
            std::cerr << "Unknown role: " << role<< std::endl;
        }
        std::ostringstream oss;
        for (const auto &option : options)
        {
            oss << option << "\n";
        }
        return oss.str();
    }
    static std::string menuItemString(){
        return "Enter Item Details \n ";
    }
     static int discardItem(){
       std::cout<<"Do you want to\n1. Delete Item\n2. Get Personalized Feedback on item\n";
       int option;
       std::cin>>option;
       return option;
    }
private:
    static std::vector<std::string> showAdminMenu()
    {
        return {"1. Add Menu Item\n2. Update Menu Item\n3. Delete Menu Item\n4. View All Menu Items\n5. View Discarded Items"};
       
    }

    static std::vector<std::string> showChefMenu()
    {
        return {"1. Get Recommendations from Engine\n2. Roll out item from recommendation\n3. Choose item to prepare\n4. View Discarded items"};

        
    }

    static std::vector<std::string> showEmployeeMenu()
    {
        return {"1. Vote on recommendation \n2. View Notifications\n3. Provide Feedback"};

       
    }
   
};
