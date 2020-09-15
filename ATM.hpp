//
//  ATM.hpp
//  ATM
//
//  Created by Hejin Liu on 9/11/20.
//  Copyright © 2020 Hejin Liu. All rights reserved.
//

#ifndef ATM_hpp
#define ATM_hpp

# include <string>
# include <map>
# include <fstream>
# include <iostream>
# include <sstream>
class account
{
private:
    std::string name;
    int balance;
public:
    account(std::string aName, int aBalance);
    std::string getName();
    int getBalance();
    void seeBalance();
    void deposit();
    void withdraw();
};

class user
{
private:
    std::string cardNum;
    std::string PIN;
    std::map<std::string, account*> accounts;
    int accNum;
public:
    user(std::string & aCardNum, std::string & aPIN, int aNum);
    void loadAccounts(std::ifstream & data);
    bool checkPIN(std::string aPIN);
    void newAccount();
    void selectAccount();
    void saveAccounts(std::ofstream & data);
    ~user();
};

class ATM
{
private:
    std::map<std::string, user*> users;
    int userNum;
public:
    ATM();
    void loadUsers(std::string & fileName);
    void newUser();
    void saveUsers(std::string & fileName);
    void login();
    ~ATM();
};

#endif /* ATM_hpp */
