#pragma once
#include "User.h"
class Donor :
    public User
{
    Date lastDonation;
    bool bloodPressure, thyroidDisease, diabetes, cancer, heartDisorders, hepatitis, otherDisease, shareData;
    string phoneNumber;
    void setData();
public:
    Donor();
    Donor(string email, string password, bool share, string id, string phone, int age, char gender, string name, string bloodType, bool d1, bool d2, bool d3, bool d4, bool d5, bool d6,Date donation);
    void signup();
    unordered_map<string, string> login();
    void donationRequest(string bloodType);
    void updateData(string DataToUpdate, string itsvalue); //DonorData.txt || RecipeantData.txt
    void deleteAcc();
    static vector<string> getDonorData(string email); //htrg3 map(email , all other data in a vector)
    static Donor setData(vector<string>);
    static bool checkDate(Date d, int op);
    ~Donor();
};

