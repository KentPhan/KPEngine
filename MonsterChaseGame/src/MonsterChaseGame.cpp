// MonsterChaseGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "C:/Users/Kent_/Projects/School/C++Programming/Assignment1/u0734504/MonsterChaseGame/include/pch.h"
#include <iostream>
#include "../include/GameObjects/Classes/Player.h"
#include "../include/GameObjects/Classes/Monster.h"
#include "../include/Managers/GameManager.h"


int main()
{
	//_CrtSetBreakAlloc(237);

	GameManager* game = new GameManager();
	game->InitiateGame();
	std::cout << "Ending Game\n";
	//std::cin.ignore();


	
	
	bool check = _CrtDumpMemoryLeaks();

	return 0;
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
