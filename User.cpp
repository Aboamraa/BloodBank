#include "User.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <cstdio>
#include "Admin.h"
using namespace std;

void User::setData()
{
	cout << "\n\t\t\t Enter Name:" << endl;
	cout << " \t\t\t ";
	cin.ignore();
	getline(cin, name);
	cout << "\n\t\t\t Enter Email:" << endl;
	cout << " \t\t\t ";
	cin >> email;
	cout << "\n\t\t\t Enter Password:" << endl;
	cout << " \t\t\t ";
	char i = ' ';
	while (true) {
		i = _getch();
		if ((i == '\n' || i == '\r') && password.size() >= 8)
			break;
		else if ((i == '\n' || i == '\r') && password.size() < 8) {
			cerr << "\n\t\t\t Password must be at least 8 charcter\nplease re-enter the password: " << endl;
			cout << " \t\t\t ";
			password.clear();
			continue;
		}
		cout << '*';
		password.push_back(i);
	}

	cout << "\n\t\t\t Enter Age:" << endl;
	cout << " \t\t\t ";
	cin >> age;
	if (Admin::checkAge(age)) {
		cout << "\t\t\tinvalid Age\n";
		exit(-1);
	}
	cout << "\n\t\t\t Enter Gender:" << endl;
	cout << " \t\t\t ";
	gender = _getche();
	gender = toupper(gender);
	while (true) {
		cout << "\n\t\t\t Enter blood Type:" << endl;
		cout << " \t\t\t ";
		string bT;
		cin >> bT;
		for (int i = 0; i < bT.size(); i++)
			bT[i] = toupper(bT[i]);
		blood.setType(bT);
		if (blood.getType() == "A+" || blood.getType() == "A-" || blood.getType() == "B+" || blood.getType() == "B-" || blood.getType() == "AB+" || blood.getType() == "AB-" || blood.getType() == "O+" || blood.getType() == "O-")
			break;
		else
			cerr << "Invalid Blood Type: please re-enter\n";
	}
}

unordered_map<string, string> User::login(string whoWillLogin)
{
	unordered_map<string, string> DataInFile;
	ifstream Login(whoWillLogin);//hnb3t hna al variable al fo2 dh bs lazm al awl n5le al format bta3t al 2 file zy b3d
	string e, p, junk;
	while (Login.good()) {
		getline(Login, e, ',');
		getline(Login, p, ',');
		getline(Login, junk, '\n');
		DataInFile.insert({ e,p });
	}
	Login.close();
	return DataInFile;
}

void User::sendIDCounter()
{
	ofstream file("IDcounter.txt");
	file << IDcounter;
	file.close();
}

int User::getIDcounter()
{
	ifstream file("IDcounter.txt");
	int count;
	file >> count;
	file.close();
	return count;
}

Blood User::getBlood()
{
	return blood;
}

void User::updateData(string DataToUpdate, string itsvalue, string fileName)
{
	vector <string>Data;
	vector <vector<string>>row;
	string line; 
	fstream file(fileName, ios::in);
	fstream temp("temp.txt", ios::out);

	if (fileName == "DonorData.txt") {//email,password,share,ID,phone,age,gender,name,otherData(7)\n -> new line
		while(file.good()){//byn2l mn kol str l al tabe (maben kol user w al b3do)
			getline(file, line, ',');//line = email
			if (line.empty())
				continue;
			Data.push_back(line);

			if (line != email) {
				getline(file, line, '\n'); //junk line m4 dh al user al 3yzeno
				Data.push_back(line);
				row.push_back(Data);
				Data.clear();
			}
			else{
				if (DataToUpdate == "lastDonationDate") {//14D 15MM 16YYY
					for (int i = 0; i < 14; i++) {
						getline(file, line, ',');
							Data.push_back(line);
					}
					Data.push_back(itsvalue);//Date of last donation seprated by (,)
					//getline(file, line, ',');
					//getline(file, line, ',');
					//getline(file, line, ',');
					getline(file, line, '\n');
					row.push_back(Data);
					Data.clear();
					continue;
				}
				if (DataToUpdate == "delete")
					continue;
				for (int i = 0; i < 8; i++) {//al data bta3t kol str lw7do
					if (i >= 7)
						getline(file, line, '\n');
					else {
						getline(file, line, ',');
						if (i == 0 && DataToUpdate == "password") {
							line = itsvalue;
							for (char i : line)
								password.push_back(i);
						}
						else if (i == 1 && DataToUpdate == "share")
							line = itsvalue;
						else if (i == 3 && DataToUpdate == "phone")
							line = itsvalue;
						else if (i == 4 && DataToUpdate == "age")
						{
							line = itsvalue;
							stringstream str(line);
							str >> this->age;
						}
						else if (i == 6 && DataToUpdate == "name") {
							line = itsvalue;
							this->name = line;
						}
					}
					Data.push_back(line);
				}
				row.push_back(Data);
				Data.clear();
			}
		}
	}

	else if (fileName == "RecipientData.txt") {//email,password,ID,age,gender,name,bloodType,hospitalName,DoctorOftheCase
		while (file.good()) {
			getline(file, line, ',');//line = email
			if (line.empty())
				continue;
			Data.push_back(line);
			if (line != email)
			{
				getline(file, line, '\n');
				Data.push_back(line);
				row.push_back(Data);
				Data.clear();
			}
			else {
				if (DataToUpdate == "delete")
					continue;
				for (int i = 0; i < 8; i++) {
					getline(file, line, ',');
					if (i == 0 && DataToUpdate == "password") {
						line = itsvalue;
						for (char i : line)
							password.push_back(i);
					}
					else if (i == 2 && DataToUpdate == "age")
					{
						line = itsvalue;
						stringstream str(line);
						str >> this->age;
					}
					else if (i == 4 && DataToUpdate == "name") {
						line = itsvalue;
						this->name = line;
					}
					else if (i == 6 && DataToUpdate == "hospital")
						line = itsvalue;
					else if (i == 7 && DataToUpdate == "doctor")
						line = itsvalue;
					Data.push_back(line);	
				}
				row.push_back(Data);
				Data.clear();
			}
		}
	}
	row.shrink_to_fit();
	for (vector<string>i : row) {//nb3t al data l al file tane b3d ma 3dlnaha
		for (string j : i) {
			if (j.back() == ',')
				temp << j;
			else
				temp << j << ',';
		}
		temp << '\n';
	}
	file.close();
	temp.close();

	remove(fileName.c_str());
	rename("temp.txt", fileName.c_str());
}

vector<string> User::getData(string email, string fileName)
{
	vector<string>data;
	ifstream file(fileName);
	string line;
	if (fileName == "DonorData.txt") {
		
		while (file.good()) {
			getline(file, line, ',');
			if (line == email)
			{
				data.push_back(email);

				for (int i = 0; i < 17; i++) {
					getline(file, line, ',');
					data.push_back(line);
				}
				break;
			}
			else
				getline(file, line, '\n');
		}
	}
	else if (fileName == "RecipientData.txt") {
		while (file.good()) {
			getline(file, line, ',');
			if (email == line) {
				data.push_back(email);
				for (int i = 1; i < 9; i++) {
					getline(file, line, ',');
					data.push_back(line);
				}
			}
			else
				getline(file, line, '\n');
		}
	}
	file.close();
	return data;
}
