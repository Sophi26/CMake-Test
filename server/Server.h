#pragma once

#include "main.h"

class IServer
{
public:
	virtual void startServer() = 0;
	virtual void closeServer() = 0;

protected:
	virtual ~IServer() {};
};

class Server: public IServer
{
public:
	Server(char p);
	void startServer();
	void closeServer();

protected:
	~Server();

private:
	int this_s; // дескриптор сокета
	struct sockaddr_in address; // структура с адресом
	char protokol; // хранит протокол, по которому будет происходить обмен данными
	void handle_TCP();
	void handle_UDP();
	void rec_send_mess(int sc);
	void get_numbers(string &result, string &sum, const string &s);
};