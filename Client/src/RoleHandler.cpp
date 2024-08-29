#ifndef ROLEHANDLER_H
#define ROLEHANDLER_H

#include "Client.h"

class RoleHandler
{
public:
    virtual bool handleOptions(Client &client) = 0;
    virtual ~RoleHandler() = default;
};


#endif // ROLEHANDLER_H
