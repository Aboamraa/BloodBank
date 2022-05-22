#define _CRT_SECURE_NO_WARNINGS
#include "Donor.h"
#include <fstream>
#include <sstream>
#include "Admin.h"

Donor::Donor() :User() {

	IDcounter = getIDcounter();
	bloodPressure = thyroidDisease = diabetes = cancer = heartDisorders = hepatitis = otherDisease = false;
}
Donor::Donor(string email, string password, bool share,string id,string phone ,int age, char gender, string name, string bloodType, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6,Date donation)
{
		this->email = email;
		for (char i : password)
			this->password.push_back(i);
		this->shareData = share;
		this->ID = id;
		this->phoneNumber = phone;
		this->age = age;
		this->gender = gender;
		this->name = name;
		this->blood.setType(bloodType);
		bloodPressure = d1;
		thyroidDisease = d2; 
		diabetes = d3; 
		cancer = d4; 
		heartDisorders = d5; 
		hepatitis = d6; 
		lastDonation = donation;
}

void Donor::signup()
{
	Donor::setData();
	unordered_map<string, string>check = Donor::login();
	if (!check.count(email)) {
		IDcounter++;
		ID.append(to_string(IDcounter));

		ofstream Datafile("DonorData.txt", ios::app);

		Datafile << email << ',';
		for (char i : password)
			Datafile << i;
		if (Admin::checkAge(age) && Admin::checkDisease(bloodPressure) && Admin::checkDisease(thyroidDisease) && Admin::checkDisease(diabetes) && Admin::checkDisease(cancer) && Admin::checkDisease(heartDisorders) && Admin::checkDisease(hepatitis)) {
			cout << "\nyour data successfully added\n\t\t\tpress any key to continue";
			Datafile << ',' << shareData << ',' << ID << ',' << phoneNumber << ',' << age << ',' << gender << ',' << name << ',' << blood.getType() << ',';//lesa fe t3del lazm yt3ml f al disease
			Datafile << " blood pressure: " << bloodPressure << ", thyroid disease: " << thyroidDisease << ", diabetes: " << diabetes << ", cancer: " << cancer << ", heart disorders: " << heartDisorders << ", hepatitis: " << hepatitis << ',' << lastDonation.Day << ',' << lastDonation.Month << ',' << lastDonation.Year << ",\n";
		}
		else
			cout << "\t\t\tinvalid Data can't signup\n\t\t\tpress any key to continue";
		_getche();
		system("CLS");
		Datafile.close();
	}
	else
		cout << "\t\t\tthis email is already in use\n\t\t\tyou may try to login\n";
}

unordered_map<string, string> Donor::login()
{
	return User::login("DonorData.txt");
}

void Donor::donationRequest(string bloodType)
{
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	bool check = false;
	if (now->tm_year + 1900 > lastDonation.Year )
		check = true;
	else if (abs((now->tm_mon + 1) - lastDonation.Month) > 3)
		check = true;
	else {
		cout << "\t\t\tcan't donate now you can donate after " << lastDonation.Day << '/' << (lastDonation.Month + 3) % 12;
		return;
	}
	blood.bloodCounter = blood.getCounter_fromFIle(bloodType);
	cout << "\n\t\t\t Donation Date: ";
	cout << " \t\t\t ";
	blood.setDonationDate();
	cout <<"\t\t\t" << blood.getDonationDate().Day << '/' << blood.getDonationDate().Month << '/' << blood.getDonationDate().Year<<endl;
	cout << "\n\t\t\t Expiration Date: ";
	cout << " \t\t\t ";
	blood.setExpireDate();
	cout << "\t\t\t" << blood.getExpireDate().Day << '/' << blood.getExpireDate().Month << '/' << blood.getExpireDate().Year << endl;
	blood.bloodCounter++;
	blood.setBloodData_inFile(blood);//y7ot al data al gdeda
	blood.updateBloodData(blood); // y3ml file gded 34an y7ot al counter al gded
	cout << "\t\t\tDonation sucsessed\n";
	lastDonation.Day = now->tm_mday;
	lastDonation.Month = now->tm_mon + 1;
	lastDonation.Year = now->tm_year + 1900;
	string day=to_string(now->tm_mday),month=to_string((now->tm_mon + 1)),year=to_string((now->tm_year + 1900)),d;
	d = d + day + "," + month + "," + year +",";
	updateData("lastDonationDate", d);
}

