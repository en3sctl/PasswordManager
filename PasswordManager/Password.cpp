#include "Password.h"
#include <iostream>
#include <iomanip>
using namespace std;


/**
 * @brief Construct a new Password object
 * 
 */
Password::Password(){}

/**
 * @brief Construct a new Password object
 * 
 * @param name 
 * @param password 
 * @param category 
 * @param URL 
 * @param Login 
 * @return none
 */
Password::Password(string name,string password,string category,string URL="",string Login=""){
    this->setName(name);
    this->setPassword(password);
    this->setCategory(category);
	this->URL=URL;
	this->Login=Login;
}

/**
 * @brief setter function for name variable
 * @param name 
 * @return void
 */
void Password::setName(string name){
    this->name=name;
}

/**
 * @brief setter function for password variable
 * 
 * @param password 
 * @return none
 */
void Password::setPassword(string password){
    this->password=password;
}

/**
 * @brief setter function for category variable
 * 
 * @param category 
 * @return none
 */
void Password::setCategory(string category){
    this->category=category;
}

/**
 * @brief returns value of name variable
 * 
 * @return string 
 * @param none
 */
string Password::getName(){
	return this->name;
}

/**
 * @brief returns value of category variable
 * @param none
 * @return string 
 */
string Password::getCategory(){
	return this->category;
}

/**
 * @brief shifts a character key places and rounds no of times
 * 
 * @param ch 
 * @param key 
 * @param rounds 
 * @return char 
 */
char Password::shift(char ch,int key,int rounds){
	for(int i=0;i<rounds;i++){
		ch=ch+key;
	}
	return ch;
}

/**
 * @brief unshifts a character key no of places and rounds no of times
 * 
 * @param ch 
 * @param key 
 * @param rounds 
 * @return char 
 */
char Password::unshift(char ch,int key,int rounds){
	for(int i=0;i<rounds;i++){
		ch=ch-key;
	}
	return ch;
}

/**
 * @brief encrypt a given string
 * 
 * @param inputP 
 * @param password 
 * @return string 
 */
string Password::encrypt(string inputP,string password){
    int total=0;
	if (password=="")return "";
	for (unsigned int i=0;i<inputP.length()-1;i++){
		total+=int(inputP[i]);
	}
	int key=total%26;
	int saltingRounds=key%5+1;
	for (unsigned int i=0;i<password.length()-1;i++){
		password[i]=shift(password[i],key,saltingRounds);
	}
	// cout << "Encrypted " << password << "\n";
	return password;
}

/**
 * @brief decrypt a given string
 * 
 * @param inputP 
 * @param password 
 * @return string 
 */
string Password::decrypt(string inputP,string password){
	int total=0;
	if(password=="")return "";
	for (unsigned int i=0;i<inputP.length()-1;i++){
		total+=int(inputP[i]);
	}
	int key=total%26;
	int saltingRounds=key%5+1;
	for (unsigned int i=0;i<password.length()-1;i++){
		password[i]=unshift(password[i],key,saltingRounds);
	}
	return password;
}

/**
 * @brief encrypts all data of the current object
 * 
 * @param secretKey 
 */
void Password::encryptData(string secretKey){
    name=encrypt(secretKey,name);
    password=encrypt(secretKey,password);
    category=encrypt(secretKey,category);
	URL=encrypt(secretKey,URL);
	Login=encrypt(secretKey,Login);
}

/**
 * @brief decrypts all data of the current object
 * 
 * @param secretKey 
 */
void Password::decryptData(string secretKey){
    name=decrypt(secretKey,name);
    password=decrypt(secretKey,password);
    category=decrypt(secretKey,category);
	URL=decrypt(secretKey,URL);
	Login=decrypt(secretKey,Login);
}

/**
 * @brief rprints data of current object on screen
 * 
 */
void Password::showData(){
    cout << name << "\t" << password << "\t" << category << "\n";
} 

/**
 * @brief Overloaded << operator for Password class
 * 
 * @param out 
 * @param p 
 * @return ostream& 
 */
ostream& operator<<(ostream &out, Password &p){
		out << p.name << "\t" << p.password << "\t" << p.category << " " << p.URL << " " << p.Login << " " << "END ";
		return out;
	}

/**
 * @brief Overloaded >> operator for Password class
 * 
 * @param in 
 * @param p 
 * @return istream& 
 */
istream& operator >>(istream &in, Password &p){
		in >>  p.name >> p.password >> p.category;
		in >> p.URL; 
		if(p.URL=="END"){
			// cout << p.URL << " fd";
			p.URL="";
			p.Login="";
			return in;
		} 
		in >> p.Login;
		if(p.Login=="END"){
			// cout << p.Login << " fd";
			p.Login="";
			return in;
		}
		string end;
		in >> end;
	} 
/**
 * @brief print the details of current object on screen
 * 
 */
void Password::printDetails(){
	if(URL=="")URL="-";
	if(Login=="")Login="-";
	cout << "\n" << left << setw(15)<< name<< setw(20) << password << setw(15) << category << setw(15) << URL << setw(15) << Login;
	if(URL=="-")URL="";
	if(Login=="-")Login="";
}