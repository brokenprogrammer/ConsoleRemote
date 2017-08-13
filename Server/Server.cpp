#include "Server.h"
#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib,"WS2_32")

#define DEFAULT_BUFLEN 512

Server::Server()
{

}

Server::~Server()
{

}

void Server::startServer()
{
	std::cout << "Starting server..." << std::endl;

	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo hints = init();
	struct addrinfo *result = nullptr;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

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

	std::cout << "Listening on port.. xxx" << std::endl;

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

	// Cleanup.
	closesocket(ClientSocket);
	WSACleanup();
}

void Server::listening()
{
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