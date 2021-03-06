
#include "../../include/Physics/PhysicsSystem.h"
#include <cassert>
#include "../../include/Physics/PhysicsComponent.h"
#include "../../include/Utils/SmartPointers.h"
#include <algorithm>

namespace KPEngine
{
	namespace Physics
	{
		bool PhysicsSystem::m_InitializeSuccessful;
		std::vector<StrongPointer<PhysicsComponent>>* PhysicsSystem::m_pPhysicsComponents;

		void PhysicsSystem::RegisterPhysicsComponent(WeakPointer<Core::GameObject> i_pGameObject, bool i_IsStatic)
		{
			assert(i_pGameObject);
			PhysicsComponent* l_NewComponent = new PhysicsComponent(i_pGameObject, i_IsStatic);
			m_pPhysicsComponents->push_back(l_NewComponent);
		}

		void PhysicsSystem::UnRegisterPhysicsComponent(const WeakPointer<Core::GameObject> i_GameObjectRef)
		{
			m_pPhysicsComponents->erase(
				std::remove_if(m_pPhysicsComponents->begin(), m_pPhysicsComponents->end(),
					[&i_GameObjectRef](StrongPointer<PhysicsComponent>& i_Item) {return i_Item->GetGameObject() == i_GameObjectRef; })
				, m_pPhysicsComponents->end());
		}

		StrongPointer<PhysicsComponent> PhysicsSystem::GetPhysicsComponent(const Core::GameObject* i_GameObjectRef)
		{
			// TODO So inefficent. But easiest way to current get a reference to the physics components without supplying a direct one to the game object
			if (PhysicsSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
				{
					if((*m_pPhysicsComponents)[i]->GetGameObject() == i_GameObjectRef)
					{
						return (*m_pPhysicsComponents)[i];
					}
				}
			}
			return nullptr;
		}

		void PhysicsSystem::Initialize()
		{
			m_pPhysicsComponents = new std::vector<StrongPointer<PhysicsComponent>>();
			PhysicsSystem::m_InitializeSuccessful = true;
		}

		void PhysicsSystem::PhysicsStepCalc(float i_DeltaTime)
		{
			if(PhysicsSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
				{
					(*m_pPhysicsComponents)[i]->UpdatePhysicsForcesPass(i_DeltaTime);
				}
			}
		}

		void PhysicsSystem::PhysicsStepApply(float i_DeltaTime)
		{
			if (PhysicsSystem::m_InitializeSuccessful)
			{
				for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
				{
					(*m_pPhysicsComponents)[i]->UpdatePhysicsMovementPass(i_DeltaTime);
				}
			}
		}

		void PhysicsSystem::Shutdown()
		{
			for (size_t i = 0; i < m_pPhysicsComponents->size(); i++)
			{
				(*m_pPhysicsComponents)[i].~StrongPointer();
			}

			m_pPhysicsComponents->clear();
			delete m_pPhysicsComponents;
		}
	}
}