void Donor::updateData(string DataToUpdate, string itsvalue)
{
	User::updateData(DataToUpdate, itsvalue, "DonorData.txt");
}

void Donor::deleteAcc()
{
	User::updateData("delete", "", "DonorData.txt");
}

vector<string> Donor::getDonorData(string email)//momkn tt7t f al User w t5adem 3le al Donor w al recipient
{
	return User::getData(email,"DonorData.txt");
}

void Donor::setData()
{
	User::setData();
	while (true)
	{
		cout << "\n\t\t\t Last Dodonation Date:(set them = 0 in case of never donated)\n\t\t\tDay: ";
		cin >> lastDonation.Day;
		if (!checkDate(lastDonation, 1))
			continue;
		cout << "\t\t\tMonth: ";
		cin >> lastDonation.Month;
		if (!checkDate(lastDonation, 2))
			continue;
		cout << "\t\t\tYear: ";
		cin >> lastDonation.Year;
		if (!checkDate(lastDonation, 3))
			continue;
		break;
	}
	cout << "\n\t\t\t Phone number: ";
	cout << " \t\t\t ";
	cin >> phoneNumber;
	cout << "\n\t\t\t Do you suffer from: (1-> yes , 0-> No)" << endl;
	cout << "\n\t\t\t blood pressure disorders: ";
	cout << " \t\t\t ";
	cin >> bloodPressure;
	cout << "\n\t\t\t thyroid disease: ";
	cout << " \t\t\t ";
	cin >> thyroidDisease;
	cout << "\n\t\t\t diabetes: ";
	cout << " \t\t\t ";
	cin >> diabetes;
	cout << "\n\t\t\t cancer: ";
	cout << " \t\t\t ";
	cin >> cancer;
	cout << "\n\t\t\t  heart disorders: ";
	cout << " \t\t\t ";
	cin >> heartDisorders;
	cout << "\n\t\t\t hepatitis: ";
	cout << " \t\t\t";
	cin >> hepatitis;
	cout << "\n\t\t\t Do you accept to share your data when needed: (ID , Phone Number)";
	cout << " \t\t\t ";
	cin >> shareData;
}

Donor Donor::setData(vector<string>arr)
{//email,password,share,ID,phone,age,gender,name,booldType,d[0->6],donationDate
	int age;
	bool disease[6], share;
	
	size_t found;
	if (arr[2] == "0")
		share = false;
	else
		share = true;
	for (int i = 0; i < 6; i++)
	{
		found = arr[i + 9].find('0');
		if (found!=string::npos)
			disease[i] = false;
		else
			disease[i] = true;
	}
	sscanf(arr[5].c_str(),"%d",&age);//convert string to int
	Date date;
	sscanf(arr[15].c_str(), "%d", &date.Day);
	sscanf(arr[16].c_str(), "%d", &date.Month);
	sscanf(arr[17].c_str(), "%d", &date.Year);

	Donor d(arr[0], arr[1],share ,arr[3],arr[4], age, arr[6][0], arr[7],arr[8], disease[0], disease[1], disease[2], disease[3], disease[4], disease[5],date);
	return d;
}

bool Donor::checkDate(Date d, int op)
{
	switch (op)
	{
	case 1:{
		if (d.Day > 31 || d.Day < 0) {
			cout << "Wrong Day data\n";
			return false;
		}
		return true;
	}
	case 2: {
		if (d.Month > 12 || d.Month < 0) {
			cout << "wrong Month data\n";
			return false;
		}
		return true;
	}
	case 3: {
		time_t t = std::time(0);   // get time now
		tm* now = std::localtime(&t);
		if (d.Year > (now->tm_year + 1900)) {
			cout << "Wrong Year data\n";
			return false;
		}
		return true;
	}
	default:
		return false;
	}
}

Donor::~Donor()
{}
