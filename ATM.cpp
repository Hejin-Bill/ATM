//
//  ATM.cpp
//  ATM
//
//  Created by Hejin Liu on 9/11/20.
//  Copyright © 2020 Hejin Liu. All rights reserved.
//

#include "ATM.hpp"
#include <vector>

account::account(std::string aName, int aBalance)
{
    name = aName;
    balance = aBalance;
}

std::string account::getName()
{   return name;}

int account::getBalance()
{   return balance;}

void account::seeBalance()
{
    std::cout<<"Balance: $"<<balance<<std::endl;
}

void account::deposit()
{
    int dep = 0;
    std::cout<<"Please put your deposit inside the box (or enter 0 to cancle):"<<std::endl;
    std::cin>>dep;
    balance += dep;
    std::cout<<"You just deposited $"<< dep<<"."<<std::endl;
}

void account::withdraw()
{
    int wit = 0;
    std::cout<<"Please enter the amount to withdraw (or enter 0 to cancle): "<<std::endl;
    std::cin>>wit;
    while(wit > balance || wit < 0)
    {
        std::cout<<"Invalid, please make sure you entered a positive number and you have enough balance. Your balance is "<< balance<<". Or you can enter 0 to cancle."<<std::endl;
        std::cin>>wit;
    }
    balance -= wit;
    std::cout<<"Here is your $"<< wit<<"."<<std::endl;
}

user::user(std::string & aCardNum, std::string & aPIN, int aNum)
{
    cardNum = aCardNum;
    PIN = aPIN;
    accNum = aNum;
}

void user::loadAccounts(std::ifstream & data)
{
    std::string accName;
    int accBalance;
    for(int i = 0;i<accNum;i++)
    {
        data >> accName >> accBalance;
        accounts[accName] = new account(accName, accBalance);
    }
}

bool user::checkPIN(std::string aPIN)
{   return PIN == aPIN;}

void user::newAccount()
{
    std::string newName;
    std::cout<<"Please input your new account name:"<<std::endl;
    std::cin >>newName;
    std::cout<<"Your new account "<< newName <<" has been created."<<std::endl;
    accounts[newName] = new account(newName, 0);
    accNum += 1;
}

void user::selectAccount()
{
    while(1)
    {
        std::vector<std::string> accNames;
        std::cout<<"Please select one account:"<<std::endl;
        int i = 0;
        for (auto & x: accounts)
        {
            std::cout<<i+1<<". "<<x.first<<std::endl;
            accNames.push_back(x.first);
            i += 1;
        }
        i += 1;
        std::cout<<i<<". Cancel"<<std::endl;
        int option = 0;
        std::cin>>option;
        while(option > i || option <1)
        {
            std::cout<<"Please select a valid account."<<std::endl;
            std::cin>>option;
        }
        if (option == i)
            break;
        while(1)
        {
            std::cout<<"What do you want to do with this account?"<<std::endl;
            std::cout   <<"1. Check Balance\n"
                        <<"2. Deposit\n"
                        <<"3. Withdraw\n"
                        << "4. Cancel"<<std::endl;
            int option1 = 0;
            std::cin>>option1;
            while(option1<1 || option1 >4)
            {
                std::cout<<"Please select from 1-4."<<std::endl;
                std::cin>>option1;
            }
            if (option1 == 4)
                break;
            switch (option1)
            {
                case 1:
                    accounts[accNames[option-1]]->seeBalance();
                    break;
                case 2:
                    accounts[accNames[option-1]]->deposit();
                    break;
                    
                case 3:
                    accounts[accNames[option-1]]->withdraw();
                    break;
            }
        }
    
    }
}

void user::saveAccounts(std::ofstream & data)
{
    data<<"CardNum "<<cardNum<<std::endl;
    data<<"PIN "<<PIN<<std::endl;
    data << accNum<<std::endl;
    for (auto & x: accounts)
    {
        data<<x.second->getName()<<" "<<x.second->getBalance()<<std::endl;
    }
}

user::~user()
{
    for (auto & x:accounts)
    {
        delete x.second;
    }
}

ATM::ATM()
{
    userNum = 0;
}

void ATM::loadUsers(std::string & fileName)
{
    std::ifstream data(fileName);
    if(data.is_open())
    {
        std::string curType;
        std::string curCardNum;
        std::string curPIN;
        int accNum = 0;
        
        //first read the number of users
        data >> userNum;
        for (int i = 0; i<userNum;i++)
        {
            data >> curType >> curCardNum;
            data >> curType >> curPIN;
            data >> accNum;
            users[curCardNum] = new user(curCardNum, curPIN, accNum);
            users[curCardNum]->loadAccounts(data);
        }
        
    }
    data.close();
}

void ATM::newUser()
{
    std::string newCardNum;
    std::string newPIN;
    std::cout<<"Please enter your card number to activate your account:"<<std::endl;
    std::cin>>newCardNum;
    std::cout<<"Please enter your PIN:"<<std::endl;
    std::cin>>newPIN;
    users[newCardNum] = new user(newCardNum, newPIN, 0);
    users[newCardNum]->newAccount();
    userNum += 1;
    std::cout<<"Your card has been activated."<<std::endl;
}

void ATM::saveUsers(std::string & fileName)
{
    std::ofstream data(fileName, std::ofstream::trunc);
    if(data.is_open())
    {
        data << userNum<<std::endl;
        for (auto & x:users)
        {
            x.second->saveAccounts(data);
        }
    }
    data.close();
}

void ATM::login()
{
    std::string curCardNum, curPIN;
    std::cout<<"Please insert your card (enter card number):"<<std::endl;
    std::cin>>curCardNum;
    while(users.find(curCardNum) == users.end())
    {
        std::cout<<"Invalid card number, please check and re-enter:"<<std::endl;
        std::cin>>curCardNum;
    }
    std::cout<<"Please enter your PIN:"<<std::endl;
    std::cin>>curPIN;
    while(!users[curCardNum]->checkPIN(curPIN))
    {
        std::cout<<"Invalid PIN, please check and re-enter again:"<<std::endl;
        std::cin>>curPIN;
    }
    while(1)
    {
        std::cout<<"What do you want to do?"<<std::endl;
        std::cout   <<"1. Create new account\n"
                    <<"2. Select an account to operate\n"
                    <<"3. Log Out"<<std::endl;
        int option = 0;
        std::cin>>option;
        while(option < 1 || option > 3)
        {
            std::cout<<"Please choose a valid option."<<std::endl;
            std::cin>>option;
        }
        if(option == 3)
            break;
        switch (option) {
            case 1:
                users[curCardNum]->newAccount();
                break;
                
            case 2:
                users[curCardNum]->selectAccount();
                break;
        }
    }
    
}

ATM::~ATM()
{
    for(auto & x:users)
    {
        delete x.second;
    }
}
