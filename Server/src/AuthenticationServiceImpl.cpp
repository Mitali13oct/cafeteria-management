
#include "../inc/AuthenticationServiceImpl.h"
bool AuthenticationServiceImpl::login(std::string username, std::string password)
{
    try
    {
        User *user = users.getUserByUsername(username);
        if (user->getPassword() == password)
        {
            // Perform additional login actions if necessary
            delete user; // Don't forget to delete the user object after use
            return true;
        }
        delete user;
    }
    catch (const std::runtime_error &e)
    {
        // Handle user not found or other errors
    }
    return false;
}
