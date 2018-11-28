#pragma once
class KPGameObject;

namespace KPEngine
{
	namespace Core
	{
		namespace Interfaces
		{
			class IKPGameObjectController
			{
			public:
				virtual void SetGameObject(KPGameObject * i_pObject) = 0;
				virtual void UpdateGameObject() = 0;
			};
		}
	}
}
