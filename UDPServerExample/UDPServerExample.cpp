#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <winsock2.h> 
#include <ws2tcpip.h> 

#pragma comment(lib, "ws2_32.lib")

int InitializeServer(const char* ip, u_short port) {

	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ip);

	bind(s, (struct sockaddr*)&serverAddr, sizeof serverAddr); 
	printf("Server is listening on %s : %u\n", ip, port);

	char buffer[1024];
	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);

	int receivedBytes = recvfrom(s, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrSize);

	int sentBytes = sendto(s, buffer, receivedBytes, 0, (struct sockaddr*)&clientAddr, clientAddrSize);
	
	if (receivedBytes) {
		printf("received %d bytes from client\n", sentBytes);
	}

	if (sentBytes) {
		printf("Sent %d bytes to client\n", sentBytes);
	}

	return 0; 
}

void main() {

	std::string specifiedIp;
	printf("What IP do you want to run the server in?\n");
		std::cin >> specifiedIp;

		u_short port;
		printf("Which port do you want to use for the server?\n");
			printf("(If you're running the server over the internet, you will have to forward said port)\n");
		std::cin >> port;

	InitializeServer(specifiedIp.c_str(), port);

}