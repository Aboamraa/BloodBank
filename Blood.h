#pragma once
#include <string>
using namespace std;
struct Date {
	int Day, Month, Year;
};
class Blood
{
	Date expireDate, donationDate;
	string type;
	
public:
	int bloodCounter = 0;
	Blood();

	void setExpireDate();
	void setDonationDate();
	void setType();
	void setType(string);

	Date getExpireDate();
	Date getDonationDate();
	string getType();

	int getCounter_fromFIle(string bloodType);// ageb al counter f awl al brnamg
	void updateBloodData(Blood blood); // f nos al brnamg ab3t al data kolha
	void setBloodData_inFile(Blood blood); // ab3t al expire w al donation dates f a5r al brnamg

	~Blood();
};