#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <ctime>
#include <locale>
#include <codecvt>
#pragma warning(disable : 4996)

using namespace std;
fstream Myfile;
const string clientsfile = "clients.txt";
const string usersfile = "users.txt";
const string logedinuser = "logedin.txt";


struct stUser {
	string usename;
	string password;
	int Permissions = 0;
	bool markfordelet = false;
};
struct stclienthistory
{
	string date;
	string object;
	string from;
	string to;
	string amount;
};
struct stclientrequest
{
	stclienthistory request;
	bool markforacceptordecline = false;
};
struct client
{
	string Fullname;
	string phoneNumer;
	string accountNumber;
	float accountBalance;
	string pingcode;
	bool marktodelet = false;
	vector <stclienthistory> history;
	vector <stclientrequest> request;

};
void menu(vector <client> temp);
string convertclientrecordtoline(client temp, string dele);
void addrecordtofile(string line , string file);
vector <client> getrecordfromfile();
vector <stUser>  getuserrecordfromfile();
vector <client> clients = getrecordfromfile();
vector <stUser> users = getuserrecordfromfile();
void transactionsmenu();
void login();
vector <string> spliteline(string line, string dele);
void manageUsers();
bool has_access(int permissions, int section);
bool isFileEmpty(string filename);
void donthaveaccses(string section);
void login();


// history
stclienthistory coverthistorylinetorecod(vector <string> temp) {
	stclienthistory tempstruct;

	tempstruct.amount = temp[0];
	tempstruct.date = temp[1];
	tempstruct.from = temp[2];
	tempstruct.to = temp[3];
	tempstruct.object = temp[4];
	return tempstruct;
}
vector <stclienthistory> gethistoryfromfile(string Fullname) {
	vector <stclienthistory> clientshistory;
	const string clienthistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + Fullname + "\\history.txt"; // change this to the path of the clients transaction in this this project ;
	Myfile.open(clienthistory, ios::in);

	if (Myfile.is_open())
	{
		stclienthistory temp;
		string line;
		while (getline(Myfile, line))
		{
			temp = coverthistorylinetorecod(spliteline(line, "#//#"));
			clientshistory.push_back(temp);
		}


		Myfile.close();
	}
	return clientshistory;
}



// to open foldrs
wstring stringToWString(const string& str) {
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);

}





bool isFileEmpty(string filename) {
	ifstream file(filename);
	return file.peek() == ifstream::traits_type::eof();
};
void addclient() {
	client temp;
	system("cls");
	cout << "enter the client account Number : \n";
	getline(cin >> ws, temp.accountNumber);

	for (client& c : clients)
	{
		if (temp.accountNumber == c.accountNumber)
		{


			cout << "this account number is alredy taken enter an other one : \n";
			getline(cin >> ws, temp.accountNumber);



		}
	}

	cout << "enter the client FullName : \n";
	getline(cin >> ws, temp.Fullname);
	cout << "enter the client phoneNumber  : \n";
	cin >> temp.phoneNumer;

	cout << "enter the client balance : \n";
	cin >> temp.accountBalance;
	cout << "enter the client pincode : \n";
	cin >> temp.pingcode;
	string line = convertclientrecordtoline(temp, "#//#");
	
	addrecordtofile(line , clientsfile);
	char isaddmore;
	cout << "\ndo you want to add one more client  Y/N: \n";
	cin >> isaddmore;

	if (toupper(isaddmore) == 'Y') {
		addclient();
	}
	else {
		clients = getrecordfromfile();
		menu(clients);
	}
}
string convertuserrecordtoline(stUser temp, string dele) {
	string line;
	line += temp.usename +dele;
	line += temp.password + dele;
	line += to_string(temp.Permissions);
	return line;

}
void adduser() {
	stUser temp;
	system("cls");
	cout << "enter the user's username : \n";
	getline(cin >> ws, temp.usename);

	for (stUser& c : users)
	{
		if (temp.usename == c.usename)
		{


			cout << "this account number is alredy taken enter an other one : \n";
			getline(cin >> ws, temp.usename);



		}
	}
	string sections[7] = {
		"View clients list",
		"Add client",
		"Client info",
		"Delete client",
		"Update client info",
		"Transactions",
		"Manage users"
	};
	

	cout << "enter the user's password : \n";
	getline(cin >> ws, temp.password);
	char isfullaccess;
	cout << "do you want the user to have full access  Y/N: \n";
	cin >> isfullaccess;

	if (toupper(isfullaccess) == 'Y') {
		temp.Permissions = -1;
	}
	else {
		char answer;
		for (int i = 0; i < 7; i++) {
			cout << "give User access to " << sections[i] << " : ";
			cin >> answer;
			if (toupper(answer) == 'Y') {
				temp.Permissions |= (1 << i);
			}
		}
	}
	
	string line = convertuserrecordtoline(temp, "#//#");

	addrecordtofile(line, usersfile);
	char isaddmore;
	cout << "\ndo you want to add one more user  Y/N: \n";
	cin >> isaddmore;

	if (toupper(isaddmore) == 'Y') {
		addclient();
	}
	else {
		
		manageUsers();
	}
}
string convertclientrecordtoline(client temp, string dele)
{
	string line;

	line += temp.accountNumber + dele;
	line += temp.Fullname + dele;
	line += temp.phoneNumer + dele;
	line += temp.pingcode + dele;
	line += to_string(temp.accountBalance);

	return line;
}

