// Bank1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
const string ClientsFileName = "Clients.txt";
enum enPersonChoise { ShowClient = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4, FindClient = 5, Exit = 6 };
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;

};


vector<string>SplitString(string S1,string Delim)
{
	vector<string>vString;
	short Pos = 0;
	string sWord;
	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos);
		if (sWord != Delim)
		{
			vString.push_back(sWord);
		}
		S1.erase(0, Pos + Delim.length());
	}
		if (S1 !=Delim)
		{
			vString.push_back(S1);
		}
		return vString;
}
sClient ConvertLineToRecord(string S1, string Sperator = "#//#")
{
	sClient Client;
	vector<string>vClientData;
	vClientData = SplitString(S1, Sperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone =vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}
vector<sClient>LoadClienstDataFromFile(string FileName)
{
	vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		sClient Client;
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}
void PrintCLientRecord(sClient Client)
{
	
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(30) << left << Client.Name;
	cout << "| " << setw(15) << left << Client.Phone;
	cout << "| " << setw(15) << left << Client.AccountBalance;
	
}										
void PrintAllClientsData(vector<sClient>vClient)
{
	cout << "\t\t\t Client List (" << vClient.size() << ") Client(s) \t\t\t";
	cout << "\n______________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(30) << left << "Name";
	cout << "| " << setw(15) << left << "Phone";
	cout << "| " << setw(15) << left << "AccountBalance";
	cout << "\n______________________________________________________________________________________________\n" << endl;
	for (sClient Client : vClient)
	{
		PrintCLientRecord(Client);
		cout << endl;
    }
	cout << "\n_____________________________________________________________________________________________\n" << endl;

}
short ReadUserChoies(short Num)
{
	cout << " Choose what do you want to do? [1 to 6]? ";
	cin >> Num;
	return Num;

}
void ShowMainMenueScreen()
{
	cout << "===========================================================\n";
	cout << "\t\t Main Menue Screen \t\t\t\n";
	cout << "===========================================================\n";
	cout << "\t[1] Show Client List. \n";
	cout << "\t[2] Add New Client. \n";
	cout << "\t[3] Delete Client. \n";
	cout << "\t[4] Update Client Info. \n";
	cout << "\t[5] Find Client. \n";
	cout << "\t[6] Exit. \n";
	cout << "===========================================================\n";

}
void GoBackToMainMenueScreen()
{
	cout << "\nPress any key to go back to Main Menue...\n";
	system("cls");
	ShowMainMenueScreen();
}


sClient ReadNewClient()
{
	sClient Client;
	cout << "\n Enter your Account Number?.\n";
	getline(cin, Client.AccountNumber);
	cout << "\n Enter your PIN Code?.\n";
	getline(cin, Client.PinCode);
	cout << "\n Enter your Name?.\n";
	getline(cin, Client.Name);
	cout << "\n Enter your Phone Number?.\n";
	getline(cin, Client.Phone);
	cout << "\n Enter Account Balance?.\n";
	cin >> Client.AccountBalance;
	return Client;
}
string ConvertRecordToline(sClient Client,string Delim="#//#")
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Delim;
	stClientRecord += Client.PinCode + Delim;
	stClientRecord += Client.Name + Delim;
	stClientRecord += Client.Phone + Delim;
	stClientRecord +=to_string( Client.AccountBalance) + Delim;
	return stClientRecord;
}
void AddDataLineToFile(string FileName,string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddClient()
{
	sClient Client;
	Client = ReadNewClient();
	ConvertRecordToline(Client);
	AddDataLineToFile(ClientsFileName, ConvertRecordToline(Client));
}
void AddClients()
{
	char AddMore = 'Y';
	do 
	{
		system("cls");
		cout << "\nAdding new client \n";
		AddClient();

		cout << "Client Added successfully,do you want to add more ?\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}


string ReadClientAccountNumber(string AccountNumber)
{
	cout << "\nEnter Account Number to Delete ?\n";
	cin >> AccountNumber;
	return AccountNumber;
}
bool MarkCLientForDeleteByAccountNumber(string AccountNumber,vector<sClient>&vClients)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	
	}
	return false;

}
bool FindClientByAccountNumber(string AccountNumber,vector<sClient>vClients,sClient& Client)
{
	
	for (sClient S : vClients)
	{
		if (S.AccountNumber == AccountNumber)
		{
			Client = S;
			return true;
		}
	}
	return false;

}
int main()
{
	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);
	PrintAllClientsData(vClients);
	ShowMainMenueScreen();
	
	system("pause>0");
	return 0;
}

