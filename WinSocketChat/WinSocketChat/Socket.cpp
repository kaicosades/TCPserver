#include"Socket.h"

Socket::Socket()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		cerr << "WSAStartup error" << endl; // cerr - тоже что и cout, но только об ошибках
		system("PAUSE");
		WSACleanup();
		exit(10);
	}
	_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_socket == INVALID_SOCKET)
	{
		cerr << "Socket creation eroor" << endl;
		system("PAUSE");
		WSACleanup();
		exit(11);
	}
}

Socket::Socket(string username):Socket()
{
	this->username = username;
}

Socket::~Socket()
{
	WSACleanup(); // чиста ресурсов
}

bool Socket::SendData(char* buffer)
{
	send(acceptSocket, buffer, strlen(buffer),0);
	//send(_socket, buffer, strlen(buffer),0);
	return true;
}

bool Socket::ReceiveData(char* buffer, int size)
{
	INT i = recv(_socket, buffer,size, 0);
	return true;
}

void Socket::CloseConnection()
{
	cout <<"Connection closing..." << endl;
	closesocket(_socket);
}

CONST CHAR* Socket::SendDataMessage()
{
	CHAR message[MAXSTRLEN]{};
	CHAR buffer[MAXSTRLEN]{};
	ZeroMemory(message, sizeof(message));
	ZeroMemory(buffer, sizeof(buffer));
	cout << "Enter message: ";
	cin.ignore(); // если не пишется при вызове
	cin.get(buffer, MAXSTRLEN);
	sprintf(message, "%s: %s", username.c_str(), buffer);
	SendData(message);
	return message;
}
