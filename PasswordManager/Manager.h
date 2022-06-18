#pragma once
#include "Password.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <ctime>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

class Manager{
    private:
        vector <Password> passwords;
        vector <Password> original_p;
        set <string> categories;
        int currSize;
        int totalSize;
        string filename;
        string secretKey,originalKey;
        string lastAttempt;
        string thisAttempt;
    public:
        /**
         * @brief Construct a new Manager object
         * 
         * @param size 
         * @param filename 
         * @param secretKey 
         */
        Manager(int size, string filename, string secretKey){
            totalSize=size;
            currSize=0;
            this->filename=filename;
            this->secretKey=secretKey;
            this->originalKey="Strong Password!";
            categories.insert("social");
            time_t end_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
            thisAttempt=ctime(&end_time);
        }

        /**
         * @brief Get the Last Attempt data
         * 
         * @return string 
         */
        string getLastAttempt(){
            return lastAttempt;
        }

        /**
         * @brief Read passwords from a file 
         * 
         */
        void readPasswords(){
            ifstream in;
            in.open(this->filename.c_str(),ios::in);
            if(!in.is_open()){
                cout << "Couldn't find file!\n";
                return;
            } 
            Password pass;
            in >> lastAttempt;
            for(int i=0;i<lastAttempt.length();i++){
                if(lastAttempt[i]=='#'){
                    lastAttempt[i]=' ';
                }
                else{
                    lastAttempt[i]=lastAttempt[i]-5;
                }
            }
            while(true){
                in >> pass;
                if(in.eof())break;
                passwords.push_back(pass);
                original_p.push_back(pass);
                currSize++;
                pass.decryptData(originalKey);
                categories.insert(pass.getCategory());
                // cout << original_p[currSize - 1] << " " << passwords[currSize-1];
            }
            // currSize--;
        }

        /**
         * @brief Write Passwords to the file
         * 
         */
        void writePasswords(){
            for(int i=0;i<thisAttempt.length();i++){
                if(thisAttempt[i]==' '){
                    thisAttempt[i]='#';
                }
                else{
                    thisAttempt[i]=thisAttempt[i]+5;
                }
            }
            ofstream out;
            out.open(this->filename.c_str(),ios::out|ios::binary);
            out << thisAttempt << "\n";
            for(int i=0;i<currSize;i++){
                out << original_p[i];
            }
        }

        /**
         * @brief Checks if the given category exists in the defined categories
         * 
         * @param cat 
         * @return true 
         * @return false 
         */
        bool checkCategory(string cat){
            int i=1;
            if(categories.find(cat)==categories.end()){
                cout << "Category not found! Enter the category from the follwoing categories or add a new one!\n";
                for(auto it = categories.begin() ; it != categories.end() ; it++){
                    cout<< i++ << ". " << *it<< " ";
                }
                cout << "\n";
                return false;
            }
            return true;
        }

        /**
         * @brief Create a Password for the user automatically
         * 
         * @return string 
         */
        string createPassword(){
            cout << "Enter the length  of characters: ";
            int length;
            cin >> length;
            bool UL_Case,S_Char;
            string ans;
            cout << "Should it contain both uppercase and lowercase alphabets?(y/n): ";
            cin >> ans;
            UL_Case=(ans=="y");
            cout << "Should it contain special characters?(y/n): ";
            cin >> ans;
            S_Char=(ans=="y");
            string dataSet="abcdefghijklmnopqrstuvwxyz";
            if(UL_Case)dataSet+="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
            if(S_Char)dataSet+=",./<>?;':-=_+!@#$%^&*";
            string password="";
            for(int i=0;i<length;i++){
                int no=rand()%dataSet.length()-1;
                password+=dataSet[no];
            }
            cout << "Your Password is: " << password << "\n";
            return password;
        }

        /**
         * @brief Cheecks the given user password for its security level and comment on it
         * 
         * @param password 
         * @return true 
         * @return false 
         */
        bool commentPassword(string password){
            string l_alph="abcdefghijklmnopqrstuvwxyz";
            string u_alph="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string symb=",./<>?;':-=_+!@#$%^&*";
            bool l_case=false,u_case=false,sym=false;
            for(int i=0;i<password.length();i++){
                if(l_alph.find(password[i])!=-1)l_case=true;
                if(u_alph.find(password[i])!=-1)u_case=true;
                if(symb.find(password[i])!=-1)sym=true;
            }
            if(password.length()<6){
                cout << "Password length is too small. Should've been more than 6 characters\n";
                return false;
            }
            else if(!l_case){
                cout << "There should be 1 lowercase alphabet.\n";
                return false;
            }
            else if(!u_case){
                cout << "There should be 1 uppercase alphabet.\n";
                return false;
            }
            else if(!sym){
                cout << "There should be 1 symbol.\n";
                return false;
            }
            else{
                cout << "Looks Strong enough..\n";
                return true;
            }
        }

