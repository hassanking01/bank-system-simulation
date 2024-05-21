#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <locale>
#include <codecvt>
#include <ctime>
#pragma warning(disable : 4996)
using namespace std;
fstream Myfile;
const string clientsfile = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients.txt";// change this to client.txt file in the admin folder (projectAlgo4)


// structer

struct stclienthistory
{
	string date;
	string to;
	string object;
	string from;
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
	vector <stclienthistory> history;
	vector <stclientrequest> request;

};

 client logedinclient;
vector <client> getrecordfromfile();
vector <client> clients = getrecordfromfile();
client convertlinetorecor(vector <string> temp);
string convertclientrecordtoline(client temp, string dele);
vector <string> spliteline(string line, string dele);
void reuplodefile(string filename);
void Deposite();
void withraw();
void quickwithraw();
void menu();
void sendmony();
void login();




// for history
void addrecordtofile(string line, string filename) {
	Myfile.open(filename, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << line << endl;
		Myfile.close();
	}
}


// you balance
void yourbalance() {
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                                                |" << endl;
	cout << "\t\t\t\t\t\t|                                                |" << endl;
	cout << "\t\t\t\t\t\t|   Your Balance Is : " << left << setw(23) << logedinclient.accountBalance << "    |" << endl;
	cout << "\t\t\t\t\t\t|                                                |" << endl;
	cout << "\t\t\t\t\t\t|                                                |" << endl;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\n\n\n\n\n";
	system("pause");	
	menu();
	
}


wstring stringToWString(const string& str) {
	wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str);

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
// main menu
void menu() {
	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                       Deposite             [1]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                       Withdraw             [2]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                   Quick Withdraw           [3]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                     Your balance           [4]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|   send money (same compeny clients only)   [5]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Take out your card.        [6]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;


	cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 6] : ";
	cin >> list;
	while (list < 0 || list > 6)
	{
		cout << "\n\t\t\t\t\t\t invalide Number! ";
		cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 6] : ";
		cin >> list;

	}
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
		quickwithraw();
		break;
	case 4:
		system("cls");
		yourbalance();
		break;
	case 5:
		system("cls");
		sendmony();
		break;
	case 6:
		system("cls");
		login();
		break;
	default:
		break;
	}
}


// login

void login() {
	clients = getrecordfromfile();
	int found = 0;
	string username, password , accountNumber = "A";

	
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  accounte number  : ";

		cin >> username;
		accountNumber += username;
		system("cls");
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  accounte number  : " << left << setw(23) << accountNumber << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      pin code     : ";
		cin >> password;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		for (client& user : clients) {
			if (user.accountNumber == accountNumber && user.pingcode == password) {
				found++;
				logedinclient = user;

				
				break;
			}
		}
		while (found <= 0) {
			system("cls");
			cout << "\t\t\t\t\tLogin Failed: Incorrect Account Number or pin code. Please try again.       \n";
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  accounte number  : ";
			accountNumber = "A";
			cin >> username;
			accountNumber += username;
			system("cls");
			cout << "\t\t\t\t\tLogin Failed: Incorrect Account Number or pin code. Please try again.       \n";
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|  accounte number  : " << left << setw(23) << accountNumber << "    |" << endl;;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			cout << "\t\t\t\t\t\t|      pin code     : ";
			cin >> password;
			cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
			for (client& user : clients) {
				if (user.accountNumber == accountNumber && user.pingcode == password) {
					found++;
					break;
				}
			}
		};
		system("cls");
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  accounte number  : " << left << setw(23) << accountNumber << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|      pin code     : " << left << setw(23) << password << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		Sleep(500);
		menu();
	
	menu();


}

// Deposite
bool validamount(int number) {
	if (number < 50)
		return false;
	int lastDigit = number % 10;           
	int secondLastDigit = (number / 10) % 10; 

	
	if (lastDigit == 0 && (secondLastDigit == 5 || secondLastDigit == 0)) {
		return true;
	}
	return false;
}

