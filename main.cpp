//
//  main.cpp
//  ATM
//
//  Created by Hejin Liu on 9/11/20.
//  Copyright © 2020 Hejin Liu. All rights reserved.
//

#include <iostream>
#include "ATM.hpp"
#include <string>
#include <fstream>

int main(int argc, const char * argv[]) {
    std::string dataFileName;
    std::ifstream test4open;
    std::cout<<"System initialization...Please enter the name of the data file with full directory:"<<std::endl;
    std::getline(std::cin, dataFileName);
    test4open.open(dataFileName);
    while(!test4open.good())
    {
        std::cout<<"Cannot open the file properly, check and re-enter again:"<<std::endl;
        std::cin>>dataFileName;
        test4open.open(dataFileName);
    }
    ATM anATM;
    anATM.loadUsers(dataFileName);
    while (1)
    {
        std::cout<<"Welcome to this ATM, what do you want to do?"<<std::endl;
        std::cout   <<"1. Log In\n"
                    <<"2. Activate My Card\n"
                    <<"3. Shut Down (FOR TECHNICIAN ONLY)"<<std::endl;
        int option = 0;
        std::cin>>option;
        while (option<1||option>3)
        {
            std::cout<<"Please choose a valid option from 1-3."<<std::endl;
            std::cin>>option;
        }
        if(option==3)
            break;
        switch (option) {
            case 1:
                anATM.login();
                break;
                
            case 2:
                anATM.newUser();
                break;
        }
    }
    anATM.saveUsers(dataFileName);
    
    return 0;
}
