#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include<cmath>
#include <chrono>
#include <ctime> 
#include <iomanip>
#include "Header.h"

int main()
{
	bool currentAccountOpened = false;		//check if a current account has been opened already
	bool ISAOpened = false;                 //check if a isa has been opened already
	int accountViewing = 0;                 //stores the index of the account currently being viewed
	std::vector <Account*> accountList;	    //vector to hold all accounts made
	std::vector <std::string> parameters;   //vector that holds the inputs made
	std::string userCommand;                //holds the whole input of the user
	std::string command;                    //holds the initial command of the user
	//outputs the menu
	std::cout << "~~~ Welcome to LincBank! ~~~" << "\n"
		"open account_type initial_deposit : account types current(1), savings(2) or ISA(3) account" << "\n"
		"view index : view balance and recent transactions" << "\n"
		"withdraw sum : withdraw funds from most recently viewed account" << "\n"
		"deposit sum : deposit funds into most recently viewed account" << "\n"
		"transfer src dest sum : transfer funds between accounts" << "\n"
		"project years : project balance forward in time" << "\n"
		"search type amount : search for Initial deposit(1), Deposit(2), Withdraw(3), Transfer from(4) or Transfer to(5) transaction with a certain amount" << "\n"
		"options : view these options again" << "\n"
		"exit : close this application" << std::endl;
	//keeps user in menu until they input "exit"
	while (userCommand != "exit")
	{
		bool inputVal = true;                               //check if the input is valid
		parameters.clear();                                 // clear ready for next command
		std::cout << std::endl << ">>> ";
		std::getline(std::cin, userCommand);                //gets the user input

		char* cstr = new char[userCommand.length() + 1];    //
		strcpy(cstr, userCommand.c_str());                  //
		char* token;                                        //
		token = strtok(cstr, " ");                          //Splits up the user input into words
		while (token != NULL)                               //and adds them to parameters vector
		{                                                   //
			parameters.push_back(token);                    //
			token = strtok(NULL, " ");                      //
		}                                                   //

		if (parameters.size() == 0)                            //
		{                                                      //Check to make sure
			std::cout << "No Input Detected" << std::endl;     //user has input something
		}                                                      //
		// Define all commands as per the brief
		else
		{
			command = parameters[0];  //sets command to the first word the user input
		}

		for (int i = 1; i < parameters.size(); i++)        //
		{                                                    //
			if (inputVal)                                    //
			{                                                //Checks if any of the input after the command
				for (char const& c : parameters[i])          //is not a digit or a ".", if not then the input is invalid
				{                                            //
					if (!(std::isdigit(c)) && c != '.')      //
					{                                        //
						inputVal = false;                    //
					}                                        //
				}                                            //
			}
			else
			{
				break;                                       //stops for loop if an invalid input is found
			}
		}

		if (!inputVal || std::find(parameters.begin(), parameters.end(), ".") != parameters.end())  //checks if invalid or if input is just a "."
		{
			std::cout << "Please input valid information" << std::endl;   //goes to next loop if input is invalid
			continue;
		}

		if (command.compare("options") == 0)
		{
			// displays the menu to the user
			std::cout << "~~~ Welcome to LincBank! ~~~" << "\n"
				"open type initial_deposit : open a current(1), savings(2) or ISA(3) account" << "\n"
				"view[index] : view balance and recent transactions" << "\n"
				"withdraw sum : withdraw funds from most recently viewed account" << "\n"
				"deposit sum : deposit funds into most recently viewed account" << "\n"
				"transfer src dest sum : transfer funds between accounts" << "\n"
				"project years : project balance forward in time" << "\n"
				"search type amount : search for Initial deposit(1), Deposit(2), Withdraw(3), Transfer from(4) or Transfer to(5) transaction with a certain amount" << "\n"
				"options : view these options again" << "\n"
				"exit : close this application" << std::endl;
		}
		else if (command.compare("open") == 0)
		{
			// allow a user to open an account
			if (parameters.size() > 2)     //checks if enough parameters have been entered
			{
				float startBalance = stof(parameters[2]);                                         //sets the third input of the user to be the start balance
				Transaction* newTransaction = new Transaction("Initial deposit", startBalance);    //creates a new transaction to be stored in history
				if (parameters[1] == "1" && !currentAccountOpened)                   //cehcks if user wants to open a current account and if they have done already
				{
					std::cout << "Current account created! " << std::endl;
					Account* currentAccount = new Current(startBalance);         //creates new current account
					currentAccountOpened = true;                                 //lets program know that a current account have been made
					accountList.push_back(currentAccount);                       //adds account to account vector
					accountViewing = accountList.size() - 1;                     //sets the currently viewing account to be the account just added
					accountList[accountViewing]->addToHistory(newTransaction);   //adds the transaction to transaction history
				}
				else if (parameters[1] == "2")     //cehcks if user wants to open a savings account
				{
					std::cout << "Savings account created!" << std::endl;
					Account* savingsAccount = new Savings(false, startBalance);      //creates new savings account
					accountList.push_back(savingsAccount);                           //adds account to account vector
					accountViewing = accountList.size() - 1;                         //sets the currently viewing account to be the account just added
					accountList[accountViewing]->addToHistory(newTransaction);       //adds the transaction to transaction history
				}
				else if (parameters[1] == "3" && !ISAOpened)    //cehcks if user wants to open an ISA account and if they have done already
				{
					if (startBalance < 1000)    //stops the program from openeing an ISA with less than £1000
					{
						std::cout << "ISA initial balance must be >= " << "\x9C" << "1000." << std::endl;  //lets user know how much they need to open an ISA with
					}
					else
					{
						std::cout << "ISA created!" << std::endl;
						Account* ISAAccount = new Savings(true, startBalance);      //creates new savings account as an ISA
						ISAOpened = true;                                           //lets program know that an ISA has been opened
						accountList.push_back(ISAAccount);                          //adds account to account vector
						accountViewing = accountList.size() - 1;                    //sets the currently viewing account to be the account just added
						accountList[accountViewing]->addToHistory(newTransaction);  //adds the transaction to transaction history
					}
				}
				else if (currentAccountOpened || ISAOpened)
				{
					std::cout << "Account already opened" << std::endl;   //tells user if they have already opened an ISA or current account
				}
				else
				{
					std::cout << "You have not given the correct information" << std::endl;
				}
			}
			else
			{
				std::cout << "You haven't given enough information" << std::endl;
			}
		}
		else if (command.compare("exit") == 0 && parameters.size() == 1)    //allows user to exit the menu
		{
			std::cout << "Press any key to quit...";
		}

		else if (accountList.size() == 0)   //if user tries to do a command other than "open" without openeing an accout then it stops them
		{
			std::cout << "You have not made an account yet" << std::endl;
		}
		else if (command.compare("view") == 0)
		{
			//display all accounts if no index is provided
			if (parameters.size() == 1)    //if the user has only input "view" then the program will view all accounts made
			{
				for (auto account : accountList)                                                                    //
				{																									//Loops through all accounts and
					std::cout << account->getType() << " account | \x9C" << account->toString() << std::endl;		//outputs balance and history
					account->getAllTransactions();																	//
				}																									//
			}																										//
			// display an account according to an index (starting from 1)
			else if (std::stoi(parameters[1]) > accountList.size())	//check to make sure the account exists
			{
				std::cout << "This account does not exist" << std::endl;
			}
			else  //if the user has entered "view" plus an account they want to view then it will only show that accounts balance and history
			{
				accountViewing = stoi(parameters[1]) - 1;																								//Sets account viewing to this one
				std::cout << accountList[accountViewing]->getType() << " account | \x9C" << accountList[accountViewing]->toString() << std::endl;		//Outputs balance
				accountList[accountViewing]->getAllTransactions();																						//Outputs history
			}
		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
			if (parameters.size() == 2)  //checks if enough parameters have been entered
			{
				if (accountList[accountViewing]->withdraw(std::stof(parameters[1])))   //checks if the withdraw can go through
				{
					Transaction* newTransaction = new Transaction("Withdraw", std::stof(parameters[1]));													//Creates new transaction
					accountList[accountViewing]->addToHistory(newTransaction);																				//Adds transaction to history
					std::cout << accountList[accountViewing]->getType() << " account | \x9C" << accountList[accountViewing]->toString() << std::endl;		//Outputs balance
					accountList[accountViewing]->getAllTransactions();																						//Outputs history
				}
			}
			else
			{
				std::cout << "You have not given the correct information" << std::endl;
			}

		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
			if (parameters.size() == 2)  //checks if enough parameters have been entered
			{
				if (accountList[accountViewing]->deposit(stof(parameters[1])))   //checks if deposit can go through
				{
					Transaction* newTransaction = new Transaction("Deposit", std::stof(parameters[1]));														//Creates new transaction
					accountList[accountViewing]->addToHistory(newTransaction);																				//Adds transaction to history
					std::cout << accountList[accountViewing]->getType() << " account | \x9C" << accountList[accountViewing]->toString() << std::endl;		//Outputs balance
					accountList[accountViewing]->getAllTransactions();																						//Outputs transactions
				}
			}
			else
			{
				std::cout << "You have not given the correct information" << std::endl;
			}

		}
		else if (command.compare("transfer") == 0)
		{
			// allow user to transfer funds between accounts
			if (parameters.size() != 4)   //checks if enough parameters have been entered
			{
				std::cout << "You have not given the correct information" << std::endl;
			}
			else
			{
				int source = std::stoi(parameters[1]);		  //Sets the second user input the be the source of the transaction
				int destination = std::stoi(parameters[2]);	  //Sets the thrid as the destination
				float sum = std::stof(parameters[3]);		  //Sets the fourth as the amount being transfered
				if (accountList.size() < source || accountList.size() < destination || parameters[1] == parameters[2])     //Makes sure the accounts exist
				{
					std::cout << "You have not given the correct information" << std::endl;
				}
				else
				{
					if (accountList[source - 1]->withdraw(sum) && accountList[destination - 1]->deposit(sum))    //Checks if the withdraw and the deposit can be made
					{
						std::cout << "Transfer successful!" << std::endl;
						Transaction* transactionOut = new Transaction("Transfer from account", sum);															//Creates new transaction for the source account
						accountList[source - 1]->addToHistory(transactionOut);																					//Add transaction to history
						Transaction* transactionIn = new Transaction("Transfer to account", sum);																//Creates new transaction for the destination account
						accountList[destination - 1]->addToHistory(transactionIn);																				//Adds transaction to history
						std::cout << accountList[source - 1]->getType() << " account | \x9C" << accountList[source - 1]->toString() << std::endl;				//Outputs source accounts balance
						accountList[source - 1]->getAllTransactions();																							//Outputs source accounts history
						std::cout << accountList[destination - 1]->getType() << " account | \x9C" << accountList[destination - 1]->toString() << std::endl;		//Outputs destination accounts balance
						accountList[destination - 1]->getAllTransactions();																						//Outputs destination accounts history
					}
				}
			}
		}
		else if (command.compare("project") == 0)
		{
			// compute compound interest t years into the future
			if (parameters.size() != 2)	  //checks if enough parameters have been entered
			{
				std::cout << "You have not given the correct information" << std::endl;
			}
			else
			{
				if (accountList[accountViewing]->getType() != "Current")  //Makes sure the account isn't a current account
				{
					Savings* tempAccount = dynamic_cast<Savings*>(accountList[accountViewing]);             //Casts the account from the account vector to a temporary account of type savings
					std::cout << "Projected balance: " << "\x9C" << tempAccount->computeInterest(stoi(parameters[1])) << std::endl;	//Outputs the computed interest 
				}
				else
				{
					std::cout << "This is not a savings account" << std::endl;
				}
			}
		}
		else if (command.compare("search") == 0)
		{
			//Allows users to search their account history for a transaction
			if (parameters.size() != 3)   //checks if enough parameters have been entered
			{
				std::cout << "You have not given the correct information" << std::endl;
			}
			else
			{
				int numType = stoi(parameters[1]);								//Sets the second user input as the type of transaction to be searched for
				float amount = stof(parameters[2]);								//Sets the third user input as the amount in the transaction to be searched for
				std::string type;												//Holds the type of transaction based on the user input
				if (numType == 1) { type = "Initial deposit"; }					//
				else if (numType == 2) { type = "Deposit"; }					//
				else if (numType == 3) { type = "Withdraw"; }					//Sets the type based on what
				else if (numType == 4) { type = "Transfer from account"; }		//number the user input
				else if (numType == 5) { type = "Transfer to account"; }		//
				else { type = " "; }											//
				accountList[accountViewing]->searchTransactions(type, amount);  //Searches through the transactions to find a match
			}
		}
		else
		{
			std::cout << "Please input valid information" << std::endl;
		}
	}
	std::getchar();
}