#include "Server.h"
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>
#include "ActionParser.h"
#include <string>
#include <vector>

#pragma comment(lib,"WS2_32")

Server::Server()
{
	ListenSocket = INVALID_SOCKET;
	ClientSocket = INVALID_SOCKET;

	hints = init();
	result = nullptr;
}

Server::~Server()
{
	closesocket(ClientSocket);
	WSACleanup();
}

void Server::startServer()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return;
	}

	// Resolve the local address and port to be used by the server
	iResult = getaddrinfo(NULL, "27015", &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return;
	}

	//Create socket to listen for incoming connections & validate.
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return;
	}

	//Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	//Once bound the result is no longer needed.
	freeaddrinfo(result);
}

void Server::startListen()
{
	//Listen to the socket.
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	std::cout << "Finished listening.." << std::endl;
	
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return;
	}

	std::cout << "Accepted connection.. " << std::endl;

	// No longer need server socket
	closesocket(ListenSocket);

	// Recieve stuff from the socket..
	do {
		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			handleMessage(recvbuf, iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return;
		}

	} while (iResult > 0);

	// Shutdown the connection when finished.
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return;
	}
}

struct addrinfo Server::init()
{
	struct addrinfo hints; 

	ZeroMemory(&hints, sizeof(hints)); //Populates hints with 0.
	hints.ai_family   = AF_INET;	   //Specify the IPv4 address family.
	hints.ai_socktype = SOCK_STREAM;   //Specify a stream socket.
	hints.ai_protocol = IPPROTO_TCP;   //Specify the TCP protocol.
	hints.ai_flags    = AI_PASSIVE;    //Flag indicates the caller intends 
									   //to use the returned socket address

	return hints;
}

void Server::handleMessage(const char *pMessage, size_t len)
{
	std::vector<std::string> commandList = parser.parseMessage(std::string(pMessage, len));
	actionHandler.handleAction(commandList);
}