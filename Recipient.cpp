#include "Recipient.h"
#include <fstream>
#include <sstream>
using namespace std;

Recipient::Recipient() {
	IDcounter = getIDcounter();
}
Recipient::Recipient(string email, string password, string id, int age, char gender, string name, string bloodType, string hospital, string DoctorOfTheCase)
{
	this->email = email;
	for (char i : password)
		this->password.push_back(i);
	this->ID = id;
	this->age = age;
	this->gender = gender;
	this->name = name;
	this->blood.setType(bloodType);
	this->hospital = hospital;
	this->DoctorOfTheCase = DoctorOfTheCase;
}
void Recipient::setData()
{
	User::setData();
	cout << "\n\t\t\t Enter Hospital name: " << endl;
	cout << " \t\t\t ";
	cin.ignore();
	getline(cin, hospital);
	cout << "\n\t\t\t Doctor of the case: " << endl;
	cout << " \t\t\t ";
	cin.ignore();
	getline(cin, DoctorOfTheCase);
}

Recipient Recipient::setData(vector<string> arr)
{
	string x = arr[3];
	stringstream str(x);
	int age = 0;
	str >> age;//convert string to int 
	Recipient r(arr[0], arr[1], arr[2], age, arr[4][0], arr[5], arr[6],arr[7],arr[8]);
	return r;
}

vector<string> Recipient::getRecipientData(string email)
{
	return User::getData(email, "RecipientData.txt");
}

void Recipient::signup()
{
	Recipient::setData();
	unordered_map<string, string>check=Recipient::login();
	if (!check.count(email)) {
		IDcounter++;
		ID.append(to_string(IDcounter));
		ofstream file("RecipientData.txt", ios::app);

		file << email << ',';
		for (char i : password)
			file << i;
		file << ',' << ID << ',' << age << ',' << gender << ',' << name << ',' << blood.getType() << ',' << hospital << ',' << DoctorOfTheCase << '\n';
		file.close();
		cout << "\n\t\t\tyour data successfully added\n\t\t\tpress any key to continue";
		_getch();
		system("CLS");
	}
	else
		cout << "\t\t\tthis email is already in use\n\t\t\tyou may try to login\n";
	
}

unordered_map<string, string> Recipient::login()
{
	return User::login("RecipientData.txt");
}

void Recipient::updateData(string DataToUpdate, string itsvalue)
{
	User::updateData(DataToUpdate, itsvalue, "RecipientData.txt");
}

bool Recipient::searchForAvailabilityOfBlood(string bloodType)
{
	for (int i=0;i<bloodType.length();i++)
		bloodType[i] = toupper(bloodType[i]);
	string fileName = bloodType;
	
	fileName.append(".txt");
	string data;
	int count = 0;
	ifstream file(fileName);
	if (file.good()) {
		getline(file, data, '\n');
		stringstream s(data);
		
		s >> count;
		file.close();
	}
	return (count>=1);
}

void Recipient::search(string bloodType)
{
		vector<string> Data;
		size_t found;
		for (int i = 0; i < bloodType.length(); i++)
			bloodType[i] = toupper(bloodType[i]);
		ifstream file("DonorData.txt");
		string line;
		while (file.good()) {
			getline(file, line, ',');
			Data.push_back(line);// 0 - 14 (first Donor) , 15 - 28 (second Donor) , ...
		}//email,password,share,ID,phone,age,gender,name,bloodType decise(6)\n -> new line
		for (int i = 2; i < Data.size(); i += 15) {
			if (Data[i] == "1" && Data[i + 6] == bloodType)
				cout << "\t\t\tID: " << Data[i + 1] << '\t' << "phone: " << Data[i + 2] << '\t' << "Name: " << Data[i + 5] << '\n';
		}
}

vector<string> Recipient::findBloodData(string bloodType)
{
	vector <string>data;
	if (searchForAvailabilityOfBlood(bloodType)) {
		string fileName = bloodType;
		string line;
		for (char i : fileName)
			i = toupper(i);
		fileName.append(".txt");
		ifstream file(fileName);

		while (file.good()) {
			getline(file, line, '\n');
			data.push_back(line);
		}
		cout << "\t\tQuantity of " << bloodType << " here is: " << data[0]<<'\n';
		for (int i = 1; i < data.size(); i++) {
			cout << "\t\t\t" << data[i]<<'\n';
		}
		file.close();
	}
	else
		cout << "\t\t\tSorry we dont have any " << bloodType << " blood\n";
	return data;
}

vector<string> Recipient::findBloodData(string bloodType, int quantity)
{
	vector <string>data;
	if (searchForAvailabilityOfBlood(bloodType)) {
		string fileName = bloodType;
		string line;
		for (char i : fileName)
			i = toupper(i);
		fileName.append(".txt");
		ifstream file(fileName);

		while (file.good()) {
			getline(file, line, '\n');
			if(!line.empty())
				data.push_back(line);
		}
		cout << "\t\tQuantity of " << bloodType << " here is: " << data[0] << '\n';
		for (int i = 1; i < data.size()&&i<=quantity; i++) {
			cout << "\t\t\t" << data[i] << '\n';
		}
		file.close();
	}
	else
		cout << "\t\t\tSorry we dont have any " << bloodType << " blood\n";
	return data;
}

void Recipient::findBloodData()
{
		findBloodData("A+");	
		findBloodData("A-");
		findBloodData("B+");
		findBloodData("B-");
		findBloodData("AB+");
		findBloodData("AB-");
		findBloodData("O+");
		findBloodData("O-");
}

void Recipient::transfareBlood(string bloodType,int QuantityAvilable)
{
	string fileName = bloodType;
	for (int i = 0; i < fileName.length(); i++)
		fileName[i] = toupper(fileName[i]);
	fileName.append(".txt");
	fstream file(fileName, ios::in);
	fstream temp("temp.txt", ios::out);
	string line;
	getline(file, line, '\n');//counter of this blood Type
	stringstream str(line);
	int oldCounter;
	str >> oldCounter;
	int newCounter = oldCounter - QuantityAvilable;
	temp << newCounter << '\n';
	for (int i = 0; i < QuantityAvilable && file.good(); i++)//hyt3mlhom transfare (ytn2lo mn al file bta3 al blood)
		getline(file, line, '\n');
	while (file.good()) {
		getline(file, line, '\n');
		temp << line << '\n';
	}

	file.close();
	temp.close();
	remove(fileName.c_str());
	rename("temp.txt", fileName.c_str());
}

void Recipient::requestBloodType(string bloodType, int quantity) 
{
	for (int i = 0; i < bloodType.length(); i++)
		bloodType[i] = toupper(bloodType[i]);
	vector <string>data;
	if (searchForAvailabilityOfBlood(bloodType)) {
		bool confirm;
		cout << "\t\t\tDo you want to recive the blood in " << hospital<<" 1-yes\t2-No";
		cin >> confirm;
		if (!confirm) {
			cout << "\t\t\tenter hospital name: ";
			string otherHospital;
			cin >> otherHospital;
		}
		data = findBloodData(bloodType,quantity);
		if (data.size() < quantity) {
			cout << "\t\t\tsorry we dont have this quantity of " << bloodType << " blood\n\t\t\tyou may ask:\n";
			quantity = data.size();
			search(bloodType);
			if (!data.empty())
				transfareBlood(bloodType, data.size());
		}
		transfareBlood(bloodType, quantity);
	}
}

void Recipient::deleteAcc()
{
	User::updateData("delete", "", "RecipientData.txt");
}
