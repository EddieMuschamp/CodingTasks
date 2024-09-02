#pragma once
#include <vector>
#include <string>

class Dice
{
public:
	Dice(int num, int type);
	void Roll();
private:
	int numberOf;
	int typeOf;
	std::vector<int> rolls;
};