        /**
         * @brief Add a new password to the current data Set
         * 
         */
        void addPassword(){
            string name,password,category,login,url;
            cout << "\nEnter the name of the entry. e.g. Google, Facebook etc: ";
            cin >> name;
            string input;
            cout << "Do you want to create an automatic password?:(y/n) ";
            cin >> input;
            if(input=="n"){
                while(true){
                    cout << "Enter the password: ";
                    cin >> password;
                    if(commentPassword(password))break;
                }
            }
            else{
                password=createPassword();
            }
            cout << "Enter the category: ";
            cin >> category;
            if(!checkCategory(category)){
                return;
            }
            cout << "Enter the URL:(Enter s if no URL) ";
            cin >> url;
            if(url=="s"){
                url="";
                login="";
            }
            else {
            cout << "Enter the Login:(Enter s if no Login) ";
            cin >> login; 
            if (login=="s"){
                login="";
            }
            }
            Password newP(name,password,category,url,login);
            newP.encryptData(originalKey);
            original_p.push_back(newP);
            newP.decryptData(secretKey);
            passwords.push_back(newP);
            currSize++;
        }

        /**
         * @brief Edit an already saved password 
         * 
         */
        void editPassword(){
            string name,password,category,login,url;
            cout << "Enter the name of password you want to edit: ";
            string pass;
            cin >> pass;
            int ind=-1;
            for(int i=0;i<original_p.size();i++){
                if (passwords[i].getName()==pass){
                    ind=i;
                    break;
                }
            }
            if(ind!=-1){
                cout << "\nEnter new details\nEnter the name of the entry. e.g. Google, Facebook etc: ";
                cin >> name;
                cout << "Enter the password: ";
                cin >> password;
                cout << "Enter the category: ";
                cin >> category;
                if(!checkCategory(category)){
                    return;
                }
                cout << "Enter the URL:(Enter s if no URL) ";
                cin >> url;
                if(url=="s"){
                    url="";
                    login="";
                }
                else {
                cout << "Enter the Login:(Enter s if no Login) ";
                cin >> login; 
                if (login=="s"){
                    login="";
                }
                }
                Password newP(name,password,category,url,login);
                newP.encryptData(originalKey);
                original_p[ind]=newP;
                newP.decryptData(secretKey);
                passwords[ind]=newP;
            }
            else{
                cout << "Entry not found!";
            }
        }

        /**
         * @brief Search for the password depending on a given criteria
         * 
         */
        void searchPassword(){
            cout << "Enter the name of password you want to search: ";
            string pass;
            cin >> pass;
            int ind=-1;
            for(int i=0;i<original_p.size();i++){
                if (passwords[i].getName()==pass){
                    ind=i;
                    break;
                }
            }
            if(ind==-1){
                cout << "No password found!\n";
                return;
            }
            else {
                cout << left << setw(15)<< "Name"<< setw(20) << "Password"<< setw(15) << "Category"<< setw(15) << "URL"<< setw(15) << "Login";
                passwords[ind].printDetails();
            }
        }

        /**
         * @brief Show all passwords
         * 
         */
        void showPasswords(){
            // cout << currSize << " " << original_p.size() << " " << passwords.size();
            if(currSize==0){
                cout << "No Passwords found!\n";
                return;
            }
            cout << left << setw(15)<< "Name"<< setw(20) << "Password"<< setw(15) << "Category"<< setw(15) << "URL"<< setw(15) << "Login";
            for(int i=0;i<currSize;i++){
                passwords[i].printDetails();
            }
        }

        /**
         * @brief Remove a password from the dataSet
         * 
         */
        void removePassword(){
            cout << "Enter the name of password you want to remove: ";
            string pass;
            cin >> pass;
            int ind=-1;
            for(int i=0;i<original_p.size();i++){
                if (passwords[i].getName()==pass){
                    ind=i;
                    break;
                }
            }
            if(ind==-1){
                cout << "No password found!\n";
                return;
            }
            else {
                for(int i=ind;i<passwords.size()-1;i++){
                    passwords[i]=passwords[i+1];
                    original_p[i]=original_p[i+1];
                }
                cout << "Entry deleted!\n";
                currSize--;
            }
        }

        /**
         * @brief Add a new category to the system
         * 
         */
        void addCategory(){
            cout << "Enter Category Name: ";
            string cat;
            cin >> cat;
            if(categories.find(cat)!=categories.end()){
                cout << "Category already exists!\n";
                return;
            }
            else{
                cout << "Category added!\n";
                categories.insert(cat);
            }
        }

        /**
         * @brief Remove a category and all its related passwords from the system
         * 
         */
        void removeCategory(){
            cout << "Enter the Category you want to remove: ";
            string cat;
            cin >> cat;
            if(categories.find(cat)!=categories.end()){
                categories.erase(categories.find(cat));
                for (int i=0;i<passwords.size();i++){
                    if(passwords[i].getCategory()==cat){
                        for(int j=i;j<passwords.size()-1;j++){
                        passwords[j]=passwords[j+1];
                        original_p[j]=original_p[j+1];
                        }
                        currSize--; 
                        i--;
                    }
                }
                return;
            }
            else{
                cout << "Category not found!\n";
            }
        }

        /**
         * @brief Sort passwords according to name and category
         * 
         */
        void sortPasswords(){
            for(int i=0;i<passwords.size();i++){
                for (int j=0;j<passwords.size();j++){
                    if(passwords[i].getName() <= passwords[j].getName() && passwords[i].getCategory() <= passwords[j].getCategory()){
                        Password temp=passwords[i];
                        passwords[i]=passwords[j];
                        passwords[j]=temp;
                        temp=original_p[i];
                        original_p[i]=original_p[j];
                        original_p[j]=temp;
                    }
                }
            }
            showPasswords();
        }

        /**
         * @brief Decrypts passwords based on the secret key
         * 
         */
        void decryptPasswords(){
            for (int i=0;i<currSize;i++){
                passwords[i].decryptData(secretKey);
            }
        }
};
