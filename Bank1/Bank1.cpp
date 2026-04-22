
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
using namespace std;
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";

enum enMainMenueOptions {
	eListClient = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6,
	eManageUsers=7,eLogOut=8 
};
enum enTransactionsMenueOptions {
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalance = 3, eShowMainMenue = 4
};
//_______________________
//_______________________
enum enMangeUsers{
	eListUsers=1,eAddNewUser=2,
	eDeleteUser=3,eUpdateUser=4,
	eFindUser=5,eMainMenue=6
};
enum enMainMenuePermissions
{
	eAll = -1, pListClint = 1, pAddNewClint = 2,
	pDeleteClient = 4, pUpdateClient = 8,
	pFindClint = 16, pTransactions = 32,
	pManageUsers = 64
};
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;

};

struct sUser
{
	string UserName;
	string PassWord;
	int  Permission;
	bool MarkForDelete = false;
};

sUser CurrentUser;
void Login();
void ShowMainMenue();
void ShowTransactionsMenue();
void ShowManageUsersMenue();
void GoBackToMainMenueScreen()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowMainMenue();
}
void GoBackToManageUserMenueScreen()
{
	cout << "\n\nPress any key to go back to Manage User Menue...";
	system("pause>0");
	ShowManageUsersMenue();
}
int ReadPermissionToSet()
{
	short Permission = 0;
	char Answer = 'n';

	cout << "\nDo you want to give full access?\n";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		return -1;
	}
	cout << "Do you want to give accsess to :\n";

	cout << "\nShow Client List? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pListClint;
	}
	cout << "\nAdd New Client? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pAddNewClint;
	}
	cout << "\nDelete Client? y/n? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pDeleteClient;
	}
	cout << "\nUpdate Client? y/n? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pUpdateClient;
	}
	cout << "\nFind Client? y/n? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pFindClint;
	}
	cout << "\nTransactions Client? y/n? ";
	cin >> Answer;

	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pTransactions;
	}
	cout << "\nManage Users? y/n? ";
	cin >> Answer;
	if (Answer == 'Y' || Answer == 'y')
	{
		Permission += enMainMenuePermissions::pManageUsers;
	}

	return Permission;

}
bool CheckAccessPermission(enMainMenuePermissions Permission)
{
	if (CurrentUser.Permission == enMainMenuePermissions::eAll)
		return true;
	if ((Permission & CurrentUser.Permission) == Permission)
		return true;
	else
		return false;
	
}
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
		if (S1 !="")
		{
			vString.push_back(S1);
		}
		return vString;
}
sClient ConvertLineToRecord(string Line, string Sperator = "#//#")
{
	sClient Client;
	vector<string>vClientData;
	vClientData = SplitString(Line, Sperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone =vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);
	return Client;
}
sUser ConvertUserLineToRecord(string Line, string Sperator = "#//#")
{
	sUser User;
	vector<string>vUserData;
	vUserData = SplitString(Line, Sperator);
	User.UserName = vUserData[0];
	User.PassWord = vUserData[1];
	User.Permission =stoi(vUserData[2]);

	return User;
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
vector<sUser>LoadUserDataFromFile(string FileName)
{
	vector<sUser>vUsers;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		sUser User;
		string Line;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			vUsers.push_back(User);
		}
		MyFile.close();
	}
	return vUsers;
}

