#include <iostream>
#include <stdio.h>
#include <WINSOCK2.H>
#pragma comment(lib, "Ws2_32.lib")

using namespace std;

// �ͻ���

const int BUF_SIZE = 64;
int client() {

	WSADATA wsd;
	SOCKET server_socket;	// �������׽���
	SOCKADDR_IN server_address;		// ��������ַ
	char buf[BUF_SIZE];		//�������ݻ�����
	char bufRecv[BUF_SIZE];
	int retyrnValue;		//����ֵ

	// ��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		cout << " ��ʼ���׽��ֶ�̬��ʧ�� " << endl;
		return -1;
	}

	// �����׽���
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == server_socket) {
		cout << "�����׽���ʧ��" << endl;
		WSACleanup();
		return -1;
	}
} 