void addrecordtofile(string line, string filename) {
	Myfile.open(filename, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << line << endl;
		Myfile.close();
	}
}

vector <string> spliteline(string line, string dele) {

	vector <string> temp;

	string sword;
	int pos = 0;

	while ((pos = line.find(dele)) != std::string::npos)
	{
		sword = line.substr(0, pos);
		temp.push_back(sword);

		line = line.erase(0, pos + dele.length());
	}
	if (line != "")
		temp.push_back(line);

	return temp;
}

client convertlinetorecor(vector <string> temp) {
	client tempstruct;

	tempstruct.accountNumber = temp[0];
	tempstruct.Fullname = temp[1];
	tempstruct.phoneNumer = temp[2];
	tempstruct.pingcode = temp[3];
	tempstruct.accountBalance = stof(temp[4]);



	return tempstruct;
}

stUser convertuserlinetorecor(vector <string> temp) {
	stUser tempstruct;

	tempstruct.usename = temp[0];
	tempstruct.password = temp[1];
	tempstruct.Permissions = stoi(temp[2]);
	



	return tempstruct;
}

vector <client> getrecordfromfile() {
	vector <client> clients;
	Myfile.open("clients.txt", ios::in);

	if (Myfile.is_open())
	{
		client temp;
		string line;
		while (getline(Myfile, line))
		{
			temp = convertlinetorecor(spliteline(line, "#//#"));
			clients.push_back(temp);
		}


		Myfile.close();
	}


	return clients;
}
vector <stUser> getuserrecordfromfile() {
	vector <stUser> users;
	Myfile.open(usersfile, ios::in);

	if (Myfile.is_open())
	{
		stUser temp;
		string line;
		while (getline(Myfile, line))
		{
			temp = convertuserlinetorecor(spliteline(line, "#//#"));
			users.push_back(temp);
		}


		Myfile.close();
	}


	return users;
}
stUser getlogedinuserrecordfromfile(string logedinuser) {
	std::ifstream Myfile(logedinuser, std::ios::in);

	if (Myfile.is_open()) {
		stUser temp;
		std::string line;

		while (std::getline(Myfile, line)) {
			temp = convertuserlinetorecor(spliteline(line, "#//#"));
			Myfile.close();
			return temp;
		}

		Myfile.close();
	}
	else {
		std::cerr << "Failed to open the file: " << logedinuser << std::endl;
	}

	// Return a default-constructed stUser if the file is not opened or no valid record is found
	return stUser();
}
void printclientinto(client temp) {

	cout << left << setw(27) << "|  " + temp.accountNumber;
	cout << left << setw(27) << "|  " + temp.Fullname;
	cout << left << setw(27) << "|  " + temp.phoneNumer;
	cout << left << setw(13) << "|  " + temp.pingcode;
	cout << left << setw(33) << "|  " + to_string(temp.accountBalance) << "|" << endl;
}

