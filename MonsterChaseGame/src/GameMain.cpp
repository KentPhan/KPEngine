#include "../include/GameMain.h"
// PlatformerGame.cpp : This file contains the 'main' function. Program execution begins and ends there.


//#include "KPEngine-init.h"
#include <iostream>
#include <Windows.h>


#include <assert.h>
#include <stdio.h>
#include <stdint.h>


#include "GLib.h"
#include "KPEngine-init.h"
#include "../include/PlatformerGame.h"

void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	//_CrtSetBreakAlloc(166);
	//_CrtSetBreakAlloc(167);


	if(KPEngine::Initialize())
	{
		
		if(PlatformerGame::PlatformerGame::InitializeGame())
		{
			KPEngine::Run();

			PlatformerGame::PlatformerGame::Shutdown();
		}

		KPEngine::CleanUp();
	}

	

	//// G Lib Test. TODO Migrate Later
	//// IMPORTANT: first we need to initialize GLib
	//bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Monster Chase Game", -1, 800, 600);

	//if (bSuccess)
	//{
	//	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	//	GLib::SetKeyStateChangeCallback(TestKeyCallback);

	//	// Create a couple of sprites using our own helper routine CreateSprite
	//	GLib::Sprites::Sprite * pGoodGuy = CreateSprite("Assets\\girl.dds");
	//	GLib::Sprites::Sprite * pBadGuy = CreateSprite("Assets\\zombie.dds");

	//	bool bQuit = false;

	//	do
	//	{
	//		// IMPORTANT: We need to let GLib do it's thing. 
	//		GLib::Service(bQuit);

	//		if (!bQuit)
	//		{
	//			// IMPORTANT: Tell GLib that we want to start rendering
	//			GLib::BeginRendering();
	//			// Tell GLib that we want to render some sprites
	//			GLib::Sprites::BeginRendering();

	//			if (pGoodGuy)
	//			{
	//				static float			moveDist = .01f;
	//				static float			moveDir = moveDist;

	//				static GLib::Point2D	Offset = { -180.0f, -100.0f };

	//				if (Offset.x < -220.0f)
	//					moveDir = moveDist;
	//				else if (Offset.x > -140.0f)
	//					moveDir = -moveDist;

	//				Offset.x += moveDir;

	//				// Tell GLib to render this sprite at our calculated location
	//				GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 0.0f);
	//				GLib::Sprites::RenderSprite(*pGoodGuy, Offset, 90.0f);
	//			}
	//			if (pBadGuy)
	//			{
	//				static float			moveDist = .02f;
	//				static float			moveDir = -moveDist;

	//				static GLib::Point2D	Offset = { 180.0f, -100.0f };

	//				if (Offset.x > 200.0f)
	//					moveDir = -moveDist;
	//				else if (Offset.x < 160.0f)
	//					moveDir = moveDist;

	//				Offset.x += moveDir;

	//				// Tell GLib to render this sprite at our calculated location
	//				GLib::Sprites::RenderSprite(*pBadGuy, Offset, 0.0f);
	//			}

	//			// Tell GLib we're done rendering sprites
	//			GLib::Sprites::EndRendering();
	//			// IMPORTANT: Tell GLib we're done rendering
	//			GLib::EndRendering();
	//		}
	//	} while (bQuit == false);

	//	if (pGoodGuy)
	//		GLib::Sprites::Release(pGoodGuy);
	//	if (pBadGuy)
	//		GLib::Sprites::Release(pBadGuy);

	//	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	//	GLib::Shutdown();
	//}


	// The Game
	/*PlatformerGame::InitializeGame();
	PlatformerGame::InitiateGame();
	std::cout << "Ending Game\n";
	std::cin.ignore();
	PlatformerGame::Shutdown();*/

	

	bool check = _CrtDumpMemoryLeaks();
	return 0;
}

GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename)
{
	assert(i_pFilename);

	size_t sizeTextureFile = 0;

	// Load the source file (texture data)
	void * pTextureFile = LoadFile(i_pFilename, sizeTextureFile);

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
	GLib::Sprites::SpriteUVs	UVs = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 1.0f, 1.0f } };
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

void * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
{
	assert(i_pFilename != NULL);

	FILE * pFile = NULL;

	errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
	if (fopenError != 0)
		return NULL;

	assert(pFile != NULL);

	int FileIOError = fseek(pFile, 0, SEEK_END);
	assert(FileIOError == 0);

	long FileSize = ftell(pFile);
	assert(FileSize >= 0);

	FileIOError = fseek(pFile, 0, SEEK_SET);
	assert(FileIOError == 0);

	uint8_t * pBuffer = new uint8_t[FileSize];
	assert(pBuffer);

	size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
	assert(FileRead == FileSize);

	fclose(pFile);

	o_sizeFile = FileSize;

	return pBuffer;
}