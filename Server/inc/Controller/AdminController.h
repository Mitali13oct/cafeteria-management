// AdminController.h
#ifndef ADMIN_CONTROLLER_H
#define ADMIN_CONTROLLER_H

#include "Admin.h"
#include"Server.h"
#include <string>
class AdminController {
public:
    std::string processOption(Admin* admin, int option, int socket, char* buffer);
    std::string processViewItemsOption(Admin *admin, int socket, char *buffer);
    

};

#endif // ADMIN_CONTROLLER_H