void clientlistmenu(vector <client> temp) {
	system("cls");
	cout << left << setw(27) << "|  account number   ";
	cout << left << setw(27) << "|  fullname   ";
	cout << left << setw(27) << "|  phone number   ";
	cout << left << setw(13) << "|  pincode   ";
	cout << left << setw(33) << "|  account balance               |" << endl;
	cout << "|------------------------------------------------------------------------------------------------------------------------------|\n";
	for (client& thisclinet : temp)
	{
		printclientinto(thisclinet);
		cout << "|------------------------------------------------------------------------------------------------------------------------------|\n";
	}

	system("pause");
	menu(clients);
}
void printuserinto(stUser temp) {

	cout << left << setw(27) << "|  " + temp.usename;
	cout << left << setw(27) << "|  " + temp.password;

	cout << left << setw(22) << "|  " + to_string(temp.Permissions) << "|" << endl;
}
void userslistmenu() {
	users = getuserrecordfromfile();
	system("cls");
	cout << left << setw(27) << "|  user's username   ";
	cout << left << setw(27) << "|  password   ";
	cout << left << setw(27) << "|  user's Permissions |"<< endl;
	cout << "|---------------------------------------------------------------------------|\n";
	for (stUser& thisclinet : users)
	{
		printuserinto(thisclinet);
		cout << "|---------------------------------------------------------------------------|\n";
	}

	system("pause");
	manageUsers();
}

void clientInfo() {
	clients = getrecordfromfile();
	string clientAccountNumber;
	cout << "\t\t\t\t\t\t enter the client account number you want to shearch for\n";
	cout << "\t\t\t\t\t\t";
	cin >> clientAccountNumber;
	int counter = 0;
	for (client& temp : clients) {
		if (temp.accountNumber == clientAccountNumber)
		{
			counter++;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   account number  : " << left << setw(23) << temp.accountNumber << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   fullName        : " << left << setw(23) << temp.Fullname << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   phone number    : " << left << setw(23) << temp.phoneNumer << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   pine code       : " << left << setw(23) << temp.pingcode << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   account balance : " << left << setw(23) << temp.accountBalance << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;

		}



	}

	if (counter == 0)
		cout << "\t\t\t\t\t\tclient with account number " << clientAccountNumber << " Not found!\n";
	char result;
	cout << "\n\n\t\t\t\t\t\t do you want to search for an other client info Y/N : \n";
	cout << "\t\t\t\t\t\t";
	cin >> result;
	if (toupper(result) == 'Y') {
		system("cls");
		clientInfo();
	}
	else {
		system("pause");
		menu(clients);
	}
}

void userInfo() {
	clients = getrecordfromfile();
	string username;
	cout << "\t\t\t\t\t\t enter the user's username want to shearch for\n";
	cout << "\t\t\t\t\t\t";
	cin >> username;
	int counter = 0;
	for (stUser& temp : users) {
		if (temp.usename == username)
		{
			counter++;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      usename      : " << left << setw(23) << temp.usename << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      password     : " << left << setw(23) << temp.password << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  user Permissions : " << left << setw(23) << temp.Permissions << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;


		}



	}

	if (counter == 0)
		cout << "\t\t\t\t\t\tuser with username : " << username << " Not found!\n";
	char result;
	cout << "\n\n\t\t\t\t\t\t do you want to search for an other user info Y/N : \n";
	cout << "\t\t\t\t\t\t";
	cin >> result;
	if (toupper(result) == 'Y') {
		system("cls");
		userInfo();
	}
	else {
		system("pause");
		manageUsers();
	}
}
void reuplodefile(string filename) {
	if (filename == clientsfile) {
		Myfile.open(filename, ios::out);
		for (client& c : clients) {
			if (c.marktodelet == false) {

				string line = convertclientrecordtoline(c, "#//#");



				if (Myfile.is_open())
				{
					Myfile << line << endl;

				}
			}
		}

		Myfile.close();
	}
	else if (filename == usersfile) {
		Myfile.open(filename, ios::out);
		for (stUser& u : users) {
			if (u.markfordelet == false) {

				string line = convertuserrecordtoline(u, "#//#");



				if (Myfile.is_open())
				{
					Myfile << line << endl;

				}
			}
		}

		Myfile.close();
	}
}

