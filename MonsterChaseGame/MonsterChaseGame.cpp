// MonsterChaseGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Monster.h"


int main()
{
	std::cout << "The Monster Chase Game - By Kent Phan!\n";


	// Get monster count input
	int number_of_monsters;
	while(true)
	{
		std::cout << "How many monsters to start?\n";
		if(std::cin >> number_of_monsters)
		{
			break;
		} else
		{
			std::cout << "Please enter a valid integer.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
		}
	}

	// Name monsters
	Monster *monsterList = new Monster[number_of_monsters];
	for(int i = 0 ; i < number_of_monsters; i++)
	{
		// STACK FIX
		char* name_input = new char[1000];
		std::cout << "Name monster " << i + 1 << ":\n";
		std::cin >> name_input;
		monsterList[i].SetName(name_input);
		std::cout << "Name " << name_input << " Accepted. \n";
		//delete[] name_input;
	}
	

	std::cout << "Hello World" << number_of_monsters << "!\n";


	delete[] monsterList;


	std::cin >> number_of_monsters;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
