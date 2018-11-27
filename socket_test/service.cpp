#include <iostream>
#include <stdio.h>
#include <WINSOCK2.H>

using namespace std;

// 服务端

#define PORT 5150
#define MSGSIZE 1024

#pragma(lib, "ws2_32.lib")

int mian(int argc, char* argv[]) {
	const int BUF_SIZE = 64;
	WSADATA		wsd;	// WAADATA变量
	SOCKET		server_socket;	// 服务器套接字
	SOCKET		client_socket;	// 客户端套接字
	SOCKADDR_IN		server_address;	// 服务器地址
	char		buf[BUF_SIZE];	//接收数据缓冲区
	char		sendBuf[BUF_SIZE];	//返回给客户端得数据
	int			returnValue;			//返回值

	// 初始化套结字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		cout << " 初始化套接字动态库失败 " << endl;
		return 1;
	}

	// 创建套接字
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == server_socket) {
		cout << " 创建套接字失败 " << endl;
		// 释放套接字
		WSACleanup();
		return -1;
	}

	// 服务器套接字地址
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4999);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// 绑定套接字
	returnValue = bind( server_socket, (LPSOCKADDR)&server_address, sizeof(SOCKADDR_IN) );
	if (SOCKET_ERROR == returnValue) {
		cout << " 绑定套接字失败 " << endl;
		// 关闭套接字
		closesocket(server_socket);
		// 释放套接字
		WSACleanup();
		return -1;
	}

	// 监听
	returnValue = listen(server_socket, 1);
	if (SOCKET_ERROR == returnValue) {
		cout << " 监听失败 " << endl;
		// 关闭套接字
		closesocket(server_socket);
		// 释放套接字
		WSACleanup();
		return -1;
	}

	// 接受客户端请求
	sockaddr_in clientAddress;	// 客户端地址
	int clientAddressLength = sizeof(clientAddress);
	client_socket = accept(server_socket, (sockaddr FAR*) &clientAddress, &clientAddressLength);
	if (INVALID_SOCKET == client_socket) {
		cout << " 客户端请求接受失败 " << endl;
		closesocket(server_socket);	//关闭套接字
		WSACleanup();			//释放套接字资源;
		return -1;
	}

	// 接受客户端数据
	while (true) {
		ZeroMemory(buf, BUF_SIZE);
		returnValue = recv(client_socket, buf, BUF_SIZE, 0);
		if (SOCKET_ERROR == returnValue) {
			cout << " 接受数据失败 " << endl;
			// 关闭套接字
			closesocket(server_socket);
			// 释放套接字
			WSACleanup();
			return -1;
		}

		if (buf[0] == '0') {
			break;
		}

		cout << "发送的数据: " << endl;
		cin >> sendBuf;

		// 发送数据
		send(client_socket, sendBuf, strlen(sendBuf), 0);
	}

	// 退出
	closesocket(server_socket);	//关闭服务端套接字
	closesocket(client_socket);	//关闭客户端套接字
	WSACleanup();			//释放套接字资源;
		
	return 0;
}