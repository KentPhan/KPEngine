#include "../../../include/Scripting/Lua/LuaSystem.h"
#include <cassert>
#include "../../../include/Utils/FileIO.h"
#include "../../../include/Graphics/RendererSystem.h"
#include "../../../include/Physics/PhysicsComponent.h"
#include "../../../include/Physics/PhysicsSystem.h"
#include "../../../include/Collision/CollisionSystem.h"
#include "../../../include/Core/GameObject/GameObjectSystem.h"
#


// TODO strcmp is bad possibly in here
namespace KPEngine
{
	using namespace KPEngine::Core;

	namespace Scripting
	{
		namespace Lua
		{
			lua_State* LuaSystem::g_pLuaState;
			void LuaSystem::Initialize()
			{
				g_pLuaState = luaL_newstate();
				assert(g_pLuaState);
				luaL_openlibs(g_pLuaState);

				//// Call the Lua C API function lua_type
				//// to get the type of the top item on stack   
				//int type = lua_type(pLuaState, -1);
				// lua_tointeger
				// lua_pop
				// lua_len
				// lua_tostring
				// lua_tonumber
				// lua_loadbuffer Returning not 0 means error in lua code?
				// lua_pcall
			}

			void LuaSystem::Shutdown()
			{
				lua_close(g_pLuaState);
			}

