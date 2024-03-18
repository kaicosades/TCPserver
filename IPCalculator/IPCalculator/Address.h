#pragma once
#include <iostream>
#include <string>
using namespace std;


class Address
{
	char a = '4';
	char address [20];
	char binary_address [20];
	//string address;
	//string binary_address;

public:
	char string[20] = "1";

	char get_addess()
	{
		return address[20];
	}

	void set_address(char* address )
	{
			strcpy(this->address, address);
		
	}


	Address(char address [])
	{
		set_address(address);
	}

	~Address()
	{

	}

	char CheckAddress()
	{
		int byte=0;
		int j = 0;
		int binary_byte = 0;
		int binary_i = 0;
		char binary_address [20];
		int bit = 8;
		const char *str = address;
		for (int i = 0; (address || j<4); i++)
		{
			if (((int)address[i] < 48 || (int)address[i] > 57) && (int)address[i] != 46)
			{
				cout << "invalid address";
				return string[20];
			}
			if ((int)address[i] == 46 && (byte < 0 || byte>255))
			{
				cout << "invalid address";
				return string[20];
			}
			if((int)address[i] == 46)
			{
				while (byte)
				{
					byte = byte / 2;
					binary_byte = binary_byte*10 + byte % 2;
					binary_i++;
				}
				byte = 0;
				i++;
				if (((int)address[i] < 48 || (int)address[i] > 57) && (int)address[i] != 46)
				{
					cout << "invalid address";
					return string[20];
				}
				j++;
			}
			byte =byte*10 + address[i]-'0';

			//for (int i = 0; i < bit - binary_i; i++)
			//{
				//добавть 0
			//}
			//добавить binary_byte
			// если j != 3
			//добавить точку
			binary_i = 0;
			binary_byte = 0;

			if (j == 4)
			{
				cout << "invalid address";
				return string[20];
			}
		}
		return a;
	}

};



