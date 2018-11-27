#include <iostream>
#include <stdio.h>
#include <WINSOCK2.H>

using namespace std;

// �����

#define PORT 5150
#define MSGSIZE 1024

#pragma(lib, "ws2_32.lib")

int mian(int argc, char* argv[]) {
	const int BUF_SIZE = 64;
	WSADATA		wsd;	// WAADATA����
	SOCKET		server_socket;	// �������׽���
	SOCKET		client_socket;	// �ͻ����׽���
	SOCKADDR_IN		server_address;	// ��������ַ
	char		buf[BUF_SIZE];	//�������ݻ�����
	char		sendBuf[BUF_SIZE];	//���ظ��ͻ��˵�����
	int			returnValue;			//����ֵ

	// ��ʼ���׽��ֶ�̬��
	if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0) {
		cout << " ��ʼ���׽��ֶ�̬��ʧ�� " << endl;
		return 1;
	}

	// �����׽���
	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == server_socket) {
		cout << " �����׽���ʧ�� " << endl;
		// �ͷ��׽���
		WSACleanup();
		return -1;
	}

	// �������׽��ֵ�ַ
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(4999);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// ���׽���
	returnValue = bind( server_socket, (LPSOCKADDR)&server_address, sizeof(SOCKADDR_IN) );
	if (SOCKET_ERROR == returnValue) {
		cout << " ���׽���ʧ�� " << endl;
		// �ر��׽���
		closesocket(server_socket);
		// �ͷ��׽���
		WSACleanup();
		return -1;
	}

	// ����
	returnValue = listen(server_socket, 1);
	if (SOCKET_ERROR == returnValue) {
		cout << " ����ʧ�� " << endl;
		// �ر��׽���
		closesocket(server_socket);
		// �ͷ��׽���
		WSACleanup();
		return -1;
	}

	// ���ܿͻ�������
	sockaddr_in clientAddress;	// �ͻ��˵�ַ
	int clientAddressLength = sizeof(clientAddress);
	client_socket = accept(server_socket, (sockaddr FAR*) &clientAddress, &clientAddressLength);
	if (INVALID_SOCKET == client_socket) {
		cout << " �ͻ����������ʧ�� " << endl;
		closesocket(server_socket);	//�ر��׽���
		WSACleanup();			//�ͷ��׽�����Դ;
		return -1;
	}

	// ���ܿͻ�������
	while (true) {
		ZeroMemory(buf, BUF_SIZE);
		returnValue = recv(client_socket, buf, BUF_SIZE, 0);
		if (SOCKET_ERROR == returnValue) {
			cout << " ��������ʧ�� " << endl;
			// �ر��׽���
			closesocket(server_socket);
			// �ͷ��׽���
			WSACleanup();
			return -1;
		}

		if (buf[0] == '0') {
			break;
		}

		cout << "���͵�����: " << endl;
		cin >> sendBuf;

		// ��������
		send(client_socket, sendBuf, strlen(sendBuf), 0);
	}

	// �˳�
	closesocket(server_socket);	//�رշ�����׽���
	closesocket(client_socket);	//�رտͻ����׽���
	WSACleanup();			//�ͷ��׽�����Դ;
		
	return 0;
}