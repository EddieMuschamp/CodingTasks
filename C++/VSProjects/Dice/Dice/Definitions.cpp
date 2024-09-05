#include <iostream>
#include <vector>
#include <string>
#include "Header.h"

Dice::Dice(int num, int type)
{
	numberOf = num;
	typeOf = type;
}

void Dice::Roll() 
{	
	rolls.clear();
	int total = 0;
	for(int i = 0; i < numberOf; i++)
	{
		int roll = rand() % (typeOf);
		roll += 1;
		rolls.push_back(roll);
		total = total + roll;
	}

	std::cout << total << ":";
	for (int roll : rolls) 
	{
		std::cout << " " << roll;
	}
}

