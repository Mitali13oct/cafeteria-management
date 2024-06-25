// ChefController.h
#ifndef CHEF_CONTROLLER_H
#define CHEF_CONTROLLER_H

#include "Chef.h"
#include"Server.h"
#include"FeedbackService.h"

class ChefController {
public:
    std::string processOption(Chef* chef, int option, int socket, char* buffer);
};

#endif // CHEF_CONTROLLER_H