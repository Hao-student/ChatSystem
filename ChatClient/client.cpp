#include <iostream>
#include <string>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <conio.h>
#include <Windows.h>

#pragma comment(lib,"Ws2_32.lib")
using namespace std;
#define BUFFERSIZE 100 //��������С

int main(int argc, char* argv[])
{
	//client��������
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

	//���� TCP socket
	SOCKET tcpS;
	tcpS = socket(AF_INET, SOCK_STREAM, 0);
	if (tcpS == SOCKET_ERROR)
	{
		cout << "socket() failed" << endl;
		WSACleanup();
		return 0;
	}

	//����server��ַ
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	inet_pton(AF_INET, argv[1], &serverAddr.sin_addr.S_un.S_addr);
	serverAddr.sin_port = htons(atoi(argv[2]));

	//���û���������ʼ��
	char sendBuf[BUFFERSIZE] = "";
	char recvBuf[BUFFERSIZE] = "";
	memset(sendBuf, 0, BUFFERSIZE);
	memset(recvBuf, 0, BUFFERSIZE);

	//����server
	err = connect(tcpS, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	if (err == SOCKET_ERROR)
	{
		cout << "Fail to connect" << endl;
		WSACleanup();
		return 0;
	}
	cout << "���ӷ������ɹ���������IP��" << argv[1] << endl;
	cout << endl;

	char username[100] = "";
	char password[100] = "";
	cout << "���Ƚ��е�¼" << endl;
	int i=0;
	while (i == 0)
	{
		cout << endl;
		cout << "�������û�����";
		cin.getline(username, 10);
		if (strcmp(username, "aa") == 0 || strcmp(username, "bb") == 0)
		{
			cout << "���������룺";
			cin.getline(password, 100);
			if (strcmp(username, "aa") == 0)
			{
				if (strcmp(password, "123") == 0)
				{
					cout << "��¼�ɹ�" << endl;
					i = 1;
				}
				else
				{
					cout << "������������³���" << endl;
					continue;
				}
			}
			if (strcmp(username, "bb") == 0)
			{
				if (strcmp(password, "789") == 0)
				{
					cout << "��¼�ɹ�" << endl;
					i = 1;
				}
				else
				{
					cout << "������������³���" << endl;
					continue;
				}

			}
		}
		else
		{
			cout << "���û������ڣ������³���" << endl;
			continue;
		}
	}

	cout << endl;
	cout << "���ڿ��Կ�ʼ������" << endl;
	cout << "��ʾ��������Ϣʱ�뽫��Ϣ�����ڡ��û���������" << endl;
	cout << endl;
	cout << "�Ƿ�������-yes/no:" ;
	char selection[20] = "";
	cin.getline(selection, 20);
	cout << endl;
	if (strcmp(selection, "yes") == 0)
	{
		while (1)
		{
			int msg;
			cout << "������Ϣ--" << username << ": ";
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
					cout << "������Ϣ--bb: " << recvBuf << endl;
				}
				if (strcmp(username, "bb") == 0)
				{
					cout << "������Ϣ--aa: " << recvBuf << endl;
				}
			}
			if (recvBuf == 0)
			{
				cout << "�޽�����Ϣ" << recvBuf << endl;
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
					cout << "������Ϣ--bb: " << recvBuf << endl;
				}
				if (strcmp(username, "bb") == 0)
				{
					cout << "������Ϣ--aa: " << recvBuf << endl;
				}
			}
			if (recvBuf == 0)
			{
				cout << "�޽�����Ϣ" << recvBuf << endl;
			}
			memset(recvBuf, 0, BUFFERSIZE);
			cout << "������Ϣ--" << username << ": ";
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