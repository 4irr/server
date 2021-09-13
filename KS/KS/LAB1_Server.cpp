#pragma comment(lib, "ws2_32.lib")
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	SOCKET  s = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	
	int c = bind(s, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s, 5);
	
	char buf[255];
	char Res[255];

	while (true) {
		//структура определяет удаленный адрес,
		//с которым  соединяется сокет
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET	s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
		while (recv(s2, buf, sizeof(buf), 0) != 0) {
			int ax, ay, bx, by, cx, cy;
			//преобразование данных из строки в координаты типа int
			ax = buf[0] - '0';
			ay = buf[1] - '0';
			bx = buf[2] - '0';
			by = buf[3] - '0';
			cx = buf[4] - '0';
			cy = buf[5] - '0';

			(cx<ax&& cy < ay&& cx > bx&& cy>by) ? strcpy(Res, "YES") : strcpy(Res, "NO");

			//Посылает данные на соединенный сокет
			send(s2, Res, sizeof(Res), 0);
		}
		closesocket(s2);
	}
	WSACleanup();
}
