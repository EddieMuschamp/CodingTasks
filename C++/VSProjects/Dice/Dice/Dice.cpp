#include <iostream>
#include <vector>
#include <string>
#include "Header.h"

int main()
{
    std::string ndM;
    std::vector<std::string> ndMSplit;
    int num;
    int type;
    std::cout << "Please enter ndM" << std::endl;
    std::cin >> ndM;
    for (int i = 0; i < ndM.size(); i++) 
    {
        if (ndM[i] == 'd') 
        {
            num = std::stoi(ndM.substr(0, i));
            type = std::stoi(ndM.substr(i + 1, ndM.size()));
        }
    }
    Dice newDice(num, type);
    newDice.Roll();
}