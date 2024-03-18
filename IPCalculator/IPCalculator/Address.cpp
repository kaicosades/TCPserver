#include "Address.h"

//#include <string>
#include <iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	cout << "¬ведите IP адресс: ";
	char ip [20];
	cin >> ip;
	//char mask[20];
	//mask = ip;
	Address IPAddress(ip);
	IPAddress.CheckAddress();
	//cin >>
}
