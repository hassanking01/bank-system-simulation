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





struct stclienthistory
{
	string date;
	string to;
	string object;
	string from;
	string amount;
	string accountNumber;
};

struct stclientrequest
{
	stclienthistory request;
	bool markforacceptordecline = false;
};
// structer
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

const string clientsfile = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients.txt"; // change this to client.txt path in the admin folder (progectalgo4)




vector <client> getrecordfromfile();
vector <client> clients = getrecordfromfile();
client convertlinetorecor(vector <string> temp);
string convertclientrecordtoline(client temp, string dele);
vector <string> spliteline(string line, string dele);
void reuplodefile(string filename);

void Request();

void menu();
void sendmony();
void login();
void history();
void addrecordtofile(string line, string filename);
void reuplodrequstfile();
void getRequest();

string getdate() {

	time_t now = time(0);


	char* dt = ctime(&now);




	tm* gmtm = gmtime(&now);
	dt = asctime(gmtm);
	return dt;
}


string converthistorytoline(stclienthistory temp, string dele) {
	string line;
	line += temp.amount + dele;
	line += temp.date + dele;
	line += temp.from + dele;
	line += temp.to + dele;
	line += temp.object ;
	

	return line;
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
// main menu
void menu() {

	string logedinclientpath = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname; // change this to clients transactions folder path in the admin folder (projectAlgo4)

	wstring wlogedinclientpath = stringToWString(logedinclientpath);

	if (CreateDirectory(wlogedinclientpath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
		//
	}

	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                 Transaction History        [1]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                       Request              [2]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                     Your balance           [3]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|   send money (same compeny clients only)   [4]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                        Logout.             [5]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;


	cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 5] : ";
	cin >> list;
	while (list < 0 || list > 5)
	{
		cout << "\n\t\t\t\t\t\t invalide Number! ";
		cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 5] : ";
		cin >> list;

	}
	switch (list)
	{
	case 1:
		system("cls");
		history();
		break;
	case 2:
		system("cls");
		Request();
		break;
	case 3:
		system("cls");
		yourbalance();
		break;
	case 4:
		system("cls");
		sendmony();
		break;
	case 5:
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
	string username, password, accountNumber = "A";


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
				logedinclient = user;
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




}
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
vector <stclienthistory> gethistoryfromfile() {
	vector <stclienthistory> clientshistory;
	const string clienthistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname + "\\history.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
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
void printhistory() {
	logedinclient.history = gethistoryfromfile();
	for (stclienthistory& history : logedinclient.history) {
		if (history.from == "Me") {
			cout << "\t\t\t\t|" << left << setw(23) << "          " + history.from;
		}
		else {
			cout << "\t\t\t\t|" << left << setw(23) << " " + history.from;
		}
		if (history.to == "Me") {
			cout << "|" << left << setw(23) << "        " + history.to;
		}
		else {
			cout << "|" << left << setw(23) << " " + history.to;
		}

		cout << "|" << left << setw(27) << " " + history.date;
		cout << "|" << left << setw(34) << " " + history.amount;
		cout << "|" << left << setw(35) << " " + history.object << "|" << endl;

		cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	}
}
void history() {

	cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "\t\t\t\t|" << left << setw(23) << "        From";
	cout << "|" << left << setw(23) << "          To";
	cout << "|" << left << setw(27) << "            Date";
	cout << "|" << left << setw(34) << "              Amount              ";
	cout << "|" << left << setw(34) << "              Subject              |" << endl;

	cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	printhistory();

	system("pause");
	menu();


}





// see Request

stclientrequest covertrequstlinetorecod(vector <string> temp) {
	stclientrequest tempstruct;

	tempstruct.request.amount = temp[0];
	tempstruct.request.date = temp[1];
	tempstruct.request.from = temp[2];
	tempstruct.request.to = temp[3];
	tempstruct.request.object = temp[4];
	tempstruct.request.accountNumber = temp[5];
	return tempstruct;
}
vector <stclientrequest> getrequstfromfile() {
	vector <stclientrequest> clientshistory;
	const string clienthistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname + "\\request.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
	Myfile.open(clienthistory, ios::in);

	if (Myfile.is_open())
	{
		stclientrequest temp;
		string line;
		while (getline(Myfile, line))
		{
			temp = covertrequstlinetorecod(spliteline(line, "#//#"));
			clientshistory.push_back(temp);
		}


		Myfile.close();
	}
	return clientshistory;
}
void decline(int rqnum) {
	int foundfrom = 0;
	int foundto = 0;
	for (client& user : clients) {
		if (foundfrom != 0 && foundto != 0)
		{
			logedinclient.request[rqnum - 1].markforacceptordecline = true;
			break;
		}
		if (logedinclient.request[rqnum - 1].request.from == user.Fullname) {

			foundfrom++;
		}
		if (logedinclient.Fullname == user.Fullname) {
			foundto++;
	
		}
	}
	reuplodrequstfile();
	logedinclient.request = getrequstfromfile();
	cout << "\n\n\t\t\t\t\t\t\tRerquest Declined successfully . \n\n";
	system("pause");
	Request();
}
void acceptrq(int rqnum) {
	while (stof(logedinclient.request[rqnum - 1].request.amount) > logedinclient.accountBalance)
	{
		cout << "\n\n\t\t\t\t\t\t\t Your balance is too low to complete this transaction. Please deposit additional funds. . \n\n";
		system("pause");
		getRequest();
		
	}
	int foundfrom = 0;
	int foundto = 0;
	stclienthistory senderhistory, receiverhistory;


	
	const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname + "\\history.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
	

	
	
	


	for (client &user : clients) {
		if (foundfrom != 0 && foundto != 0)
		{
			logedinclient.request[rqnum - 1].markforacceptordecline = true;
			break;
		}
		if (logedinclient.request[rqnum - 1].request.from == user.Fullname && logedinclient.request[rqnum - 1].request.accountNumber == user.accountNumber) {
			string receivernclientpathtxt = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + user.Fullname + "\\history.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
			string receivernclientpath = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + user.Fullname; // change this to clients transactions folder path in the admin folder (projectAlgo4)

			wstring wlogedinclientpath = stringToWString(receivernclientpath);

			if (CreateDirectory(wlogedinclientpath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
				//
			}
			receiverhistory.from = logedinclient.Fullname;
			receiverhistory.to = "Me";
			receiverhistory.date = getdate();
			if (!receiverhistory.date.empty() && receiverhistory.date.back() == '\n') {
				receiverhistory.date.pop_back();
			}
			receiverhistory.amount = "+ " +logedinclient.request[rqnum - 1].request.amount;
			receiverhistory.object = "accepted your request : " + logedinclient.request[rqnum - 1].request.object;
			string receiverrecord = converthistorytoline(receiverhistory, "#//#");
			addrecordtofile(receiverrecord, receivernclientpathtxt);
			user.accountBalance += stof(logedinclient.request[rqnum - 1].request.amount);
			foundfrom++;
		}
		if (logedinclient.Fullname == user.Fullname) {
			foundto++;
			senderhistory.date = getdate();
			if (!senderhistory.date.empty() && senderhistory.date.back() == '\n') {
				senderhistory.date.pop_back();
			}
			senderhistory.amount = "- " + logedinclient.request[rqnum - 1].request.amount;
			senderhistory.from = "Me";
			senderhistory.to = logedinclient.request[rqnum - 1].request.from;
			senderhistory.object = "you accepted request : " + logedinclient.request[rqnum - 1].request.object;
			string senderrecord = converthistorytoline(senderhistory, "#//#");
			addrecordtofile(senderrecord, clientshistory);
			user.accountBalance -= stof(logedinclient.request[rqnum - 1].request.amount);
		}
	}
	reuplodefile(clientsfile);
	clients = getrecordfromfile();
	reuplodrequstfile();
	logedinclient.request = getrequstfromfile();
	cout << "\n\n\t\t\t\t\t\t\tRerquest Accepted The Amount is sent successfully . \n\n";
	system("pause");
	Request();
}
string convertrequesttiline(stclientrequest c, string dele) {
	string line;
	line += c.request.amount + dele;
	line += c.request.date + dele;
	line += c.request.from + dele;
	line += c.request.to + dele;
	line += c.request.object + dele ;
	line += c.request.accountNumber;
	return line;

}
void reuplodrequstfile() {
	const string clienrequests = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname + "\\request.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
		Myfile.open(clienrequests, ios::out);
		for (stclientrequest& c : logedinclient.request) {
			if (c.markforacceptordecline == false) {

				string line = convertrequesttiline(c, "#//#");



				if (Myfile.is_open())
				{
					Myfile << line << endl;

				}
			}
		}

		Myfile.close();
	
}
void showrequist(int rqNumber) {
	system("cls");
	cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	cout << "\t\t\t\t|" << left << setw(23) << "        From";
	cout << "|" << left << setw(23) << "          To";
	cout << "|" << left << setw(27) << "            Date";
	cout << "|" << left << setw(34) << "              Amount              ";
	cout << "|" << left << setw(34) << "              Subject              |" << endl;

	cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;

	if (logedinclient.request[rqNumber - 1].request.from == logedinclient.Fullname ) {
		cout << "\t\t\t\t|" << left << setw(23) << "          Me";
	}
	else {
		cout << "\t\t\t\t|" << left << setw(23) << " " + logedinclient.request[rqNumber - 1].request.from;
	}
	if (logedinclient.request[rqNumber - 1].request.to == logedinclient.Fullname) {
		cout << "|" << left << setw(23) << "        Me";
	}
	else {
		cout << "|" << left << setw(23) << " " + logedinclient.request[rqNumber - 1].request.to;
	}

	cout << "|" << left << setw(27) << " " + logedinclient.request[rqNumber - 1].request.date;
	cout << "|" << left << setw(34) << " " + logedinclient.request[rqNumber - 1].request.amount;
	cout << "|" << left << setw(35) << " " + logedinclient.request[rqNumber - 1].request.object << "|" << endl;

	cout << "\t\t\t\t|--------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
	int action = 0;
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t\t\twhat do you want to do \n\n";
	cout << "\t\t\t\t\t\t\t|---|                                         |---|\n";
	cout << "\t\t\t\t\t\t\t| 1 |accept                                   | 2 |decline\n";
	cout << "\t\t\t\t\t\t\t|---|                                         |---|\n";
	cout << "\t\t\t\t\t\t\t";
	cin >> action;
	switch (action)
	{
	case 1:
		acceptrq(rqNumber);
		break;
	case 2:
		decline(rqNumber);
		break;

	default:
		break;
	}
	
}
void getRequest() {
	system("cls");
	logedinclient.request = getrequstfromfile();
	cout << "\t\t\t\t\t\t\t|----------------------------------------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t\t|        " << left << setw(15) << "Number";
	cout << "|" << left << setw(23) << "        From";
	cout << "|" << left << setw(34) << "              Amount              |" << endl;
	cout << "\t\t\t\t\t\t\t|----------------------------------------------------------------------------------|" << endl;
	int i = 0;
	for (stclientrequest& client : logedinclient.request) {
		cout << "\t\t\t\t\t\t\t|        " << left << setw(15) << i + 1;
		cout << "|" << left << setw(23) << " " + client.request.from;
		cout << "|" << left << setw(34) << " " + client.request.amount << "|" << endl;
		cout << "\t\t\t\t\t\t\t|----------------------------------------------------------------------------------|" << endl;
		i++;
	}
	int list = 0;
	cout << "\t\t\t\t\t\t\t select the number of the request you want to show or enter 0 to return to The Requst menu : ";
	cin >> list;
	while (list < 0 || list > i+1) {
		cout << "\t\t\t\t\t\t\t There is No request With That Number ";
		cout << "\t\t\t\t\t\t\t Please select the number of the request you want to show or enter 0 to return to The Requst menu : ";
		cin >> list;
	}
	if (list == 0) {
		Request();
	}else
	showrequist(list);
	
}
// make Request
void setRequest() {
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
	cout << "\t\t\t\t\t\t|    fullname       : ";
	getline(cin >> ws, phonenumber);
	cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
	for (client& user : clients) {
		if (foudsender > 0 && foundreceiver > 0) {
			break;
		}
		if (user.accountNumber == accountNumber && user.Fullname == phonenumber) {
			foundreceiver = counter;





		}


		if (user.accountNumber == logedinclient.accountNumber && user.pingcode == logedinclient.pingcode) {
			foudsender = counter;


		}
		counter++;




	}
	while (foundreceiver <= 0) {
		system("cls");
		cout << "\t\t\t\t\tThere is no client with account number or fullname. Please try again.       \n";
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
		cout << "\t\t\t\t\t\t|     fullname      : ";
		getline(cin >> ws, phonenumber);
		cout << "\t\t\t\t\t\t|------------------------------------------------|" << endl;
		int foundreceiver = 0;
		int foudsender = 0;
		int counter = 1;

		for (client& user : clients) {
			if (foudsender > 0 && foundreceiver > 0) {
				break;
			}
			if (user.accountNumber == accountNumber && user.Fullname == phonenumber) {
				foundreceiver = counter;





			}


			if (user.accountNumber == logedinclient.accountNumber && user.pingcode == logedinclient.pingcode) {
				foudsender = counter;


			}
			counter++;




		}

	};
	char ansewr;
	cout << "\t\t\t\t\t\t user founded are you sur to make a request to : " << clients[foundreceiver - 1].Fullname << " answer By Y/N" << endl;
	cout << "\n\t\t\t\t\t\t";
	cin >> ansewr;
	float amountTosend;
	if (toupper(ansewr) == 'Y') {
		stclientrequest senderhistory;
		cout << "\t\t\t\t\t\tenter the amount you want in the request : ";
		cin >> amountTosend;
		
		string receivernclientpath = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + clients[foundreceiver - 1].Fullname; // change this to clients transactions folder path in the admin folder (projectAlgo4)

		wstring wlogedinclientpath = stringToWString(receivernclientpath);

		if (CreateDirectory(wlogedinclientpath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			//
		}
		senderhistory.request.date = getdate();
		if (!senderhistory.request.date.empty() && senderhistory.request.date.back() == '\n') {
			senderhistory.request.date.pop_back();
		}
		senderhistory.request.amount = to_string(amountTosend);
		senderhistory.request.from = logedinclient.Fullname;
		senderhistory.request.to = clients[foundreceiver - 1].Fullname;
		senderhistory.request.accountNumber = logedinclient.accountNumber;
		cout << "\n\t\t\t\t\t\twhats the Subject of this request make it short (33 characters Max!) : ";
		getline(cin >> ws, senderhistory.request.object);
		while (senderhistory.request.object.size() > 34) {
			cout << "\n\t\t\t\t\t\ttoo long make it shorter!!";
			cout << "\n\t\t\t\t\t\twhats the Subject of this request make it short (33 characters Max!) : ";
			getline(cin >> ws, senderhistory.request.object);
		}
		cout << endl;
		string senderrecord = convertrequesttiline(senderhistory , "#//#");

		string receivernclientpathtxt = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + clients[foundreceiver - 1].Fullname + "\\request.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)

		addrecordtofile(senderrecord, receivernclientpathtxt);


		cout << "\t\t\t\t\t\tthe request has been sent successfully to " + clients[foundreceiver - 1].Fullname << endl;

		reuplodefile(clientsfile);
		clients = getrecordfromfile();

		system("pause");
		menu();


	}
}
// withraw



void Request() {

	system("cls");
	int list;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  See All Request's         [1]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  Make A Request            [2]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;
	cout << "\t\t\t\t\t\t|                  Return to menu            [3]     |" << endl;
	cout << "\t\t\t\t\t\t|----------------------------------------------------|" << endl;

	cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 3] : ";
	cin >> list;


	while ( list <=0  || list > 3) {
		cout << "\n\t\t\t\t\t\t The number you enterd is not On the List!!";
		cout << "\n\t\t\t\t\t\t choose what do you want to do [1 to 3] : ";
		cin >> list;
	}
	switch (list)
	{
	case 1:
		system("cls");
		getRequest();

		break;
	case 2:
		system("cls");
		setRequest();
		break;
	case 3:
		system("cls");
		menu();
		break;
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









void addrecordtofile(string line, string filename) {
	Myfile.open(filename, ios::out | ios::app);
	if (Myfile.is_open())
	{
		Myfile << line << endl;
		Myfile.close();
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
		int foundreceiver = 0;
		int foudsender = 0;
		int counter = 1;

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

	};
	char ansewr;
	cout << "\t\t\t\t\t\tis this the user you want to send Money to : " << clients[foundreceiver - 1].Fullname << " answer By Y/N" << endl;
	cout << "\n\t\t\t\t\t\t";
	cin >> ansewr;
	float amountTosend;
	if (toupper(ansewr) == 'Y') {
		stclienthistory senderhistory, receiverhistory;
		cout << "\t\t\t\t\t\tenter the amount you want to send : ";
		cin >> amountTosend;
		while (amountTosend > logedinclient.accountBalance)
		{
			cout << "\t\t\t\t\t\tinvalid amount you can send up tp : " << logedinclient.accountBalance;
			cout << "\n\t\t\t\t\t\tenter the amount you want to send : ";

			cin >> amountTosend;
		}
		string receivernclientpath = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + clients[foundreceiver - 1].Fullname; // change this to clients transactions folder path in the admin folder (projectAlgo4)

		wstring wlogedinclientpath = stringToWString(receivernclientpath);

		if (CreateDirectory(wlogedinclientpath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {
			//
		}
		senderhistory.date = getdate();
		if (!senderhistory.date.empty() && senderhistory.date.back() == '\n') {
			senderhistory.date.pop_back();
		}
		senderhistory.amount = "- " + to_string(amountTosend);
		senderhistory.from = "Me";
		senderhistory.to = clients[foundreceiver - 1].Fullname;
		cout << "\n\t\t\t\t\t\twhats the Subject of this transaction make it short (33 characters Max!) : ";
		getline(cin >> ws, senderhistory.object);
		while (senderhistory.object.size() > 34) {
			cout << "\n\t\t\t\t\t\ttoo long make it shorter!!";
			cout << "\n\t\t\t\t\t\twhats the Subject of this transaction make it short (33 characters Max!) : ";
			getline(cin >> ws, senderhistory.object);
		}
		cout << endl;
		string senderrecord = converthistorytoline(senderhistory, "#//#");
		const string clientshistory = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + logedinclient.Fullname + "\\history.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)
		string receivernclientpathtxt = "C:\\Users\\hassa\\Desktop\\c++ courses\\projectAlgo4\\clients Transactions\\" + clients[foundreceiver - 1].Fullname + "\\history.txt"; // change this to clients transactions folder path in the admin folder (projectAlgo4)

		addrecordtofile(senderrecord, clientshistory);
		receiverhistory = senderhistory;
		receiverhistory.from = logedinclient.Fullname;
		receiverhistory.to = "Me";
		receiverhistory.amount = "+ " + to_string(amountTosend);
		string receiverrecord = converthistorytoline(receiverhistory, "#//#");
		addrecordtofile(receiverrecord, receivernclientpathtxt);
		clients[foudsender - 1].accountBalance -= amountTosend;
		clients[foundreceiver - 1].accountBalance += amountTosend;
		logedinclient.accountBalance -= amountTosend;

		cout << "\t\t\t\t\t\tthe amount has been sent successfully to " + clients[foundreceiver - 1].Fullname + " your balance now is " << logedinclient.accountBalance << endl;

		reuplodefile(clientsfile);
		clients = getrecordfromfile();

		system("pause");
		menu();


	}


}



int main()
{


	login();


	return 0;
}