void updateclientinfo() {

	string clientAccountNumber;
	cout << "\t\t\t\t\t\t enter the client account number you want to update\n";
	cout << "\t\t\t\t\t\t";
	cin >> clientAccountNumber;
	int counter = 0;

	for (client& temp : clients) {
		if (temp.accountNumber == clientAccountNumber)
		{


			counter++;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[]account number     : " << left << setw(23) << temp.accountNumber << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[1]fullName           : " << left << setw(23) << temp.Fullname << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[2]phone number       : " << left << setw(23) << temp.phoneNumer << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[3]pine code          : " << left << setw(23) << temp.pingcode << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[4]account balance    : " << left << setw(23) << temp.accountBalance << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;

			int areyousure;
			cout << "\t\t\t\t\t\t enter the number you want to update \n";
			cout << "\t\t\t\t\t\t";
			cin >> areyousure;
			switch (areyousure)
			{
			case 1:
				cout << "\t\t\t\t\t\t enter the new fullName \n";
				cout << "\t\t\t\t\t\t";
				getline(cin >> ws, temp.Fullname);
				break;
			case 2:
				cout << "\t\t\t\t\t\t enter the new phone number \n";
				cout << "\t\t\t\t\t\t";
				cin >> temp.phoneNumer;
				break;
			case 3:
				cout << "\t\t\t\t\t\t enter the new pine code \n";
				cout << "\t\t\t\t\t\t";
				cin >> temp.pingcode;
				break;
			case 4:
				cout << "\t\t\t\t\t\t enter the new account balance \n";
				cout << "\t\t\t\t\t\t";
				cin >> temp.accountBalance;
				break;
			default:
				break;
			}


			break;
		}



	}
	if (counter == 0)
		cout << "\t\t\t\t\t\tclient with account number (" << clientAccountNumber << ") Not found!\n";
	reuplodefile(clientsfile);
	clients = getrecordfromfile();

	system("pause");
	menu(clients);

}

