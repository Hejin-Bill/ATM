# ATM
Simple C++ Implementation of ATM

## Build
Please clone this repository and create a C++ project with the source files. This project was originally developed on Xcode 11.7.

## User Guide
### Step 1

Enter the absolute path to tell the program where to find a data file. An example `data.txt` is provided.

### Step 2

There are 4 levels of menu:

***Level 1***

[![Level 1](https://github.com/Hejin-Bill/ATM/blob/master/L1.png)]()


***Level 2: After log in***

[![Level 2: After log in](https://github.com/Hejin-Bill/ATM/blob/master/L2.png)]()

***Level 3: Select an account***

[![Level 3: Select an account](https://github.com/Hejin-Bill/ATM/blob/master/L3.png)]()
- Select `Cancel` will return to level 2.

***Level 4: Select an operation***

[![Level 3: Select an operation](https://github.com/Hejin-Bill/ATM/blob/master/L4.png)]()
- Select `Cancel` will return to level 3.

### Step 3
When shut down the system (option 3 in level 1), all the user information will be saved in the file of given path. The file is in `.txt` format for debug convenience.
The pattern of the data file is shown below:
```javascript
Number_of_user
CardNum Card_Number_1
PIN PIN_1
Number_of_account
Account_name_1 Account_balance_1
...
CardNum Card_Number_2
...
```
