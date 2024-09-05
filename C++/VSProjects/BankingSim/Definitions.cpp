#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include<cmath>
#include <vector>
#include <chrono>
#include <ctime> 
#include "Header.h"


//Transaction Class:

Transaction::Transaction(std::string type, float newValue)	//Constructor for transaction objects
{
	desc = type;			//Sets the type of the transaction 
	value = newValue;		//Sets the value
	timeStamp = getTime();	//Gets a time stamp of when the transaction was made
}

std::string Transaction::toString()  //Gets the value of a transaction as a string
{
	std::ostringstream stream;
	stream << value;
	return stream.str();
}

std::string Transaction::getTime() //Gets the date and time of a transaction
{
	auto clock = std::chrono::system_clock::now();
	std::time_t dateTime = std::chrono::system_clock::to_time_t(clock);
	return std::ctime(&dateTime);
}

std::string Transaction::displayTransaction()  //Displays a transaction
{
	std::string fullTransaction = "-- " + desc + ": \x9C" + toString() + " on " + timeStamp;  //Formats the output as a string
	return fullTransaction;
}

int Transaction::getValue()   //Returns the value of a transaction
{
	return value;
}

std::string Transaction::getType()  //Returns the type of a transaction
{
	return desc;
}


//Current Class:

Current::Current(float startBalance)   //Constructor for current accounts
{
	balance = startBalance;		//Sets the balance of the account to the initial deposit
	accountType = "Current";	//Sets the type of the account to current
}
bool Current::deposit(float depositAmount)	//Method to deposit an amount into current account
{
	if (depositAmount < 0)	//Checks if the amount entered is negative
	{
		std::cout << "Transaction failed" << std::endl;	//Tells user that the deposit didn't go through
		return false;									//Returns false so a transaction object isn't made
	}
	else
	{
		float tempBalance = getBalance();	//Gets the current balance
		tempBalance += depositAmount;		//Adds amount to the balance
		setBalance(tempBalance);			//Sets the new balance
		return true;						//Returns true so a transaction object can be made
	}
}

std::string Current::toString()		//Method to output balance as a string
{
	std::ostringstream stream;
	stream << balance;
	return stream.str();
}

bool Current::withdraw(float withdrawAmount)	//Method to withdraw an amount from current account
{
	float tempBalance = getBalance();										//Gets the current balance
	if (tempBalance - withdrawAmount < overdraft || withdrawAmount < 0)		//Cehcks if the overdraft is exceeded or the amount is less than 0
	{
		std::cout << "Transaction failed" << std::endl;						//Tells user that the transaction has failed
		return false;
	}
	else
	{
		tempBalance -= withdrawAmount;										//Takes amount away from balance
		setBalance(tempBalance);											//Sets the new balance
		return true;
	}
}

float Current::getBalance()		//Method to return the balance
{
	return balance;
}

void Current::setBalance(float balanceChange)	//Method to set the balance
{
	balance = balanceChange;
}

std::string Current::getType()	//Method to return the type of account
{
	return accountType;
}

void Current::addToHistory(Transaction* newTransaction)	//Method to add a transaction to the accounts history
{
	history.push_back(newTransaction);		//Adds a new transaction to the end of history
}

int Current::historyLength()	//Returns the size of history
{
	return history.size();
}

void Current::getAllTransactions()	//Method to display all transactions
{
	for (int i = 0; i < history.size(); i++)	//Loops for each transaction in history
	{
		std::cout << history[i]->displayTransaction();	//Calls method from Transaction class to display the transaction
	}
}

void Current::searchTransactions(std::string type, float amount)	//Method to sort and search the history
{
	bool sortFinished = false;														//Bool to check if the sort is finsihed
	std::vector<Transaction*> sortedHistory(history);								//New vector to hold the sorted transactions
	while (!sortFinished)															//Loops until vector is sorted
	{
		sortFinished = true;
		for (int i = 0; i < sortedHistory.size() - 1; i++)							//Loops through each object in the vector
		{
			if (sortedHistory[i]->getValue() > sortedHistory[i + 1]->getValue())	//Checks if the next objects value is smaller than this objects value
			{
				Transaction* temp = sortedHistory[i];								//Creates a temporary object
				sortedHistory[i] = sortedHistory[i + 1];							//Swaps the objects around
				sortedHistory[i + 1] = temp;										//
				sortFinished = false;												//If an object has been switched then the sort isn't finished
			}
		}
	}

	bool found = false;						//Bool to check if the search is finished
	int first = 0;							//Sets the first index to the start of the vector
	int last = sortedHistory.size() - 1;	//Sets the last index to the end
	int halfway;							//Variable to store the index halfway
	while (!found && first <= last)																		//Loops while it ins't found or the last index becomes less than first
	{
		halfway = (first + last) / 2;																	//Sets the halfway point
		if (sortedHistory[halfway]->getValue() == amount && sortedHistory[halfway]->getType() == type)	//Checks if the transaction has been found
		{
			found = true;
			std::cout << sortedHistory[halfway]->displayTransaction() << std::endl;						//Displays the found transaction
		}
		else if (sortedHistory[halfway]->getValue() > amount)											//If the value of the transaction at halfway is creater than the input, then the last index is set to the halfway point
		{
			last = halfway - 1;
		}
		else																							//If the value of the transaction at halfway is less than the input, then the first index is set to the halfway point
		{
			first = halfway + 1;
		}
	}

	if (!found)			//If the transaction was never found then it tells the user
	{
		std::cout << "This transaction does not exist" << std::endl;
	}
	sortedHistory.clear(); //deletes all of the objects within
}



