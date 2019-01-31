#pragma once
#include <Core/Interfaces/IGameObjectController.h>

using namespace KPEngine::Core;

namespace PlatformerGame
{
	namespace Controllers
	{
		class RandomMonsterController : public KPEngine::Core::Interfaces::IGameObjectController
		{
		public:
			RandomMonsterController();
			~RandomMonsterController()
			{
				delete m_pObject;
			};

			// Setter
			

			// Order
			inline void Initialize(GameObject* i_pObject) override
			{
				m_pObject = i_pObject;
				m_pObject->SetController(this);
			}
			void UpdateGameObject() override;

			// Info
			inline void PrintInfo() const override
			{
				std::cout << "Dumb Monster \"" << this->m_pObject->GetName().Get() << "\" at [" << this->m_pObject->GetPosition().X() << "," << this->m_pObject->GetPosition().Y() << "]\n";
			}
			inline char GetSymbol() const override
			{
				return 'm';
			}
			inline KPVector2 GetPosition() const override
			{
				return m_pObject->GetPosition();
			}
		private:
			void MoveMonsterRandomly();
			GameObject * m_pObject;
		};
	}
}


