#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <conio.h>
#include <Windows.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define BUFFERSIZE 100 //缓存区大小

int main(int argc, char* argv[])
{
	//client端输入检查
	if (argc != 3)
	{
		cout << "Usage: "<<argv[0]<<" Server_IP Server_port" << endl;
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

	//创建 TCP socket
	SOCKET tcpS;
	tcpS = socket(AF_INET, SOCK_STREAM, 0);
	if (tcpS == SOCKET_ERROR)
	{
		cout << "socket() failed" << endl;
		WSACleanup();
		return 0;
	}

	//设置server地址
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &serverAddr.sin_addr.S_un.S_addr);
	serverAddr.sin_port = htons(atoi(argv[2]));

	//设置缓冲区并初始化
	char sendBuf[BUFFERSIZE] = "";
	char recvBuf[BUFFERSIZE] = "";
	memset(sendBuf, 0, BUFFERSIZE);
	memset(recvBuf, 0, BUFFERSIZE);

	//连接server
	err = connect(tcpS, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (err == SOCKET_ERROR)
	{
		cout << "Fail to connect" << endl;
		WSACleanup();
		return 0;
	}
	cout << "连接服务器成功，服务器IP：" << argv[1] << endl;
	cout << endl;

	char username[100] = "";
	char password[100] = "";
	cout << "请先进行登录" << endl;
	int i=0;
	while (i == 0)
	{
		cout << endl;
		cout << "请输入用户名：";
		cin.getline(username, 10);
		if (strcmp(username, "aa") == 0 || strcmp(username, "bb") == 0)
		{
			cout << "请输入密码：";
			cin.getline(password, 100);
			if (strcmp(username, "aa") == 0)
			{
				if (strcmp(password, "123") == 0)
				{
					cout << "登录成功" << endl;
					i = 1;
				}
				else
				{
					cout << "密码错误，请重新尝试" << endl;
					continue;
				}
			}
			if (strcmp(username, "bb") == 0)
			{
				if (strcmp(password, "789") == 0)
				{
					cout << "登录成功" << endl;
					i = 1;
				}
				else
				{
					cout << "密码错误，请重新尝试" << endl;
					continue;
				}

			}
		}
		else
		{
			cout << "该用户不存在，请重新尝试" << endl;
			continue;
		}
	}

	cout << endl;
	cout << "现在可以开始聊天了" << endl;
	cout << "提示：发送消息时请将消息输入在‘用户名：’后" << endl;
	cout << endl;
	cout << "是否发起聊天-yes/no:" ;
	char selection[20] = "";
	cin.getline(selection, 20);
	cout << endl;
	if (strcmp(selection, "yes") == 0)
	{
		while (1)
		{
			int msg;
			cout << "发送消息--" << username << ": ";
			cin.getline(sendBuf, 50);
			msg = send(tcpS, sendBuf, sizeof(sendBuf), 0);
			if (msg == SOCKET_ERROR)
			{
				cout << "send() failed" << endl;
				break;
			}
			memset(sendBuf, 0, BUFFERSIZE);
			msg = recv(tcpS, recvBuf, BUFFERSIZE, 0);
			if (recvBuf != 0)
			{
				if (strcmp(username, "aa") == 0)
				{
					cout << "接收消息--bb: " << recvBuf << endl;
				}
				if (strcmp(username, "bb") == 0)
				{
					cout << "接收消息--aa: " << recvBuf << endl;
				}
			}
			if (recvBuf == 0)
			{
				cout << "无接收消息" << recvBuf << endl;
			}
			memset(recvBuf, 0, BUFFERSIZE);
		}
	}
	if (strcmp(selection, "no") == 0)
	{
		while (1)
		{
			int msg;
			msg = recv(tcpS, recvBuf, BUFFERSIZE, 0);
			if (recvBuf != 0)
			{
				if (strcmp(username, "aa") == 0)
				{
					cout << "接收消息--bb: " << recvBuf << endl;
				}
				if (strcmp(username, "bb") == 0)
				{
					cout << "接收消息--aa: " << recvBuf << endl;
				}
			}
			if (recvBuf == 0)
			{
				cout << "无接收消息" << recvBuf << endl;
			}
			memset(recvBuf, 0, BUFFERSIZE);
			cout << "发送消息--" << username << ": ";
			cin.getline(sendBuf, 50);
			msg = send(tcpS, sendBuf, sizeof(sendBuf), 0);
			if (msg == SOCKET_ERROR)
			{
				cout << "send() failed" << endl;
				break;
			}
			memset(sendBuf, 0, BUFFERSIZE);
		}
	}
	
	closesocket(tcpS);
	WSACleanup();
	return 0;
}