//Savings Class:

Savings::Savings(bool ISA, float startBalance)  //Constructor for savings account
{
	balance = startBalance;			//Sets balance to the start balance
	isa = ISA;						//Sets if the account is an ISA or not
	if (isa == true)				//If it is an ISA then the interest rate is set to 0.0115
	{
		interestRate = 0.0115f;
		accountType = "ISA";
	}
	else							//If it isn't an ISA then the interest rate is 0.0085
	{
		interestRate = 0.0085f;
		accountType = "Savings";
	}

}

bool Savings::deposit(float depositAmount)  //Method to deposit into savings account
{
	if (depositAmount < 0)	//If the amount depositing is negative then the transaction fails
	{
		return false;
		std::cout << "Transaction failed" << std::endl;
	}
	else
	{
		float tempBalance = getBalance(); //Makes a temporary balance
		tempBalance += depositAmount;     //Adds amount to balance
		setBalance(tempBalance);		  //Sets new balance
		return true;
	}
}

std::string Savings::toString()  //Method to make the balance a string
{
	std::ostringstream stream;
	stream << balance;
	return stream.str();
}

bool Savings::withdraw(float withdrawAmount)	//Method to withdraw money from savings account
{
	float tempBalance = getBalance();							//Sets a temporary balance
	if (tempBalance - withdrawAmount < 0 || withdrawAmount < 0)	//Checks if input is negative or the withdraw would set the account below 0
	{
		std::cout << "Transaction failed" << std::endl;
		return false;
	}
	else
	{
		tempBalance -= withdrawAmount;	//Subracts input amount from balance
		setBalance(tempBalance);		//Sets new balance
		return true;
	}
}

float Savings::computeInterest(int years)	//Method to compute the interest earned
{
	float interestOutput;															//Variable to hold the interest earned
	float tempBalance = getBalance();												//Gets the current balance
	interestOutput = (tempBalance * pow((1 + (interestRate / 12)), (12 * years)));	//Computes the interest
	return interestOutput;															//Returns the interest earned
}

float Savings::getBalance()	//Method to fetch the balance
{
	return balance;
}

void Savings::setBalance(float balanceChange)	//Method to set the balance
{
	balance = balanceChange;
}

std::string Savings::getType()	//Method to get the type of the account
{
	return accountType;
}

void Savings::addToHistory(Transaction* newTransaction)		//Method to add a transaction to the history
{
	history.push_back(newTransaction);	//Adds transaction to the end of history
}

int Savings::historyLength()	//Method to get the size of history
{
	return history.size();
}

void Savings::getAllTransactions()	//Method to output all transactions in history
{
	for (int i = 0; i < history.size(); i++)			//Iterates through all the transactions
	{
		std::cout << history[i]->displayTransaction();	//Displays each one
	}
}

void Savings::searchTransactions(std::string type, float amount)	//Method to sort and search through transactions
{
	bool finished = false;															//Bool to check if the sort is finsihed
	std::vector<Transaction*> sortedHistory(history);								//New vector to hold the sorted transactions
	while (!finished)																//Loops until vector is sorted
	{
		finished = true;
		for (int i = 0; i < sortedHistory.size() - 1; i++)							//Loops through each object in the vector
		{
			if (sortedHistory[i]->getValue() > sortedHistory[i + 1]->getValue())		//Checks if the next objects value is smaller than this objects value
			{
				Transaction* temp = sortedHistory[i];								//Creates a temporary object
				sortedHistory[i] = sortedHistory[i + 1];								//Swaps the object around
				sortedHistory[i + 1] = temp;											//
				finished = false;													//If an object has been switched then the sort isn't finished
			}
		}
	}

	bool found = false;						//Bool to check if the search is finished
	int first = 0;							//Sets the first index to the start of the vector
	int last = sortedHistory.size() - 1;	//Sets the last index to the end
	int halfway;							//Variable to store index halfway
	while (!found && first <= last)																		//Loops while it ins't found or the last index becomes less than first
	{
		halfway = (first + last) / 2;																	//Sets the halfway point			
		if (sortedHistory[halfway]->getValue() == amount && sortedHistory[halfway]->getType() == type)	//Checks if the transaction has been found
		{
			found = true;
			std::cout << sortedHistory[halfway]->displayTransaction() << std::endl;						//Displays the found transaction
		}
		else if (sortedHistory[halfway]->getValue() > amount)											//If the value of the transaction at halfway is creater than the input, then the last index is set to the halfway point
		{
			last = halfway - 1;
		}
		else																							//If the value of the transaction at halfway is less than the input, then the first index is set to the halfway point
		{
			first = halfway + 1;
		}
	}

	if (!found)			//If the transaction was never found then it tells the user
	{
		std::cout << "This transaction does not exist" << std::endl;
	}

	sortedHistory.clear(); //deletes all of the objects within
}