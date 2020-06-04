#pragma once

#include "main.h"

class IClient
{
public:
	virtual void readString() = 0;
	virtual void printString() = 0;

protected:
	virtual ~IClient() {};
};

class Client : public IClient
{
public:
	Client(char p);
	void readString();
	void printString();

protected:
	~Client();

private:
	int c_sock; // дескриптор сокета
	struct sockaddr_in c_addr; // структура с адресом
	char protokol; // хранит протокол, по которому будет происходить обмен данными
	string message; // хранит строку, которая отправляется на сервер
	string buffer; // хранит строку, полученную от сервера
	void handle();
};

