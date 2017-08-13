#ifndef SERVER_H
#define SERVER_H
#pragma once


class Server
{
public:
	Server();
	Server(const Server&) = default;
	~Server();

	Server& operator =(const Server&) = default;

	void startServer();

private:
	void listening();
	struct addrinfo init();
};

#endif