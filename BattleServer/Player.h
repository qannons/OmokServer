#pragma once
#include "Session.h"

class Player : public Session
{
public:
	bool waitingForGame = false;
	INT16 elo = 1500;

private:
	INT32 _ID = -1;
	string _name = u8"default name";
	SOCKET _battleSocket;

public:
	Player() : Session()
	{
		_battleSocket = ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	}

public:

	virtual void Connect(INT16 port=0) override;

	void setName(string&& pName)
	{
		_name = move(pName);
	}
	void setInfo(BYTE* buffer, INT32 len);

	const string getName()
	{
		return _name;
	}

	SOCKET GetBattleSocket()
	{
		return _battleSocket;
	}
	// Session을(를) 통해 상속됨
	void HandlePacket(BYTE* buffer, INT32 len, ePacketID ID) override;
};

