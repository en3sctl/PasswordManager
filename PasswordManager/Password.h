#pragma once
#include <iostream>
using namespace std;

class Password{
    private:
        string name;
        string password;
        string category;
        string URL;
        string Login;
    public:      
        Password();
        Password(string ,string ,string, string, string );
        void setName(string name);
        void setPassword(string password);
        void setCategory(string category);
        void setSecretKey(string key);
        string getName();
        string getCategory();
        char shift(char ch,int key,int rounds);
        char unshift(char ch,int key,int rounds);
        string encrypt(string inputP,string password);
        string decrypt(string inputP,string password);
        void encryptData(string secretKey);
        void decryptData(string secretKey);
        void showData();
        void printDetails();
        friend ostream& operator <<(ostream&, Password&);
        friend istream& operator >>(istream&, Password&);
};  