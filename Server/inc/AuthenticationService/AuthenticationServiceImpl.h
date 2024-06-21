#pragma Once
#include "AuthenticationService.h"
#include "UserRepository.h"
class AuthenticationServiceImpl : public AuthenticationService
{
private:
    UserRepository users;

public:
    AuthenticationServiceImpl(UserRepository &users) : users(users) {}

    bool login(std::string username, std::string password);
};
