#include <iostream>
#include <stdio.h>
#include <WINSOCK2.H>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

// 客户端

const int BUF_SIZE = 64;
int client() {

	WSADATA wsd;
	SOCKET server_socket;	// 服务器套接字
	SOCKADDR_IN server_address;		// 服务器地址
	char buf[BUF_SIZE];		//接收数据缓冲区
	char bufRecv[BUF_SIZE];
	int retyrnValue;		//返回值

	// 初始化套接字动态库
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		cout << " 初始化套接字动态库失败 " << endl;
		return -1;
	}

	// 创建套接字
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == server_socket) {
		cout << "创建套接字失败" << endl;
		WSACleanup();
		return -1;
	}
} 
