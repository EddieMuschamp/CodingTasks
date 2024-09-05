#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include<cmath>
#include <chrono>
#include <ctime> 


//Transaction Class

class Transaction
{
public:
	Transaction(std::string type, float newValue);
	std::string toString();
	std::string getTime();
	std::string displayTransaction();
	int getValue();
	std::string getType();
protected:
	std::string desc;		//Holds the transaction type
	std::string timeStamp;	//Holds the time stamp
	float value;			//Holds the value of the transaciton
};


//Account Class with pure abstract functions

class Account
{
public:
	virtual bool deposit(float depositAmount) = 0;
	virtual std::string toString() = 0;
	virtual bool withdraw(float withdrawAmount) = 0;
	virtual float getBalance() = 0;
	virtual void setBalance(float balanceChange) = 0;
	virtual void addToHistory(Transaction* newTransaction) = 0;
	virtual int historyLength() = 0;
	virtual void getAllTransactions() = 0;
	virtual void searchTransactions(std::string type, float amount) = 0;
	virtual std::string getType() = 0;
protected:
	float balance;							//Holds the current balance of the account
	std::vector <Transaction*> history;		//Holds the history of transactions
	std::string accountType;				//Holds the account type
};


//Interest Earning Interface

class InterestEarning
{
public:
	virtual float computeInterest(int years) = 0;
};


//Current class

class Current : public Account
{
public:
	Current(float startBalance);
	bool deposit(float depositAmount);
	std::string toString();
	bool withdraw(float withdrawAmount);
	float getBalance();
	void setBalance(float balanceChange);
	void addToHistory(Transaction* newTransaction);
	int historyLength();
	void getAllTransactions();
	void searchTransactions(std::string type, float amount);
	std::string getType();
private:
	float overdraft = -500;	//Holds the overdraft of the current account
};


//Savings class

class Savings : public Account, public InterestEarning
{
public:
	Savings(bool ISA = false, float startBalance = 0);
	float computeInterest(int years);
	bool deposit(float depositAmount);
	std::string toString();
	bool withdraw(float withdrawAmount);
	float getBalance();
	void setBalance(float balanceChange);
	void addToHistory(Transaction* newTransaction);
	int historyLength();
	void getAllTransactions();
	void searchTransactions(std::string type, float amount);
	std::string getType();
private:
	float interestRate;	//Holds the interest rate
	bool isa;			//Bool to check if the account is an ISA or not
};


