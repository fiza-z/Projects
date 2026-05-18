#include <iostream>
using namespace std;
int main()
{
	cout << "WELCOME TO ABC BANK\nPlease insert your card to get started." << endl;                       //instructions for the user
	const int pin = 1234;                    //fixed pin
	int user_pin, attempts = 1;                        //counter for loop
	cout << "Enter your 4 digit Pin: "; 
	cin >> user_pin;
	while (attempts < 3 && user_pin != pin)                    //loop for entering pin, provides user with 2 more attemps
	{
		cout << "Try Again" << endl;
		cout << "Enter your Pin again: ";
		cin >> user_pin;
		attempts++;
	}
		if (user_pin == pin)            //executes if the user enters correct pin within the given attempts
		{
			cout << "You have entered the correct Pin." << endl;
			int choice, balance = 80950, amount, tran=0;            //choice for user to enter, current balance, amount to deposit or withdraw, transation for mini statement
			string last_tran = "None";              //string for transation type in mini statement
			do
			{
				cout << "Choose the options from the list below:\n1. Check Balance\n2. Deposite Money\n3. Withdraw Money\n4. Show Mini Statement\n5. Exit" << endl;              //menu for user selection
				cin >> choice;
				switch (choice)
				{
				case 1:
				{
					cout << "Your current balance is PKR " << balance << endl;
					break;
				}
				case 2:
				{
					cout << "Enter the amount you want to deposit: PKR ";
					cin >> amount;
					if (amount + balance < balance)             //shows operator overflow
					{
						cout << "There is a balance underflow." << endl;
					}
					else
					{
						balance += amount;         //balance updated using prefix and postfix
						last_tran = "Deposited";           //stored the cureent transaction type
						tran = amount;           //stored the transaction amount
						cout << "Your amount has been deposited.\nYour new balance is: " << balance << endl;
					}
					break;
				}
				case 3:
				{
					cout << "Enter the amount you want to withdraw: PKR ";
					cin >> amount;
					if (balance < amount)
					{
						cout << "You have insufficient balance." << endl;
					}
					else
					{
						balance -= amount;        //balance updated using pref and postfix
						last_tran = "Withdrawed";        //stored the cureent transaction type
						tran = amount;            //stored the transaction amount
						cout << "Your amount has been withdrawed.\nYour new balance is: " << balance << endl;
					}
					break;
				}
				case 4:
				{
					cout << "STATEMENT OF LAST TRANSACTION:" << endl;
					if (last_tran == "None")       //if user does not perform any transactions
					{
						cout << "No transaction has been made yet." << endl;
					}
					else
					{
						cout << "You " << last_tran << " PKR " << tran << "." << endl;
						cout << "Your baance after transacton is: " << balance << endl;
					}
						break;
				}
				case 5:
				{
					cout << "THANK YOU FOR USING OUR ATM, GOODBYE!" << endl;       //program terminates when user chooses exit and displays goodbye message
					break;
				}
				default:
				{
					cout << "Invalid choice" << endl;        //executes when user enters something apart fron the provided choices
				}
				}
			} while (choice != 5);           //program terminates when user enters 5
		}
		else
		{ 
			cout << "Incorrect pasword, the ATM has been locked." << endl;         //executes if user enters wrong pin 3 times
		}
}