#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <cstdio>
#include <vector>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define BUFFERSIZE 100 //缓存区大小

vector<int> sockets;//声明全局变量vector，用于存储所有的socket

//服务线程
DWORD WINAPI ServerThread(LPVOID lpParameter)
{
	SOCKET* ClientSocket = (SOCKET*)lpParameter;
	sockets.push_back(*ClientSocket);
	int msg;
	int smsg;
	char buff[BUFFERSIZE];
	cout << endl;
	while (1)
	{
		msg = recv(*ClientSocket, buff, sizeof(buff), 0);
		cout << "接收消息：" << buff << endl;
		cout << "来自客户端：" << *ClientSocket << endl;
		if (*ClientSocket == sockets[0])
		{
			smsg = send(sockets[1], buff, sizeof(buff), 0);
			cout << "发送该消息至客户端：" << sockets[1] << endl;
		}
		if (*ClientSocket == sockets[1])
		{
			smsg = send(sockets[0], buff, sizeof(buff), 0);
			cout << "发送该消息至客户端：" << sockets[0] << endl;
		}
		if (smsg == SOCKET_ERROR)
		{
			cout << "send() failed" << endl;
			break;
		}
		cout << endl;
		memset(buff, 0, sizeof(buff));
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	return 0;
}

int main(int argc, char* argv[])
{
	//server端输入检查
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " Server_port" << endl;
		return 0;
	}

	int err;
	WORD wVersion;
	WSAData wData;
	wVersion = MAKEWORD(2, 2);
	err = WSAStartup(wVersion, &wData);
	if (err != 0)
	{
		cout << "Fail to load socket dll" << endl;
		return 0;
	}

	//创建监听socket
	SOCKET lisSocket;
	lisSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (lisSocket == SOCKET_ERROR)
	{
		cout << "socket() failed" << endl;
		WSACleanup();
		return 0;
	}

	//设置server地址
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr=htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(argv[1]));

	//绑定并监听
	int ret;
	ret = bind(lisSocket, (LPSOCKADDR)&serverAddr, sizeof(sockaddr_in));
	if (ret == SOCKET_ERROR)
	{
		cout << "bind() failed" << endl;
		WSACleanup();
		return 0;
	}
	if (listen(lisSocket, 10) == SOCKET_ERROR)
	{
		cout << "listen() failed" << endl;
		WSACleanup();
		return 0;
	}
	cout << "服务器IP：127.0.0.1" << endl;
	cout << "服务器端口号: " << argv[1] << endl;
	cout << "监听中..." << endl;
	cout << endl;

	//收发消息
	while (1)
	{
		//循环接收客户端连接请求并创建服务线程
		SOCKET *ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//接收客户端连接请求
		int len = sizeof(sockaddr);
		*ClientSocket = accept(lisSocket, 0, 0);
		cout << "一个客户端已连接到服务器，socket：" << *ClientSocket << endl;
		CreateThread(NULL, 0, &ServerThread, ClientSocket, 0, NULL);
	}
	closesocket(lisSocket);
	WSACleanup();
	return 0;
}
