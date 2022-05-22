#pragma once
#include "User.h"
class Recipient :
    public User
{
    string hospital, DoctorOfTheCase;
public:
    Recipient();
    Recipient(string email, string password, string id, int age, char gender, string name, string bloodType, string hospital, string doctorOfTheCase);
    void setData();
    static Recipient setData(vector<string>arr);
    static vector <string>getRecipientData(string email);
    void signup();
    unordered_map<string, string> login();
    void updateData(string DataToUpdate, string itsvalue);

    bool searchForAvailabilityOfBlood(string bloodType);
    void search(string bloodType);
    vector<string> findBloodData(string bloodType);
    vector<string> findBloodData(string bloodType,int quantity);
    void findBloodData();
    void transfareBlood(string bloodType,int QuantityAvilable);
    void requestBloodType(string bloodType, int quantity);
    void deleteAcc();
};

