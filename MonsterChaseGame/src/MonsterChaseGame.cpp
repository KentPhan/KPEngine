// MonsterChaseGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "../include/GameObjects/Classes/Player.h"
#include "../include/GameObjects/Classes/Monster.h"
#include "../include/Managers/GameManager.h"
#include "../../KPEngine/include/Utils/List.h"


int main()
{
	
	//_CrtSetBreakAlloc(237);

	/*GameObject* test = new GameObject();
	GameObject* test2 = new GameObject();
	GameObject* test3 = new GameObject();


	List<GameObject*> * shit = new List<GameObject*>();

	shit->Add(test);
	shit->Add(test2);
	shit->Add(test3);
	std::cout << shit->length() <<std::endl;
	std::cout << shit->Get(2) << std::endl;
	std::cout << shit->Get(1) << std::endl;
	std::cout << shit->Get(0) << std::endl;
	std::cout << shit->Get(3) << std::endl;
	shit->Remove(test2);
	shit->Print();*/
	

	

	GameManager* game = new GameManager();
	game->InitiateGame();
	std::cout << "Ending Game\n";
	//std::cin.ignore();


	/*delete shit;*/

	delete game;
    
	
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
