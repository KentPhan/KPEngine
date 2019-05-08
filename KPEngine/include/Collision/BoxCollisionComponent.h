#pragma once
#include "../Utils/KPVector4SSE.h"
#include "../Core/GameObject/GameObject.h"

#include "CollisionSystem.h"
#include "../Utils/Delegates.h"
#include "../Physics/PhysicsComponent.h"

namespace KPEngine
{
	namespace Collision
	{
		struct CollisionInfo;

		class BoxCollisionComponent
		{
		public:
			BoxCollisionComponent(StrongPointer<Core::GameObject> i_GameObject);
			~BoxCollisionComponent();

			inline StrongPointer<Core::GameObject> GetGameObject() const
			{
				return m_pGameObject;
			}
			inline StrongPointer<Physics::PhysicsComponent> GetPhysicsComponent() const
			{
				return m_pPhysicsComponent;
			}

			KPVector3SSE m_Center;
			KPVector3SSE m_Extents;

			// TODO add delegate method to subscribe on collision
			MultiCastDelegate<CollisionInfo> OnCollisionHandler;

		private:
			StrongPointer<Core::GameObject> m_pGameObject;
			StrongPointer<Physics::PhysicsComponent> m_pPhysicsComponent;
			
		};
	}
}
