
#include "Server/inc/AuthenticationService/AuthenticationServiceImpl.h"
bool AuthenticationServiceImpl::login(std::string username, std::string password)
{
    bool isUser = users.authenticateUser(username, password);
    return isUser;
}
