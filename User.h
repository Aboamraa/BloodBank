#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "Blood.h"
#include <unordered_map>
using namespace std;
class User
{
protected:
	static int IDcounter;
	string ID = "20201700", email, name, password;
	char gender = ' ';
	Blood blood;
	int age = 0;

	virtual void setData();

	virtual unordered_map<string, string> login(string whoWillLogin);
	void updateData(string DataToUpdate, string itsvalue, string fileName); //DonorData.txt || RecipeantData.txt
	static vector<string>getData(string email, string fileName);
	
	static int getIDcounter();
public:
	Blood getBlood();
	static void sendIDCounter();

};

