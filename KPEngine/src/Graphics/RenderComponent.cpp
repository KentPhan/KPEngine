#include "../../include/Graphics/RenderComponent.h"
#include "GLib.h"
#include <cassert>
#include "../../include/Utils/FileIO.h"


namespace KPEngine
{
	namespace Graphics
	{
		RenderComponent::RenderComponent(WeakPointer<Core::GameObject> i_GameObject, const char* i_pFileName) :m_pGameObject(i_GameObject), m_isFlipped(false)
		{
			m_FileName = KPString(i_pFileName);
			m_pSprite = CreateSprite(m_FileName.Get(), false);
		}


		RenderComponent::~RenderComponent()
		{
			GLib::Sprites::Release(m_pSprite);
			m_pGameObject.~WeakPointer();
		}

		void RenderComponent::Draw(const KPMatrix4x4SSE& i_CameraSpace)
		{
			/*static float			moveDist = .01f;
			static float			moveDir = moveDist;

			static GLib::Point2D	Offset = { -180.0f, -100.0f };

			if (Offset.x < -220.0f)
				moveDir = moveDist;
			else if (Offset.x > -140.0f)
				moveDir = -moveDist;

			Offset.x += moveDir;*/

			// TODO No Idea what the hell is happening here possibly. But there needs to be some clean up if invalid
			StrongPointer<Core::GameObject> l_pTempGameObject =  m_pGameObject.GetStrongPointer();
			assert(l_pTempGameObject);// Breaking here on purpose for purposes of testing and experimentation
			if (!l_pTempGameObject)
				return;

			KPVector3SSE m_Position = i_CameraSpace * l_pTempGameObject-> GetPosition();
			GLib::Point2D Offset = { m_Position.X(), m_Position.Y() };
			GLib::Sprites::RenderSprite(*m_pSprite, Offset, 0.0f);
		}

		void RenderComponent::FlipSprite()
		{
			GLib::Sprites::Release(m_pSprite);
			m_isFlipped = !m_isFlipped;
			m_pSprite = CreateSprite(m_FileName.Get(), m_isFlipped);
		}

		GLib::Sprites::Sprite* RenderComponent::CreateSprite(const char * i_pFilename, bool i_FlipHorizontally)
		{
			assert(i_pFilename);

			size_t sizeTextureFile = 0;

			// Load the source file (texture data)
			void * pTextureFile = FileIO::LoadFile(i_pFilename, sizeTextureFile);

			// Ask GLib to create a texture out of the data (assuming it was loaded successfully)
			GLib::Texture * pTexture = pTextureFile ? GLib::CreateTexture(pTextureFile, sizeTextureFile) : nullptr;

			// exit if something didn't work
			// probably need some debug logging in here!!!!
			if (pTextureFile)
				delete[] pTextureFile;

			if (pTexture == nullptr)
				return NULL;

			unsigned int width = 0;
			unsigned int height = 0;
			unsigned int depth = 0;

			// Get the dimensions of the texture. We'll use this to determine how big it is on screen
			bool result = GLib::GetDimensions(pTexture, width, height, depth);
			assert(result == true);
			assert((width > 0) && (height > 0));

			// Define the sprite edges
			GLib::Sprites::SpriteEdges	Edges = { -float(width / 2.0f), float(height), float(width / 2.0f), 0.0f };
			
			GLib::Sprites::SpriteUVs	UVs;
			if(!i_FlipHorizontally)
				UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
			else
				UVs = { { 1.0f, 0.0f }, { 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

			GLib::RGBA							Color = { 255, 255, 255, 255 };

			// Create the sprite
			GLib::Sprites::Sprite * pSprite = GLib::Sprites::CreateSprite(Edges, 0.1f, Color, UVs);
			if (pSprite == nullptr)
			{
				GLib::Release(pTexture);
				return nullptr;
			}

			// Bind the texture to sprite
			GLib::Sprites::SetTexture(*pSprite, *pTexture);

			return pSprite;
		}

		
	}
}


