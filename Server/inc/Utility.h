#include <iostream>
#include <vector>
#include "User.h"
#include "MenuItem.h"
#include "sstream"
class Utility
{

public:
    static std::string showMenu(const User &user)
    {
        std::vector<std::string> options;
        if (user.getRole() == "Admin")
        {
            options = showAdminMenu();
        }
        else if (user.getRole() == "Chef")
        {
            options = showChefMenu();
        }
        else if (user.getRole() == "Employee")
        {
            options = showEmployeeMenu();
        }
        else
        {
            std::cerr << "Unknown role: " << user.getRole() << std::endl;
        }
        std::ostringstream oss;
        for (const auto &option : options)
        {
            oss << option << "\n";
        }
        return oss.str();
    }

private:
    static std::vector<std::string> showAdminMenu()
    {
        return {"1. Add Menu Item\n2. Update Menu Item\n3. Delete Menu Item\n4. View All Menu Items"};
        // Additional admin options here
    }

    static std::vector<std::string> showChefMenu()
    {
        return {"1. View Menu Items\n2. Generate Monthly Report\n3. Send Notification\n"};

        // Additional chef options here
    }

    static std::vector<std::string> showEmployeeMenu()
    {
        return {"1. Choose Menu Item\n2. Provide Feedback\n3. View Notifications\n"};

        // Additional employee options here
    }
};