void updateuserinfo() {

	string username;
	cout << "\t\t\t\t\t\t enter the user's username you want to update\n";
	cout << "\t\t\t\t\t\t";
	cin >> username;
	int counter = 0;
	string sections[7] =
	                     {
                           "View clients list",
                           "Add client",
                           "Client info",
                           "Delete client",
                           "Update client info",
                           "Transactions",
                           "Manage users"
	                     };


	 for (stUser& temp : users) {
		if (temp.usename == username)
		{


			counter++;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[]username            : " << left << setw(23) << temp.usename << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[1]password           : " << left << setw(23) << temp.password << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[2]user's Permissions : " << left << setw(23) << temp.Permissions << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			

			int areyousure;
			cout << "\t\t\t\t\t\t enter the number you want to update \n";
			cout << "\t\t\t\t\t\t";
			cin >> areyousure;
			switch (areyousure)
			{
			case 1:
				cout << "\t\t\t\t\t\t enter the new password \n";
				cout << "\t\t\t\t\t\t";
				getline(cin >> ws, temp.password);
				break;
			case 2:

				cout << "\t\t\t\t\t\t fill the new Permissions\n";
				
				temp.Permissions = 0;
				char answer;
				int counter = 0;
				for (int i = 0; i < 7; i++) {
					counter++;
					cout << "\t\t\t\t\t\t";
					cout << "give User access to " << sections[i] << " Y/N : ";
					cin >> answer;
					if (toupper(answer) == 'Y') {
						temp.Permissions |= (1 << i);
					}
					if (counter == 7) {
						temp.Permissions = -1;
					}
				}
				break;
		
			
			}


			break;
		}



	}
	if (counter == 0)
		cout << "\t\t\t\t\t\tclient with account number (" << username << ") Not found!\n";
	reuplodefile(clientsfile);
	clients = getrecordfromfile();

	system("pause");
	menu(clients);

}
string getdate() {

	time_t now = time(0);


	char* dt = ctime(&now);




	tm* gmtm = gmtime(&now);
	dt = asctime(gmtm);
	string str = dt;
	if (!str.empty() && str.back() == '\n') {
		str.pop_back();
	}
	return str;
}
string converthistorytoline(stclienthistory temp, string dele) {
	string line;
	line += temp.amount + dele;
	line += temp.date + dele;
	line += temp.from + dele;
	line += temp.to + dele;
	line += temp.object;

	return line;
}
void Deposite() {

	cout << "\t\t\t\t\t\t" << left << setw(27) << "|  account number   ";
	cout << left << setw(27) << "|  fullname   ";
	cout << "|" << endl;
	cout << "\t\t\t\t\t\t" << "|-----------------------------------------------------|\n";


	for (client& temp : clients) {
		cout << "\t\t\t\t\t\t" << left << setw(27) << "|  " + temp.accountNumber;
		cout << left << setw(27) << "|  " + temp.Fullname;
		cout << "|" << endl;
		cout << "\t\t\t\t\t\t" << "|-----------------------------------------------------|\n";
	}





	string clientAccountNumber;
	cout << "\t\t\t\t\t\t enter the client account number \n";
	cout << "\t\t\t\t\t\t";
	cin >> clientAccountNumber;
	system("cls");
	int counter = 0;
	for (client& temp : clients) {
		if (temp.accountNumber == clientAccountNumber)
		{
			const string clientfolder = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname; // change this to client transactions path
			cout << "\t\t\t\t\t\t the following client details : \n";

			counter++;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  account number      : " << left << setw(23) << temp.accountNumber << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  fullName            : " << left << setw(23) << temp.Fullname << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  phone number        : " << left << setw(23) << temp.phoneNumer << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  pine code           : " << left << setw(23) << temp.pingcode << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  account balance     : " << left << setw(23) << temp.accountBalance << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;


			float depositamaount;
			cout << "\t\t\t\t\t\t enter the deposite amount : \n";
			cout << "\t\t\t\t\t\t ";
			cin >> depositamaount;

			char answer;
			cout << "\n\t\t\t\t\t\t are you sure you want to deposite Y/N: ";
			cin >> answer;

			if (toupper(answer) == 'Y') {
				wstring wclientfolder = stringToWString(clientfolder);

				if (CreateDirectory(wclientfolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
					//
				}
				stclienthistory history;
				history.from = "        -";
				history.to = "Me";
				history.amount = "+ " + to_string(depositamaount);
				history.date = getdate();
				history.object = "deposite in the banck";
				temp.accountBalance += depositamaount;
				const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname + "\\history.txt";// change this the clients transactions path
				string receiverrecord = converthistorytoline(history, "#//#");
				addrecordtofile(receiverrecord, clientshistory);
				reuplodefile(clientsfile);
				clients = getrecordfromfile();
				cout << "\n\t\t\t\t\t\t the amount has been sent successfully .";

				system("pause");
				transactionsmenu();

			}
			else
			{
				transactionsmenu();

			}

			break;
		}



	}



}

void withraw() {
	string clientAccountNumber;
	cout << "\t\t\t\t\t\t enter the client account number \n";
	cout << "\t\t\t\t\t\t";
	cin >> clientAccountNumber;
	int counter = 0;
	for (client& temp : clients) {
		if (temp.accountNumber == clientAccountNumber)
		{
			cout << "\t\t\t\t\t\t the following client details : \n";

			counter++;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[]account number      : " << left << setw(23) << temp.accountNumber << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[1]fullName           : " << left << setw(23) << temp.Fullname << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[2]phone number       : " << left << setw(23) << temp.phoneNumer << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[3]pine code          : " << left << setw(23) << temp.pingcode << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|[4]account balance    : " << left << setw(23) << temp.accountBalance << "    |" << endl;
			cout << "\t\t\t\t\t\t|---------------------------------------------------|" << endl;


			float withrawamaount;
			cout << "\t\t\t\t\t\t enter the withraw amount : \n";
			cout << "\t\t\t\t\t\t ";
			cin >> withrawamaount;


			while (withrawamaount > temp.accountBalance) {
				cout << "\n\t\t\t\t\t\t amount is bigger then the balance you can withdraw up to " << temp.accountBalance << endl;
				cout << "\t\t\t\t\t\t ";
				cin >> withrawamaount;
			};


			char answer;
			cout << "\n\t\t\t\t\t\t are you sure you want to withraw Y/N: ";
			cin >> answer;

			if (toupper(answer) == 'Y') {
				stclienthistory history;
				history.from = "        -";
				history.to = "Me";
				history.amount = "- " + to_string(withrawamaount);
				history.date = getdate();
				history.object = "withraw in the banck";
				
				const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname + "\\history.txt"; // chagne this to clients transactions path
				string receiverrecord = converthistorytoline(history, "#//#");
				addrecordtofile(receiverrecord, clientshistory);
				temp.accountBalance -= withrawamaount;
				cout << "\n\t\t\t\t\t\t done successfully the new amount is " << temp.accountBalance << endl;
				reuplodefile(clientsfile);
				clients = getrecordfromfile();


				system("pause");
				transactionsmenu();

			}
			else
			{
				transactionsmenu();

			}

			break;
		}



	}



}

void TotaleBalance() {
	int totalbalance = 0;

	system("cls");
	cout << left << setw(27) << "|  account number   ";
	cout << left << setw(27) << "|  fullname   ";
	cout << left << setw(27) << "|  phone number   ";
	cout << left << setw(13) << "|  pincode   ";
	cout << left << setw(33) << "|  account balance               |" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
	for (client& thisclinet : clients)
	{
		totalbalance += thisclinet.accountBalance;
		printclientinto(thisclinet);
		cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
	}
	cout << "\t\t\t\t\t\t|-----------------------------------------|\n";
	cout << "\t\t\t\t\t\t| Totale balance is :   " << left << setw(18) << totalbalance << "|\n";
	cout << "\t\t\t\t\t\t|-----------------------------------------|\n";

	system("pause");
	transactionsmenu();


}


void transactionsmenu() {
	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Deposite       [1]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  Withdraw      [2]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|             Totale balance     [3]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 main menu      [4]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;


	cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 4] : ";
	cin >> list;

	switch (list)
	{
	case 1:
		system("cls");
		Deposite();
		break;
	case 2:
		system("cls");
		withraw();
		break;
	case 3:
		system("cls");
		TotaleBalance();
		break;
	case 4:
		system("cls");
		menu(clients);
		break;
	default:
		break;
	}
}



