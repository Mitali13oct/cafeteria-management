#pragma once
#include<iostream>
class AuthenticationService
{

public:
    virtual bool login(std::string username, std::string password)=0;
};


