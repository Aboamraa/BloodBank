#define _CRT_SECURE_NO_WARNINGS
#include "Blood.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <time.h>
Blood::Blood()
{  
}
void Blood::setExpireDate()
{
    expireDate.Day = donationDate.Day;
    if ((donationDate.Month + 3) > 12) {
        expireDate.Month = (donationDate.Month + 3) % 12;
        expireDate.Year = donationDate.Year + 1;
    }
    else {
        expireDate.Month = donationDate.Month + 3;
        expireDate.Year = donationDate.Year;
    }
}

void Blood::setDonationDate()
{
    time_t t = time(0);
    tm* now = localtime(&t);
    
    donationDate.Day = now->tm_mday;
    donationDate.Month = now->tm_mon + 1;
    donationDate.Year = now->tm_year+1900;
}

void Blood::setType()
{
    cin >> this->type;
    for (char i : type)
        i = toupper(i);
}

void Blood::setType(string b)
{
    type = b;
}

Date Blood::getExpireDate()
{
    return expireDate;
}

Date Blood::getDonationDate()
{
    return donationDate;
}

string Blood::getType()
{
    return type;
}

int Blood::getCounter_fromFIle(string bloodType)
{
    bloodType.append(".txt");
    ifstream file(bloodType);
    string counter;
    file >> counter;
    stringstream c(counter);
    int count;
    c >> count;
    file.close();
    return count;
}

void Blood::updateBloodData(Blood blood)
{
    string filename = blood.getType();
    filename.append(".txt");
    fstream file(filename, ios::in);
    fstream temp("temp.txt", ios::out);
    temp << bloodCounter << '\n';
    string line;
    getline(file, line, '\n');
    while (file.good()) {
        getline(file, line, '\n');
        temp << line << '\n';
    }//al data al gdeda kolha gwa temp 5las
    file.close();
    temp.close();
    remove(filename.c_str());
    rename("temp.txt", filename.c_str());
}

void Blood::setBloodData_inFile(Blood blood)//Donation and expire dates//
{
    string bloodType = blood.getType();
    for (char i : bloodType)
        i = toupper(i);
    bloodType.append(".txt");
    ofstream file(bloodType,ios::app);
    file << blood.getDonationDate().Day << '/' << blood.getDonationDate().Month << '/' << blood.getDonationDate().Year << '\t'
         << blood.getExpireDate().Day<<'/'<< blood.getExpireDate().Month << '/' << blood.getExpireDate().Year << '\n';
    file.close();
}

Blood::~Blood()
{
}