void Deposite() {

	
	system("cls");
	int counter = 0;
	for (client& temp : clients) {
		if (temp.accountNumber == logedinclient.accountNumber)
		{
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
			cout << "\t\t\t\t\t\t enter the deposite amount, the amount shoud be multiplied by 50 and gretar or equal 50 : \n";
			cout << "\t\t\t\t\t\t ";
			cin >> depositamaount;
			while(!validamount(depositamaount)) {
				cout << "\n\t\t\t\t\t\t invalid amount!";
				cout << "\n\t\t\t\t\t\t the amount shoud be multiplied by 50 and gretar or equal 50 !";
				cout << "\n\t\t\t\t\t\t enter the deposite amount : \n";
				cout << "\t\t\t\t\t\t ";
				cin >> depositamaount;
			}

			char answer;
			cout << "\n\t\t\t\t\t\t are you sure you want to deposite Y/N: ";
			cin >> answer;

			if (toupper(answer) == 'Y') {
				const string clientfolder = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname; // change this to clients transactions folder in the admin folder (projectAlgo4)
				wstring wclientfolder = stringToWString(clientfolder);

				if (CreateDirectory(wclientfolder.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
					//
				}
				stclienthistory history;
				history.from = "        -";
				history.to = "Me";
				history.amount = "+ " + to_string(depositamaount);
				history.date = getdate();
				history.object = "deposite in the ATM machin";
				
				const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname + "\\history.txt"; // change this to clients transactions folder in the admin folder (projectAlgo4)
				string receiverrecord = converthistorytoline(history, "#//#");
				addrecordtofile(receiverrecord, clientshistory);
				temp.accountBalance += depositamaount;
				reuplodefile(clientsfile);
				clients = getrecordfromfile();
				
				
				cout << "\n\t\t\t\t\t\t the amount has been sent successfully .\n\n";
			
				system("pause");
				menu();

			}
			else
			{
				menu();

			}

			break;
		}



	}



}


// withraw

void withraw() {

	int counter = 0;
	for (client& temp : clients) {
		if (temp.accountNumber == logedinclient.accountNumber)
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
			cout << "\t\t\t\t\t\t enter the withraw amount , the amount shoud be multiplied by 50 and gretar or equal 50 : \n";
			cout << "\t\t\t\t\t\t ";
			cin >> withrawamaount;


			while (withrawamaount > temp.accountBalance) {
				cout << "\n\t\t\t\t\t\t amount is bigger then the balance you can withdraw up to " << temp.accountBalance << endl;
				cout << "\t\t\t\t\t\t ";
				cin >> withrawamaount;
			};
			while (!validamount(withrawamaount)) {
				cout << "\n\t\t\t\t\t\t invalid amount!";
				cout << "\n\t\t\t\t\t\t the amount shoud be multiplied by 50 and gretar or equal 50 !";
				cout << "\n\t\t\t\t\t\t enter the withraw amount : \n";
				cout << "\t\t\t\t\t\t ";
				cin >> withrawamaount;
			}

			char answer;
			cout << "\n\t\t\t\t\t\t are you sure you want to withdraw Y/N: ";
			cin >> answer;

			if (toupper(answer) == 'Y') {
				stclienthistory history;
				history.from = "        -";
				history.to = "Me";
				history.amount = "- " + to_string(withrawamaount);
				history.date = getdate();
				history.object = "withraw in the ATM machin";

				const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + temp.Fullname + "\\history.txt"; // change this to clients transactions folder in the admin folder (projectAlgo4)
				string receiverrecord = converthistorytoline(history, "#//#");
				addrecordtofile(receiverrecord, clientshistory);
				temp.accountBalance -= withrawamaount;
				
				system("cls");
				cout << "\n\t\t\t\t\t\t done successfully the new amount is " << temp.accountBalance << endl;

				cout << "\n\n";
				reuplodefile(clientsfile);
				clients = getrecordfromfile();


				system("pause");
				menu();

			}
			else
			{
				menu();

			}

			break;
		}



	}



}
// splite
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

// convert line to record
client convertlinetorecor(vector <string> temp) {
	client tempstruct;

	tempstruct.accountNumber = temp[0];
	tempstruct.Fullname = temp[1];
	tempstruct.phoneNumer = temp[2];
	tempstruct.pingcode = temp[3];
	tempstruct.accountBalance = stof(temp[4]);



	return tempstruct;
}
// convert record to line 
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

// update date
void reuplodefile(string filename) {
	if (filename == clientsfile) {
		Myfile.open(filename, ios::out);
		for (client& c : clients) {
			

				string line = convertclientrecordtoline(c, "#//#");



				if (Myfile.is_open())
				{
					Myfile << line << endl;

				}
			
		}

		Myfile.close();
	}

}

