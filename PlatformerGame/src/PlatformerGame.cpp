
#include <iostream>
#include "conio.h"
#include "Utils/KP_Log.h"
#include "../include/GameObjects/GameObjectType.h"
#include "../include/PlatformerGame.h"
#include "Core/Core.h"
#include  "Physics/PhysicsComponent.h"
#include <string>


using namespace PlatformerGame::Controllers;
using namespace KPEngine::Core;

namespace PlatformerGame
{
	
	using namespace KPEngine::Core::Interfaces;

	bool PlatformerGame::Init()
	{
		try
		{
			StrongPointer<GameObject> l_GameObject =  Core::InstantiateGameObject("Assets\\src\\Player.lua");
			//StrongPointer<GameObject> l_GameObject2 = Core::InstantiateGameObject("Assets\\src\\Monster.lua");
			StrongPointer<GameObject> l_GameObjectPlat = Core::InstantiateGameObject("Assets\\src\\Platform.lua");

			// Attaching Controller
			m_pPlayerController = new PlayerController();
			m_pPlayerController->Initialize(l_GameObject);


		}
		catch (int i_e)
		{
			DEBUG_PRINT(KPLogType::Fatal, "Game Failed to Initialize InitGame() %i",i_e);
			return false;
		}
		return true;
	}

	void PlatformerGame::Update(float i_deltaTime)
	{
		m_pPlayerController->Update(i_deltaTime);
		//DEBUG_PRINT(KPLogType::Verbose, "Game Update Triggered: %f", i_deltaTime);
	}

	bool PlatformerGame::Shutdown()
	{
		m_pPlayerController->Destroy();
		delete m_pPlayerController;
		return true;
	}
}

