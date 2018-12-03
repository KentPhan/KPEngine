#pragma once

#include "../../../KPEngine/include/Utils/List.h"
#include "Core/Classes/KPGameObject.h"
#include "../Controllers/RandomMonsterController.h"
#include "../Controllers/PlayerController.h"




namespace MonsterChaseGame
{
	namespace Managers
	{
		class GameManager
		{
		private:
			KPGameObject* map_[20][20];
			List<KPGameObject*> * MonsterList;
			bool endGame = false;
			const int monster_limit_ = 50;

			void MainGameLoop(Controllers::PlayerController* player);
			void PrintMap() const;
			void UpdateMonsters();
			void SpawnMonster(const char* name);

		public:
			int number_of_monsters;

			// Constructors, Destructors
			GameManager();
			inline ~GameManager()
			{
				delete MonsterList;
				//delete[] map_;
			}

			void InitiateGame();
		};
	}
}