void deleteclient() {
	string clientAccountNumber;
	cout << "\t\t\t\t\t\t enter the client account number you want to delete\n";
	cout << "\t\t\t\t\t\t";
	cin >> clientAccountNumber;
	int counter = 0;

	for (client& temp : clients) {
		if (temp.accountNumber == clientAccountNumber)
		{

			temp.marktodelet = true;
			counter++;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   account number  : " << left << setw(23) << temp.accountNumber << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   fullName        : " << left << setw(23) << temp.Fullname << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   phone number    : " << left << setw(23) << temp.phoneNumer << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   pine code       : " << left << setw(23) << temp.pingcode << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   account balance : " << left << setw(23) << temp.accountBalance << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			break;
		}



	}
	if (counter == 0)
		cout << "\t\t\t\t\t\tclient with account number (" << clientAccountNumber << ") Not found!\n";

	if (counter != 0)
	{
		char areyousure;
		cout << "\t\t\t\t\t\t are you sure you want to delete this client \n";
		cout << "\t\t\t\t\t\t";
		cin >> areyousure;
		if (toupper(areyousure) == 'Y')
		{

			reuplodefile(clientsfile);
			clients = getrecordfromfile();




		}
		else {
			menu(clients);

		}


	}




	char result;
	cout << "\n\n\t\t\t\t\t\t do you want to delet an other client Y/N : \n";
	cout << "\t\t\t\t\t\t";
	cin >> result;
	if (toupper(result) == 'Y') {
		system("cls");
		deleteclient();
	}
	else {
		system("pause");
		menu(clients);
	}

}


