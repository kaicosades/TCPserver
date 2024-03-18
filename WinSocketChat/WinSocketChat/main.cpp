#define _CRT_SECURE_NO_WARNINGS // без этого не работает strcpy(sendMessage, client.SendDataMessage());
#include<string>
#include"ServerSocket.h"
#include"ClientSocket.h"

void main()
{
	setlocale(LC_ALL, "");
	CONST INT SIZE_NAME = 32;
	//string username[SIZE_NAME] = "Sever";
	int nChoice;
	int port = 22000;
	string ipAddress;
	char receiveMessage[MAXSTRLEN]{};
	char sendMessage[MAXSTRLEN]{};
	cout << "1. Start server" << endl;
	cout << "2. Connect to server" << endl;
	cout << "3. Exit" << endl;
	cin >> nChoice;
	switch (nChoice)
	{
	case 1:
	{
		ServerSocket server;
		cout << "Starting server" << endl;
		server.StartHosting(port);
		while (true)
		{
			//cout << "Waiting..." << endl;
			server.ReceiveData(receiveMessage, MAXSTRLEN);
			if (strstr(receiveMessage, "bye"))//break;
			{
				server.AcceptClient();
			}
			cout /*<< "Received: "*/ << receiveMessage << endl;
			server.SendDataMessage();
			if (strstr(sendMessage, "bye"))break;
		}
	}
	break;
	case 2:
	{
		string username;
		ipAddress = "127.0.0.1";
		//cout << "Enter IP address:";
		//cin >> ipAddress;
		cout << "Enter username: "; cin >> username;
		ClientSocket client = username;
		client.ConnectToServer(ipAddress.c_str(), port);
		while (true)
		{
			ZeroMemory(sendMessage, sizeof(sendMessage));
			ZeroMemory(receiveMessage, sizeof(receiveMessage));
			strcpy(sendMessage, client.SendDataMessage());
			if (strstr(sendMessage, "bye"))break;
			//cout << "Waiting" << endl;
			client.ReceiveData(receiveMessage, MAXSTRLEN);
			cout /*<< "Received: "*/ << receiveMessage << endl;
			if (strstr(receiveMessage, "bye"))break; //стрстр возвращает адрес подстроки, либо NULL
		}
		client.CloseConnection();
	}
	break;
	} // последние минуты 3-4 не записывал, как сказал препод
}