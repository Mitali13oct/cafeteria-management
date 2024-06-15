#pragma Once
#include "UserRepository.h"
#include "AuthenticationService.h"
class AuthenticationServiceImpl : public AuthenticationService
{
private:
    UserRepository users;

public:
    AuthenticationServiceImpl(UserRepository &users) : users(users) {}

    bool login(std::string username, std::string password);
};
