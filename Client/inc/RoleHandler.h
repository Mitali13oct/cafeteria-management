#pragma once

#include "Client.h"

class RoleHandler
{
public:
    virtual bool handleOptions(Client &client) = 0;
    virtual ~RoleHandler() = default;
};


