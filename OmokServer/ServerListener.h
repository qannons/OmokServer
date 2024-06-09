#pragma once
#include "Listener.h"
#include "BattleServerSession.h"

class ServerListener : public Listener
{
public:
    ServerListener(wstring ip, INT16 port) : Listener(ip, port, []() { return make_shared<BattleServerSession>(); })
    {

    }
};

