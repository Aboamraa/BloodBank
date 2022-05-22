#define _CRT_SECURE_NO_WARNINGS
#include "Admin.h"
#include "Blood.h"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

bool Admin::checkAge(int age)
{
	return (age <= 60 || age >= 17);
}

bool Admin::checkDate(Date date)
{
	time_t t1 = time(0);   // get time now
	tm* now = localtime(&t1);

	return (now->tm_year > date.Year + 1900 || (now->tm_mon + 1) - date.Month >= 3);;
}

bool Admin::checkDisease(bool disease)
{
	return !disease;
}

void Admin::updateBlood(string fileName)
{
	stringstream str;
	int counter;
	string line;
	Date donate, expire;
	vector<Date>data;
	time_t t = std::time(0);   // get time now
	tm* now = std::localtime(&t);

	fstream file(fileName, ios::in);
	fstream temp("tmp.txt", ios::out);
	getline(file, line, '\n');
	sscanf(line.c_str(), "%d", &counter);
	while (file.good()) {
		getline(file, line, '/');
		if (line.empty())
			continue;
		sscanf(line.c_str(), "%d", &donate.Day);
		getline(file, line, '/');
		sscanf(line.c_str(), "%d", &donate.Month);
		getline(file, line, '\t');//
		sscanf(line.c_str(), "%d", &donate.Year);
		//getline(file, line, '\t');
		getline(file, line, '/');
		sscanf(line.c_str(), "%d", &expire.Day);
		getline(file, line, '/');
		sscanf(line.c_str(), "%d", &expire.Month);
		getline(file, line, '\n');
		sscanf(line.c_str(), "%d", &expire.Year);

		if ((expire.Month - (now->tm_mon+1)) % 12 > 0 || ((((now->tm_mon+1) - expire.Month) % 12 == 0) && (expire.Day - now->tm_mday) > 0)) {
			//temp << donate.Day << '/' << donate.Month << '/' << donate.Year << '\t' << expire.Day << '/' << expire.Month << '/' << expire.Year << '\n';
			data.push_back(donate);
			data.push_back(expire);
		}
		else if(counter>0)
			counter--;
	}
	temp << counter<<'\n';
	for (int i = 0; i < data.size();i+=2) {
		temp << data[i].Day << '/' << data[i].Month << '/' << data[i].Year << '\t' << data[i+1].Day << '/' << data[i+1].Month << '/' << data[i+1].Year << '\n';
	}
	file.close();
	temp.close();
	remove(fileName.c_str());
	rename("tmp.txt", fileName.c_str());
}