void PrintCLientRecordLine(sClient Client)
{
	
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(30) << left << Client.Name;
	cout << "| " << setw(15) << left << Client.Phone;
	cout << "| " << setw(15) << left << Client.AccountBalance;
	
}		
void PrintUserRecordLine(sUser User)
{

	cout << "| " << setw(15) << left << User.UserName;
	cout << "| " << setw(10) << left << User.PassWord;
	cout << "| " << setw(30) << left << User.Permission;
	

}
void ShowAccessDeniedMessage()
{
	cout << "\n____________________________________________\n";
	cout << "Access Denied,\nYou dont Have Permisisson To Do this,\nPlease Conact Your Admin.";
	cout << "\n____________________________________________\n";

}
void PrintClientCard(sClient Client)
{
	
	{
		cout << "\n The following are the client details:\n";
		cout << "_____________________________________________";
		cout <<"\nAccount Number : " << Client.AccountNumber;
		cout <<"\nName           :" << Client.Name;
		cout <<"\nPhone          :" << Client.Phone;
		cout <<"\nPin Code       :" << Client.PinCode;
		cout <<"\nAccount Balance:" << Client.AccountBalance;
		cout << "\n_____________________________________________\n";
	
	}
}
void PrintUserCard(sUser User)
{

	{
		cout << "\n The following are the User details:\n";
		cout << "_____________________________________________";
		cout << "\nUsername    :" << User.UserName;
		cout << "\nPassword    :" << User.PassWord;
		cout << "\nPermission  :" << User.Permission;
		cout << "\n_____________________________________________\n";

	}
}
void PrintAllClientsData()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pListClint))
	{
		ShowAccessDeniedMessage();
		return;
	}

	vector<sClient>vClients =
		LoadClienstDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\t Client List (" << vClients.size() << ") Client(s) .";
	cout << "\n______________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(10) << left << "PinCode";
	cout << "| " << setw(30) << left << "Name";
	cout << "| " << setw(15) << left << "Phone";
	cout << "| " << setw(15) << left << "AccountBalance";
	cout << "\n______________________________________________________________________________________________" << endl;
	cout << "______________________________________________________________________________________________\n" << endl;


	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System !";
	else
	for (sClient &Client : vClients)
	{
		PrintCLientRecordLine(Client);
		cout << endl;
    }
	cout << "\n_____________________________________________________________________________________________\n" << endl;

}
void PrintAllUsersData()
{
	vector<sUser>vUsers =
		LoadUserDataFromFile(UsersFileName);
	cout << "\n\t\t\t\t\t User List (" << vUsers.size() << ") Users(s) .";
	cout << "\n______________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "UserName";
	cout << "| " << setw(10) << left << "Password";
	cout << "| " << setw(30) << left << "Permission";
	
	cout << "\n______________________________________________________________________________________________" << endl;
	cout << "______________________________________________________________________________________________\n" << endl;


	if (vUsers.size() == 0)
		cout << "\t\t\t\tNo Users Available In the System !";
	else
		for (sUser& User : vUsers)
		{
			PrintUserRecordLine(User);
			cout << endl;
		}
	cout << "\n_____________________________________________________________________________________________\n" << endl;

}
void ShowTotalBalances()
{
	vector<sClient>vClients =
		LoadClienstDataFromFile(ClientsFileName);
	cout << "\n\t\t\t\t\t Balances List (" << vClients.size() << ") Client(s) .";
	cout << "\n______________________________________________________________________________________________\n";
	cout << "| " << setw(15) << left << "AccountNumber";
	cout << "| " << setw(30) << left << "Client Name";
	cout << "| " << setw(15) << left << "Balance";
	cout << "\n______________________________________________________________________________________________\n";
	double TotalBalances = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System !";
	else
		for (sClient& Client : vClients)
		{
			PrintCLientRecordLine(Client);
			TotalBalances += Client.AccountBalance;

			cout << endl;
		}
	cout << "\n______________________________________________________________________________________________\n";
	cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 8]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;

}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	//vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			//vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
bool UserExistsByUsername(string Username, string FileName)
{
	//vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	if (MyFile.is_open())
	{
		string Line;
		sUser User;
		while (getline(MyFile, Line))
		{
			User = ConvertUserLineToRecord(Line);
			if (User.UserName == Username)
			{
				MyFile.close();
				return true;
			}
			//vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}
sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter your Account Number?.";
	getline(cin>>ws, Client.AccountNumber);
	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
	{
		cout << "\nClient with (" << Client.AccountNumber << ") alread exists,Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);

	}
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
sUser ReadNewUser()
{
	sUser User;
	cout << "Enter Username?.";
	getline(cin >> ws, User.UserName);
	while (UserExistsByUsername(User.UserName, UsersFileName))
	{
		cout << "\nUser with (" << User.UserName << ") alread exists,Enter another Username? ";
		getline(cin >> ws, User.UserName);

	}
	cout << "Enter Password?.";
	getline(cin >> ws, User.PassWord);

	User.Permission = ReadPermissionToSet();
	
	return User;

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
string ConvertUserRecordToLine(sUser User, string Delim = "#//#")
{
	string stUserRecord = "";
	stUserRecord += User.UserName + Delim;
	stUserRecord += User.PassWord + Delim;
	stUserRecord += to_string(User.Permission);

	return stUserRecord;
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
void AddNewClient()
{
	sClient Client;
	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConvertRecordToline(Client));
	
}
void AddNewUser()
{
	sUser User;
	User = ReadNewUser();
	AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));

}
void AddNewClients()
{
	char AddMore = 'Y';
	do 
	{
		//system("cls");
		cout << "\nAdding New Client \n";
		AddNewClient();

		cout << "Client Added Successfully, do you want to add more clients? Y/N ?\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void AddNewUsers()
{
	char AddMore = 'Y';
	do
	{
		//system("cls");
		cout << "\nAdding New Users \n";
		AddNewUser();

		cout << "User Added Successfully, do you want to add more Users? Y/N ?\n";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}

vector<sClient>SaveClientsDataToFile(string FileName, vector<sClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToline(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
vector<sUser>SaveUsersDataToFile(string FileName, vector<sUser>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);

	string DataLine;

	if (MyFile.is_open())
	{
		for (sUser& C : vUsers)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vUsers;
}

string ReadClientAccountNumber()
{
	string AccountNumber="";
	cout << "\nEnter Account Number ?\n";
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
bool MarkUserForDeleteByUsername(string Username, vector<sUser>& vUsers)
{
	for (sUser& C : vUsers)
	{
		if (C.UserName == Username)
		{

			C.MarkForDelete = true;

			return true;

		}

	}
	return false;

}
bool FindClientByAccountNumber(string AccountNumber,vector<sClient>&vClients,sClient& Client)
{
	
	
	for (sClient &C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;

}
bool FindUserByUsername(string Username, vector<sUser>& vUsers, sUser& User)
{


	for (sUser& C : vUsers)
	{
		if (C.UserName == Username)
		{
			User = C;
			return true;
		}
	}
	return false;

}
bool FindUserByUsernameAndPassword(string Username, string Password, sUser& User)
{

	vector<sUser>vUsers = LoadUserDataFromFile(UsersFileName);

	for (sUser& C : vUsers)
	{
		if (C.UserName == Username&&C.PassWord==Password)
		{
			User = C;
			return true;
		}
	}
	return false;

}
bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answar = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to delete this client ? Y/N ?";
		cin >> Answar;
		if (Answar == 'y' || Answar == 'Y')
		{
			MarkCLientForDeleteByAccountNumber(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);
			  
			vClients = LoadClienstDataFromFile(ClientsFileName);

			cout << "\n\n Client Deleted Successfully. ";
			return true;
		}
	}
	else
	{
		cout << "\n\n Client  with Account Number (" << AccountNumber << ") is Not Found " << endl;
			return false;
	}
	
}
bool DeleteUserByUserName(string Username, vector<sUser>& vUsers)
{
	if (Username == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;
	}
	sUser User;
	char Answar = 'n';

	if (FindUserByUsername(Username, vUsers, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want to delete this User ? Y/N ?";
		cin >> Answar;
		if (Answar == 'y' || Answar == 'Y')
		{
			MarkUserForDeleteByUsername(Username, vUsers);
			SaveUsersDataToFile(UsersFileName, vUsers);

			vUsers = LoadUserDataFromFile(UsersFileName);

			cout << "\n\n User Deleted Successfully. ";
			return true;
		}
	}
	else
	{
		cout << "\n\n User  with Username  (" << Username << ") is Not Found " << endl;
		return false;
	}

}
sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\n Enter your PIN Code?.\n";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter your Name?";
	getline(cin, Client.Name);
	cout << "Enter your Phone Number?";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance?";
	cin >> Client.AccountBalance;
	return Client;
}
sUser ChangeUserRecord(string Username)
{
	sUser User;
	User.UserName = Username;
	cout << "\n\n Enter Password?.\n";
	getline(cin >> ws, User.PassWord);
	User.Permission = ReadPermissionToSet();
	return User;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
{
	sClient Client;
	char Answar = 'n';
	if (FindClientByAccountNumber(AccountNumber, vClients,Client))
	{
		PrintClientCard(Client);
		cout << "\n\nAre you sure you want to update  this Client ? y/n ?";
		cin >> Answar;
		if (Answar == 'y' || Answar == 'Y')
		{

			for (sClient& C : vClients)
			{

				if (C.AccountNumber == AccountNumber)

				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}

			}
			SaveClientsDataToFile(ClientsFileName, vClients);
			cout << "\n\nClient Updated Successfully.";
				return true;

		}

	}

	else
	{
		cout << "\n\n Client with Account Number (" << AccountNumber << ") is Not Found . " << endl;

		return false;
	}

	
}
bool UpdateUserByUsername(string Username, vector<sUser>& vUsers)
{
	sUser User;
	char Answar = 'n';
	if (FindUserByUsername(Username, vUsers, User))
	{
		PrintUserCard(User);
		cout << "\n\nAre you sure you want to update  this User ? y/n ?";
		cin >> Answar;
		if (Answar == 'y' || Answar == 'Y')
		{

			for (sUser& C : vUsers)
			{

				if (C.UserName == Username)

				{
					C = ChangeUserRecord(Username);
					break;
				}

			}
			SaveUsersDataToFile(UsersFileName, vUsers);
			cout << "\n\nUser Updated Successfully.";
			return true;

		}

	}

	else
	{
		cout << "\n\n User with Username(" << Username << ") is Not Found . " << endl;

		return false;
	}


}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perform this transaction? y/n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
				return true;
			}
		}
		return false;
	}

}
void ShowAddNewClientsScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n______________________________________________________\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n______________________________________________________\n";
	AddNewClients();

}
void ShowDeleteClientScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n______________________________________________________\n";
	cout << "\tDelete Client Screen";
	cout << "\n______________________________________________________\n";

	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);

	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}
void ShowFindClientScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n______________________________________________________\n";
	cout << "\tFind Clients Screen";
	cout << "\n______________________________________________________\n";

	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);
	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
		PrintClientCard(Client);
	else
		cout << "\n Client with Account Number(" << AccountNumber << ") i not found !";

}
void ShowUpdateClientScreen()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		return;
	}
	cout << "\n______________________________________________________\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n______________________________________________________\n";

	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);
}
void ShowEndScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tProgram Ends :-) ";
	cout << "\n______________________________________________________\n";
}
void ShowDepositScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tDeposit Screen";
	cout << "\n______________________________________________________\n";

	sClient Client;
	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter deposit amount? ";
	cin >> Amount;
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}
void ShowWithDrawScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tWithDraw Screen";
	cout << "\n______________________________________________________\n";

	sClient Client;
	vector<sClient>vClients = LoadClienstDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();

	while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadClientAccountNumber();
	}
	PrintClientCard(Client);
	double Amount = 0;
	cout << "\nPlease enter withdraw amount? ";
	cin >> Amount;
	
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
		cout << "Please enter another amount? ";
		cin >> Amount;
	}
	DepositBalanceToClientByAccountNumber(AccountNumber, Amount*-1, vClients);

}
void ShowTotalBalancesScreen()
{
	ShowTotalBalances();
}
void GoBackToTransactionsMenue()
{
	cout << "\n\nPressany key to go back to Transactions Menue...";
	system("pause>0");
	ShowTransactionsMenue();
}