			StrongPointer<Core::GameObject> LuaSystem::CreateGameObject(const char* i_pScriptFileName, bool i_OverridePosition, KPVector3SSE i_Position)
			{
				size_t l_SizeFile;
				StrongPointer<GameObject> l_NewStrongPointer = nullptr;

				// TODO need to adapt pathing
				char * l_pFileContents = static_cast<char*>(FileIO::LoadFile(i_pScriptFileName, l_SizeFile));

				// TODO File Error Handling
				//// exit if something didn't work
				//	// probably need some debug logging in here!!!!
				//if (l_pFileContents)
				//	delete[] l_pFileContents;

				//if (l_pFileContents == nullptr)
				//	return NULL;

				if (l_pFileContents && l_SizeFile)
				{
					int result = 0;
					result = luaL_loadbuffer(g_pLuaState, l_pFileContents, l_SizeFile, nullptr);
					assert(result == 0);
					result = lua_pcall(g_pLuaState, 0, 0, 0);
					assert(result == 0);

					
					// Getting number of items in table
					/*int l_type1 = lua_getglobal(g_pLuaState, "GameObject");
					assert(l_type1 == LUA_TTABLE);


					lua_len(g_pLuaState, -1);
					assert(lua_type(g_pLuaState, -1) == LUA_TNUMBER);

					lua_Integer table_entries = lua_tointeger(g_pLuaState, -1);
					int l_table_Entries = table_entries < INT_MAX ? int(table_entries) : INT_MAX;

					lua_pop(g_pLuaState, 1);
*/

					// Getting a specific key
					int l_GameObjectTable = lua_getglobal(g_pLuaState, "GameObject");
					assert(l_GameObjectTable == LUA_TTABLE);

					// Get Name
					lua_pushstring(g_pLuaState, "name");
					// Using stack field 1 as the key, get it's value from the table (in
					// stack field 2) replacing the key in field 1 by the associated value
					int l_nameType = lua_gettable(g_pLuaState, -2); // GameObject[top of stack after popping] =  Does GameObject(-2)["name"(Top of Stack)]
					// It should be a string
					assert(l_nameType == LUA_TSTRING);
					// Retrieve the value associated with key "name" as a string, assuming it�s a string
					const char * l_pName = lua_tostring(g_pLuaState, -1);
					// Pop it off the stack now we're done
					lua_pop(g_pLuaState, 1);

					// Get Position
					lua_pushstring(g_pLuaState, "position");
					int l_positionType = lua_gettable(g_pLuaState, -2);
					assert(l_positionType == LUA_TTABLE);
					int l_xType = lua_rawgeti(g_pLuaState, -1, 1);
					int l_yType = lua_rawgeti(g_pLuaState, -2, 2);
					int l_zType = lua_rawgeti(g_pLuaState, -3, 3);
					assert(l_xType == LUA_TNUMBER);
					assert(l_yType == LUA_TNUMBER);
					assert(l_zType == LUA_TNUMBER);
					float l_xValue = static_cast<float>(lua_tonumber(g_pLuaState, -3));
					float l_yValue =static_cast<float>(lua_tonumber(g_pLuaState, -2));
					float l_zValue = static_cast<float>(lua_tonumber(g_pLuaState, -1));
					lua_pop(g_pLuaState, 4);

					// Create Player Game Object and register components with engine
					KPVector3SSE l_startPosition = KPVector3SSE(l_xValue, l_yValue, 0.0f);
					if (i_OverridePosition)
					{
						l_startPosition = i_Position;
					}

					// Get Layer
					lua_pushstring(g_pLuaState, "layer");
					int l_layerType = lua_gettable(g_pLuaState, -2);
					assert(l_layerType == LUA_TNUMBER);
					Layer l_Layer = static_cast<Layer>(static_cast<int>(lua_tonumber(g_pLuaState, -1)));
					lua_pop(g_pLuaState, 1);

					// Get Tag
					lua_pushstring(g_pLuaState, "tag");
					int l_tagType = lua_gettable(g_pLuaState, -2);
					assert(l_tagType == LUA_TNUMBER);
					Tag l_Tag = static_cast<Tag>(static_cast<int>(lua_tonumber(g_pLuaState, -1)));
					lua_pop(g_pLuaState, 1);

					StrongPointer<GameObject> l_playerObject = new GameObject(l_pName, l_startPosition, l_Layer, l_Tag);
					GameObjectSystem::RegisterGameObject(l_playerObject);


					// Loop through components
					lua_pushstring(g_pLuaState, "components");
					int l_componentsType = lua_gettable(g_pLuaState, -2);
					assert(l_componentsType == LUA_TTABLE);
					lua_pushnil(g_pLuaState);
					while(lua_next(g_pLuaState, -2) != 0)
					{
						assert(lua_type(g_pLuaState, -2) == LUA_TSTRING);
						assert(lua_type(g_pLuaState, -1) == LUA_TTABLE);

						const char* l_key = lua_tostring(g_pLuaState, -2);
						

						if(strcmp(l_key,"KPRender2DComponent") == 0)
						{
							// Get Render String File name
							lua_pushstring(g_pLuaState, "texture");
							
							int l_fileNameType = lua_gettable(g_pLuaState, -2); // KPRenderComponent[top of stack after popping] =  Does KPRenderComponent(-2)["texture"(Top of Stack)]
							// It should be a string
							assert(l_fileNameType == LUA_TSTRING);
							// Retrieve the value associated with key "texture" as a string, assuming it�s a string
							const char * l_pFileName = lua_tostring(g_pLuaState, -1);
							
							// Registering Renderer Component
							KPEngine::Graphics::RendererSystem::RegisterSprite(l_playerObject, l_pFileName);
							lua_pop(g_pLuaState, 1);
						}
						else if (strcmp(l_key,"KPPhysics2DComponent") == 0 )
						{
							// Get Static property
							lua_pushstring(g_pLuaState, "isStatic");

							int l_staticType = lua_gettable(g_pLuaState, -2);

							assert(l_staticType == LUA_TBOOLEAN);

							int l_staticValue = lua_toboolean(g_pLuaState, -1);

							// Register Physics Component and passing to controller
							KPEngine::Physics::PhysicsSystem::RegisterPhysicsComponent(l_playerObject,
							                                                           l_staticValue != 0);

							lua_pop(g_pLuaState, 1);
						}
						else if (strcmp(l_key, "BoxCollisionComponent") == 0)
						{
							// Get Center
							KPVector3SSE l_Center = ReadVector("center");

							// Get Extents
							KPVector3SSE l_Extents = ReadVector("extents");

							// TODO For now. Add a Box collision to everything for testing purposes
							Collision::CollisionSystem::RegisterBoxComponent(l_playerObject, l_Center, l_Extents);
						}
						else if (strcmp(l_key, "CameraComponent") == 0)
						{
							// Just set as main camera for now
							Graphics::RendererSystem::RegisterMainCamera(l_playerObject);
						}
						else
						{
							assert(false && "UnIdentified Component");
						}

						

						lua_pop(g_pLuaState, 1);
					}
					l_NewStrongPointer = l_playerObject;
				}
				// Determine Game Object, Components, Properties, and stuff from Lua code, and return game object after adding it to the list
				delete[] l_pFileContents;

				return l_NewStrongPointer;
			}

			KPVector3SSE LuaSystem::ReadVector(const char* i_TableName)
			{
				lua_pushstring(g_pLuaState, i_TableName); // Push field name to table
				assert(lua_gettable(g_pLuaState, -2) == LUA_TTABLE); // Confirm it is a table
				assert((lua_rawgeti(g_pLuaState, -1, 1) == LUA_TNUMBER) && (lua_rawgeti(g_pLuaState, -2, 2) == LUA_TNUMBER) && (lua_rawgeti(g_pLuaState, -3, 3) == LUA_TNUMBER)); // confirm all the raw values are numbers
				KPVector3SSE l_Data = KPVector3SSE(static_cast<float>(lua_tonumber(g_pLuaState, -3)),
					static_cast<float>(lua_tonumber(g_pLuaState, -2)),
					static_cast<float>(lua_tonumber(g_pLuaState, -1))); // Get Vector
				lua_pop(g_pLuaState, 4);
				return l_Data;
			}
		}
	}

	
}

