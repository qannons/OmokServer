﻿#include "pch.h"
#include "SocketUtils.h"
#include "PacketHeader.h"
#include "LobbyRoomManager.h"
#include "Protocol.pb.h"
#include "BattleServerSession.h"
#include "PacketHandler.h"
#include "LobbyPlayer.h"
#include "PlayerListener.h"
#include "ServerListener.h"

int main()
{
    SocketUtils::Init();
    GLobbyRoomManager.Init();
    PlayerListener playerListener(L"127.0.0.1", 7777);
    ServerListener serverListener(L"127.0.0.1", 7788);

    GBattleServer = make_shared<BattleServerSession>();
    GBattleServer->Connect(8877);

    vector<thread> workerThreads;

    for (int i = 0; i < 5; ++i)
    {
        workerThreads.push_back(thread([=]() {
            while (true)
                GIocpCore.Dispatch();
            }));
    }

    thread tPlayerListener(&Listener::StartAccept, &playerListener);
    thread tServerListener(&Listener::StartAccept, &serverListener);

    // 모든 스레드가 종료될 때까지 대기
    for (auto& workerThread : workerThreads)
        workerThread.join();
    tPlayerListener.join();
    tServerListener.join();

    return 0;
}

