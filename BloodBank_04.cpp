#include <iostream>
#include "Donor.h"
#include "Blood.h"
#include "Recipient.h"
#include "Admin.h"
using namespace std;
int User::IDcounter = User::getIDcounter();
Donor d;
Recipient r;
short operation = 2;

void signUp() {
	cout << "\n\t\t\t 1-As Donor\t2-As Recipeant" << endl;
	cout << " \t\t\t ";
	cin >> operation;
	system("CLS");
	if (operation == 1)
		d.signup();
	else if (operation == 2)
		r.signup();
}
bool DonorLogin() {
	string email, password;
	unordered_map <string, string> Data;
	cout << "\n\t\t\t Email: " << endl;
	cout << " \t\t\t ";
	cin >> email;
	cout << "\n\t\t\t password: " << endl;
	cout << " \t\t\t ";

	char i = ' ';
	while (true) {
		i = _getch();
		if (i == '\n' || i == '\r')
			break;
		password.push_back(i);
		cout << '*';
	}

	Data = d.login();
	if (Data.count(email)) {
		if (Data.at(email) == password) {
			cout << "\n\t\t\tlogin sucsess\n";
			d = Donor::setData(Donor::getDonorData(email));//kda al d b2a gwaha al Donor al ana bt3aml m3ah
			operation = _getch();
			system("CLS");
			return true;
		}
		else {
			cout << "\n\t\t\tWrong password";
			return false;
		}
		
	}
	else {
		cout << "\n\t\t\tInvalid email address\n";
		return false;
	}
}
void DonationRequest(){
	d.donationRequest(d.getBlood().getType());
}
void DonorUpdateData() {
	cout << "\n\t\t\tupdate: 1-name\t2-password\t3-age\t4-share\t5-phone" << endl;
	cout << " \t\t\t ";
	string value;
	cin >> operation;
	cout << "\n\t\t\t its value: " << endl;
	cout << " \t\t\t ";
	getline(cin, value);
	if (operation == 1)
		d.updateData("name", value);
	else if (operation == 2)
		d.updateData("password", value);
	else if (operation == 3)
		d.updateData("age", value);
	else if (operation == 4)
		d.updateData("share", value);
	else if (operation == 5)
		d.updateData("phone", value);
}
void DonorPath() {
	if (DonorLogin()) {
		cout << "\n\t\t\t 1-Donation request\t2-update Data\t3-Delete account\t4-logout" << endl;
		cout << " \t\t\t ";
		cin >> operation;
		system("CLS");
		if (operation == 1)
			DonationRequest();
		else if (operation == 2)
			DonorUpdateData();
		else if (operation == 3)
			d.deleteAcc();
		else
			return;
	}
}

bool RecipientLogin() {
	string email, password;
	unordered_map <string, string> Data;
	cout << "\n\t\t\t Email: " << endl;
	cout << " \t\t\t ";
	cin >> email;
	cout << "\n\t\t\t password: " << endl;
	cout << " \t\t\t ";

	char i;
	while (true) {
		i = _getch();
		if (i == '\n' || i == '\r')
			break;
		password.push_back(i);
		cout << '*';
	}
	Data = r.login();
	if (Data.count(email)) {
		if (Data.at(email) == password) {
			cout << "\n\t\t\tlogin sucsess\n";
			r = Recipient::setData(Recipient::getRecipientData(email));//kda al d b2a gwaha al Donor al ana bt3aml m3ah
			operation = _getch();
			system("CLS");
			return true;
		}
		else {
			cout << "\n\t\t\tWrong password\n";
			return false;
		}
	}
	else {
		cout << "\n\t\t\tInvalid email address\n";
		return false;
	}
}
void SearchForAvilabilty() {
	string bloodType;
	cout << "\n\t\t\t blood Type: " << endl;
	cout << " \t\t\t ";
	cin >> bloodType;
	if (r.searchForAvailabilityOfBlood(bloodType))
		cout << "\t\t\tAvilabile\n";
	else
		cout << "\t\t\tNot Avilabile\n";
}
void RecipientUpdateData() {
	system("CLS");
	cout << "\n\t\t\tupdate:\n\t\t\t1-name\n\t\t\t2-password\n\t\t\t3-age\n\t\t\t4-Hospital\n\t\t\t5-Doctor of the case" << endl;
	cout << " \t\t\t ";
	string value;
	cin >> operation;
	cout << "\n\t\t\t its value: " << endl;
	cout << " \t\t\t ";
	getline(cin, value);
	if (operation == 1)
		r.updateData("name", value);
	else if (operation == 2)
		r.updateData("password", value);
	else if (operation == 3)
		r.updateData("age", value);
	else if (operation == 4)
		r.updateData("hospital", value);
	else if (operation == 5)
		r.updateData("doctor", value);
}
void RequestBloodData() {
	string bloodType;
	int Quantity;
	while (true) {
		cout << "\n\t\t\t Blood Type: " << endl;
		cout << " \t\t\t ";
		cin >> bloodType;
		for (int i = 0; i < bloodType.size(); i++)
			bloodType[i] = toupper(bloodType[i]);
		if (bloodType == "A+" || bloodType == "A-" || bloodType == "B+" || bloodType == "B-" || bloodType == "AB+" || bloodType == "AB-" || bloodType == "O+" || bloodType == "O-")
			break;
		cerr << "\t\t\tWrong blood type : please re-enter:";
	}
	cout << "\n\t\t\t Quantity: " << endl;
	cout << " \t\t\t ";
	cin >> Quantity;
	r.requestBloodType(bloodType, Quantity);
}
void RecipientPath() {
	if (RecipientLogin()) {
		cout << "\n\t\t\t1-Search for the availability\n\t\t\t2-update Data\n\t\t\t3-Delete account\n\t\t\t4-Display all blood data\n\t\t\t5-request blood\n\t\t\t6-logout" << endl;
		cout << " \t\t\t ";
		cin >> operation;
		if (operation == 1)
			SearchForAvilabilty();
		else if (operation == 2)
			RecipientUpdateData();
		else if (operation == 3)
			r.deleteAcc();
		else if (operation == 4)
			r.findBloodData();
		else if (operation == 5)
			RequestBloodData();
		else
			return;
	}
}
int main() {
	Admin::updateBlood("A+.txt");
	Admin::updateBlood("A-.txt");
	Admin::updateBlood("B+.txt");
	Admin::updateBlood("B-.txt");
	Admin::updateBlood("AB+.txt");
	Admin::updateBlood("AB-.txt");
	Admin::updateBlood("O+.txt");
	Admin::updateBlood("O-.txt");
	
	while (operation == 2) {
		cout << "\n\t\t\t 1-signUp\t2-Login" << endl;
		cout << " \t\t\t ";
		cin >> operation;
		system("CLS");
		if (operation == 1)
			signUp();
		else if (operation == 2) {
			cout << "\n\t\t\t 1-As Donor\t2-As Recipeant" << endl;
			cout << " \t\t\t ";
			cin >> operation;
			system("CLS");
			if (operation == 1)
				DonorPath();
			else if (operation == 2)
				RecipientPath();
		}
		cout << "\n\t\t\t 1-exit\t2-continue" << endl;
		cout << " \t\t\t ";
		cin >> operation;
		system("CLS");
	}
	User::sendIDCounter();
}