short ReadTransactionsMenueOption()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
	switch (TransactionMenueOption)
	{
	case enTransactionsMenueOptions::eDeposit:
	{
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionsMenueOptions::eWithdraw:
	{
		system("cls");
		ShowWithDrawScreen();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionsMenueOptions::eShowTotalBalance:
	{
		system("cls");
		ShowTotalBalancesScreen();
		GoBackToTransactionsMenue();
		break;
	}
	case enTransactionsMenueOptions::eShowMainMenue:
	{
		ShowMainMenue();
	}
	}
}
void ShowTransactionsMenue()
{
	if (!CheckAccessPermission(enMainMenuePermissions::pTransactions))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenueScreen();
		return;
	}
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tTransactions Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Main Menue.\n";
	cout << "===========================================\n";


	PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());

}

void PreformMainMenueOption(enMainMenueOptions MainMenueOption)
{
	switch (MainMenueOption)
	{
	case enMainMenueOptions::eListClient:
	{
		system("cls");
		PrintAllClientsData();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
	{
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenueOptions::eDeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenueOptions::eUpdateClient:
	{
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenueOptions::eFindClient:
	{
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenueScreen();
		break;
	}
	case enMainMenueOptions::eShowTransactionsMenue:
	{
		system("cls");
		ShowTransactionsMenue();
		break;
	}
	case enMainMenueOptions::eManageUsers:
	{
		system("cls");
		ShowManageUsersMenue();
		
		break;
	}
	case enMainMenueOptions::eLogOut:
	{
		system("cls");
		//ShowEndScreen()
		Login();

		break;
	}

    }
}



////Extension_2______________________________________
string ReadUserName()
{
	string UserName = "";
	cout << "\nPlease Enter UserName? ";
	getline(cin >>ws, UserName);
	return UserName;
}
void ShowListUsersScreen()
{
	PrintAllUsersData();
}
void ShowAddNewUsersScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tAdd New User Screen";
	cout << "\n______________________________________________________\n";
	AddNewUsers();
}
void ShowDeleteUsersScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tDelete User Screen";
	cout << "\n______________________________________________________\n";
	vector<sUser>vUsers = LoadUserDataFromFile(UsersFileName);

	string Username = ReadUserName();
	DeleteUserByUserName(Username, vUsers);
	
}
void ShowUpdateUsersScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tUpdate User Screen";
	cout << "\n______________________________________________________\n";
	vector<sUser>vUsers = LoadUserDataFromFile(UsersFileName);

	string Username = ReadUserName();
	UpdateUserByUsername(Username, vUsers);
}
void ShowFindUsersScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tFind User Screen";
	cout << "\n______________________________________________________\n";

	vector<sUser>vUsers = LoadUserDataFromFile(UsersFileName);
	sUser User;
	string Username = ReadUserName();
	if (FindUserByUsername(Username, vUsers, User))
		PrintUserCard(User);
	else
		cout << "\n User with Username(" << Username << ") i not found !";

}
short ReadManageUsersMenueOption()
{
	cout << "Choose what do you want to do? [1 to 6]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
bool LoadUserInfo(string Username, string Password)
{
	if (FindUserByUsernameAndPassword(Username, Password, CurrentUser))
		return true;
	else
		return false;
}

void Login()
{
	bool LoginFaild = false;
	string Username, Password;
	do
	{
		system("cls");

		cout << "\n__________________________________\n";
		cout << "\tLogin Screen";
		cout << "\n__________________________________\n";

		if (LoginFaild)
		{
			cout << "Invalid Username/Password!\n";
		}
		cout << "Enter Username? ";
		cin >> Username;

		cout << "Enter Password? ";
		cin >> Password;

		LoginFaild = !LoadUserInfo(Username, Password);

	} while (LoginFaild);
	ShowMainMenue();
}
void PreformManageUsersMenueOption(enMangeUsers MangeUsers)
{
	switch (MangeUsers)
	{
	case enMangeUsers::eListUsers:
	{
		system("cls");
		ShowListUsersScreen();
		GoBackToManageUserMenueScreen();
		break;

	}
	case enMangeUsers::eAddNewUser:
	{
		system("cls");
		ShowAddNewUsersScreen();
		GoBackToManageUserMenueScreen();
		break;
	}
	case enMangeUsers::eDeleteUser:
	{
		system("cls");
		ShowDeleteUsersScreen();
		GoBackToManageUserMenueScreen();
		break;
		
	}
	case enMangeUsers::eUpdateUser:
	{
		system("cls");
		ShowUpdateUsersScreen();
		GoBackToManageUserMenueScreen();
		break;
	}
	case enMangeUsers::eFindUser:
	{
		system("cls");
		ShowFindUsersScreen();
		GoBackToManageUserMenueScreen();
		break;

	}
	case enMangeUsers::eMainMenue:
	{

		ShowMainMenue();
		

	}

	}

}
void ShowManageUsersMenue()
{

	if (!CheckAccessPermission(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenueScreen();
		return;
	}
	system("cls");
	cout << "===========================================\n";
	cout << "\t\tManage Users Menue Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] List Users.\n";
	cout << "\t[2] Add New Users.\n";
	cout << "\t[3] Delete Users.\n";
	cout << "\t[4] Update Users.\n";
	cout << "\t[5] Find Users.\n";
	cout << "\t[6] Main Menue.\n";
	cout << "===========================================\n";


	PreformManageUsersMenueOption((enMangeUsers)ReadManageUsersMenueOption());

}
void ShowLoginScreen()
{
	cout << "\n______________________________________________________\n";
	cout << "\tLogin Screen";
	cout << "\n______________________________________________________\n";


}





void ShowMainMenue()
{

	system("cls");

	cout << "===========================================================\n";
	cout << "\t\t Main Menue Screen \t\t\t\n";
	cout << "===========================================================\n";
	cout << "\t[1] Show Client List. \n";
	cout << "\t[2] Add New Client. \n";
	cout << "\t[3] Delete Client. \n";
	cout << "\t[4] Update Client Info. \n";
	cout << "\t[5] Find Client. \n";
	cout << "\t[6] Transactions. \n";
	cout << "\t[7] Manage Users. \n";
	cout << "\t[8] Logout. \n";
	cout << "===========================================================\n";

	PreformMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
int main()
{

	Login();
    system("pause>0");
	return 0;

}






