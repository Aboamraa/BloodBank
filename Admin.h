#pragma once
#include "Blood.h"
#include <String>
using namespace std;
class Admin
{

public:
	static bool checkAge(int age);
	static bool checkDate(Date date);
	static bool checkDisease(bool disease);
	static void updateBlood(string fileName);
};