// get records
vector <client> getrecordfromfile() {
	vector <client> clients;
	Myfile.open(clientsfile, ios::in);

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
void getamount(int amount) {
	for (client& user : clients) {
		if (user.accountNumber == logedinclient.accountNumber) {

			user.accountBalance -= amount;
			stclienthistory history;
			history.from = "        -";
			history.to = "Me";
			history.amount = "- " + to_string(amount);
			history.date = getdate();
			history.object = "quick withraw in the ATM machin";

			const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + user.Fullname + "\\history.txt"; // change this to clients transactions folder in the admin folder (projectAlgo4)
			string receiverrecord = converthistorytoline(history, "#//#");
			addrecordtofile(receiverrecord, clientshistory);
			
			cout << "\n\t\t\t\t\t\t done successfully the new amount is " << user.accountBalance << endl;

			cout << "\n\n";
			reuplodefile(clientsfile);
			clients = getrecordfromfile();
			system("pause");
			
		}
	}
}
// quick withraw
void quickwithraw() {
	cout << "\t\t\t\t\t\t [1]50dh                                        [5]500dh\n";
	cout << "\t\t\t\t\t\t [2]100dh                                       [6]1000dh\n";
	cout << "\t\t\t\t\t\t [3]200dh                                       [7]2000dh\n";
	cout << "\t\t\t\t\t\t [4]400dh                                       [8]on other amount\n";
	int amount;
	cout << "\t\t\t\t\t\t select the amount number in the list \n";
	cin >> amount;
	while (amount < 0 || amount > 6)
	{
		cout << "\n\t\t\t\t\t\t invalide Number! ";
		cout << "\t\t\t\t\t\t select the amount number in the list \n";
		cin >> amount;

	}
	switch (amount) {
	case 1:
		getamount(50);
		menu();
		break;

	case 2:
		getamount(100);
		menu();
		break;
	case 3:
		getamount(200);
		menu();
		break;
	case 4:
		getamount(400);
		menu();
		break;
	case 5:
		getamount(500);
		menu();
		break;
	case 6:
		getamount(1000);
		menu();
		break;
	case 7:
		getamount(2000);
		menu();
		break;
	case 8:
		withraw();
		break;





	}

}







// send mony (same company clients)

void sendmony() {
	clients = getrecordfromfile();
	int foundreceiver = 0;
	int foudsender = 0;
	int counter = 1;

	string username, phonenumber, accountNumber = "A";

	cout << "\t\t\t\t\t\t enter some details about the client you want to send mony to \n\n\n\n";
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|  accounte number  : A";

	cin >> username;
	accountNumber += username;
	system("cls");
	cout << "\t\t\t\t\t\t enter some details about the client you want to send mony to \n\n\n\n";
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|  accounte number  : " << left << setw(23) << accountNumber << "    |" << endl;;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|  phone number     : ";
	cin >> phonenumber;
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	for (client& user : clients) {
		if (foudsender > 0 && foundreceiver > 0) {
			break;
		}
		if (user.accountNumber == accountNumber && user.phoneNumer == phonenumber) {
			foundreceiver = counter;
			
			


			
		}
		
		
		if (user.accountNumber == logedinclient.accountNumber && user.pingcode == logedinclient.pingcode) {
			foudsender = counter;
			

		}
		counter++;
	}
	while (foundreceiver <= 0) {
		system("cls");
		cout << "\t\t\t\t\tThere is no client with account number or phone number. Please try again.       \n";
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  accounte number  : A";
		accountNumber = "A";
		cin >> username;
		accountNumber += username;
		system("cls");
		cout << "\t\t\t\t\tThere is no client with account number or phone number. Please try again.       \n";
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  accounte number  : " << left << setw(23) << accountNumber << "    |" << endl;;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		cout << "\t\t\t\t\t\t|  phone number     : ";
		cin >> phonenumber;
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		
	};
	char ansewr;
	cout << "\t\t\t\t\t\tis this the user you want to send Money to : " << clients[foundreceiver-1].Fullname << " answer By Y/N" << endl;
	cout << "\n\t\t\t\t\t\t";
	cin >> ansewr;
	float amountTosend;
	if (toupper(ansewr) == 'Y') {
		cout << "\t\t\t\t\t\tenter the amount you want to send : ";
		cin >> amountTosend;
		while (amountTosend > logedinclient.accountBalance)
		{
			cout << "\t\t\t\t\t\tinvalid amount you can send up tp : " << logedinclient.accountBalance;
			cout << "\n\t\t\t\t\t\tenter the amount you want to send : ";
			
			cin >> amountTosend;
		}

		clients[foudsender-1].accountBalance -= amountTosend;
		clients[foundreceiver-1].accountBalance += amountTosend;
		logedinclient.accountBalance -= amountTosend;

		cout << "\t\t\t\t\t\tthe amount has been sent successfully to "+ clients[foundreceiver-1].Fullname + " your balance now is " << logedinclient.accountBalance << endl ;

		reuplodefile(clientsfile);
		clients = getrecordfromfile();

		system("pause");
		menu();


	}
	
	
}



int main()
{


	login();
	//manageUsers();



	return 0;
}