void deleteuser() {
	string username;
	cout << "\t\t\t\t\t\t enter the client account number you want to delete\n";
	cout << "\t\t\t\t\t\t";
	cin >> username;
	int counter = 0;

	for (stUser& temp : users) {
		if (temp.usename == username)
		{

			temp.markfordelet = true;
			counter++;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   account number  : " << left << setw(23) << temp.usename << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   fullName        : " << left << setw(23) << temp.password << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|   phone number    : " << left << setw(23) << temp.Permissions << "    |" << endl;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;

			break;
		}



	}
	if (counter == 0)
		cout << "\t\t\t\t\t\tuser with username (" << username << ") Not found!\n";

	if (counter != 0)
	{
		char areyousure;
		cout << "\t\t\t\t\t\t are you sure you want to delete this client \n";
		cout << "\t\t\t\t\t\t";
		cin >> areyousure;
		if (toupper(areyousure) == 'Y')
		{

			reuplodefile(usersfile);
			users = getuserrecordfromfile();




		}
		else {
			for (stUser& temp : users) {
				if (temp.usename == username)
				{
					temp.markfordelet = false;
					break;
				}
			}
			manageUsers();

		}


	}




	char result;
	cout << "\n\n\t\t\t\t\t\t do you want to delet an other client Y/N : \n";
	cout << "\t\t\t\t\t\t";
	cin >> result;
	if (toupper(result) == 'Y') {
		system("cls");
		deleteclient();
	}
	else {
		system("pause");
		menu(clients);
	}

}
void logout() {
	ofstream file(logedinuser, std::ios::trunc);
	login();
}
void menu(vector <client> temp)
{
	const wchar_t* folderName = L"clients Transactions";
	if (CreateDirectory(folderName, NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		//
	}

	string sections[7] = {
		"View clients list",
		"Add client",
		"Client info",
		"Delete client",
		"Update client info",
		"Transactions",
		"Manage users"
	};
	stUser logedInUser = getlogedinuserrecordfromfile(logedinuser);
	clients = getrecordfromfile();
	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|            View clients list   [1]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                Add client      [2]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                Client info     [3]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                Delete client   [4]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|            Update client info  [5]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                Transactions    [6]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Manage users   [7]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                    Log out     [8]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;

	cout << "\n\n\n\t\t\t\t\t\t enter a number in the list \n";
	cout << "\t\t\t\t\t\t";
	cin >> list;

	switch (list)
	{
	case 1:
		system("cls");
		if(has_access(logedInUser.Permissions , list)){
			clientlistmenu(temp);
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 2:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			addclient();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 3:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			clientInfo();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 4:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			deleteclient();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 5:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			updateclientinfo();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 6:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			transactionsmenu();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
		break;
	case 7:
		system("cls");
		system("cls");
		if (has_access(logedInUser.Permissions, list)) {
			manageUsers();
		}
		else
		{
			donthaveaccses(sections[list - 1]);
		}
	
		break;
	case 8:
		system("cls");
		logout();
		
		
		break;
	default:
		break;
	}


}
bool has_access(int permissions, int section) {
	return permissions & (1 << (section - 1)) || permissions == -1;
}

void donthaveaccses(string section) {
	cout << "\t\t\t\t\t\t|------------------------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                                                                  |" << endl;
	cout << "\t\t\t\t\t\t|  "<< left << setw(64)<<"You Dont have Accsess to "+section+" contact your admin" ;
	cout << "|" << endl;
	cout << "\t\t\t\t\t\t|                                                                  |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------------------------|" << endl;
	system("pause");
	system("cls");
	menu(clients);
}

void manageUsers() {
	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|              View Users list   [1]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                Add New User    [2]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  User info     [3]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Delete User    [4]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Update User    [5]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  Main Menu     [6]             |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\n\n\n\t\t\t\t\t\t enter a number in the list \n";
	cout << "\t\t\t\t\t\t";
	cin >> list;

	switch (list)
	{
	case 1:
		system("cls");
		userslistmenu();
		break;
	case 2:
		system("cls");
		adduser();
		break;
	case 3:
		system("cls");
		userInfo();
		break;
	case 4:
		system("cls");
		deleteuser();
		break;
	case 5:
		system("cls");
		updateuserinfo();
		break;
	case 6:
		system("cls");
		menu(clients);
		break;

	default:
		break;
	}
}


void login() {
	users = getuserrecordfromfile();
	int found = 0;
	string username, password;

	
	if(isFileEmpty(logedinuser))
	{
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      usename      : ";

		cin >> username;
		system("cls");
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      usename      : " << left << setw(23) << username << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      password     : ";
		cin >> password;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		for (stUser& user : users) {
			if (user.usename == username && user.password == password) {
				found++;
				string line = convertuserrecordtoline(user, "#//#");

				addrecordtofile(line, logedinuser);
				break;
			}
		}
		while (found <= 0) {
			system("cls");
			cout << "\t\t\t\t\tLogin Failed: Incorrect Username or Password. Please try again.       \n";
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      usename      : ";

			cin >> username;
			system("cls");
			cout << "\t\t\t\t\tLogin Failed: Incorrect Username or Password. Please try again.       \n";
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      usename      : " << left << setw(23) << username << "    |" << endl;;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      password     : ";
			cin >> password;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			for (stUser& user : users) {
				if (user.usename == username && user.password == password) {
					found++;
					string line = convertuserrecordtoline(user, "#//#");

					addrecordtofile(line, logedinuser);
					break;
				}
			}
		};
		system("cls");
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      usename      : " << left << setw(23) << username << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      password     : " << left << setw(23) << password << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		Sleep(500);
		menu(clients);
	}
	menu(clients);


}

int main()
{
	// if your first time login :
	//  username : admin  
	// password  : admin 

	login();



	return 0;
}