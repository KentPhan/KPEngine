#include "../../../include/Core/HeapManager/MemorySystem.h"
#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
#include <cassert>
#include "../../../include/Utils/KPLogType.h"
#include "../../../include/Utils/KP_Log.h"

namespace KPEngine
{
	namespace Core
	{
		namespace HeapManager
		{
			// TODO: Ask the question. Why the heck do I have to put these definitions of static variables here.
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_16_HeapSystem = nullptr;
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_32_HeapSystem = nullptr;
			Fixed::KPFixedHeapManager* MemorySystem::Fixed_128_HeapSystem = nullptr;
			Dynamic::KPDynamicHeapManager* MemorySystem::Dynamic_HeapSystem = nullptr;


			void* MemorySystem::MemorySystemAlloc(size_t i_size)
			{
				if (i_size <= 16)
				{
#if defined(_DEBUG)
					void* toReturn = Fixed_16_HeapSystem->_alloc(i_size);
					if (toReturn == nullptr)
						DEBUG_PRINT(Utils::KPLogType::Error, "FIXED 16 ALLOCATOR OUT OF BLOCKS. PRECONFIGURE ADDITIONAL BLOCKS");
					return toReturn;
#else
					return Fixed_16_HeapSystem->_alloc(i_size);
#endif
				}
				else if (i_size <= 32)
				{
#if defined(_DEBUG)
					void* toReturn = Fixed_32_HeapSystem->_alloc(i_size);
					if (toReturn == nullptr)
						DEBUG_PRINT(Utils::KPLogType::Error, "FIXED 32 ALLOCATOR OUT OF BLOCKS. PRECONFIGURE ADDITIONAL BLOCKS");
					return toReturn;
#else
					return Fixed_32_HeapSystem->_alloc(i_size);
#endif
				}
				else if (i_size <= 96)
				{
#if defined(_DEBUG)
					void* toReturn = Fixed_128_HeapSystem->_alloc(i_size);
					if (toReturn == nullptr)
						DEBUG_PRINT(Utils::KPLogType::Error, "FIXED 128 ALLOCATOR OUT OF BLOCKS. PRECONFIGURE ADDITIONAL BLOCKS");
					return toReturn;
#else
					return Fixed_128_HeapSystem->_alloc(i_size);
#endif		
				}
					

				return Dynamic_HeapSystem->_alloc(i_size, 4);
			}

			void MemorySystem::MemorySystemFree(void* i_ptr)
			{
				if (Fixed_16_HeapSystem->Contains(i_ptr))
				{
					Fixed_16_HeapSystem->_free(i_ptr);
					return;
				}
				else if (Fixed_32_HeapSystem->Contains(i_ptr))
				{
					Fixed_32_HeapSystem->_free(i_ptr);
					return;
				}
				else if (Fixed_128_HeapSystem->Contains(i_ptr))
				{
					Fixed_128_HeapSystem->_free(i_ptr);
					return;
				}

				bool test = Dynamic_HeapSystem->_free(i_ptr);
				assert(test);
				return;
			}

			bool MemorySystem::InitializeMemorySystem(void * i_pHeapMemory, size_t i_sizeHeapMemory)
			{
				// Create Fixed Heap Managers
				size_t l_memoryLeft = i_sizeHeapMemory;
				Fixed_16_HeapSystem = Fixed::KPFixedHeapManager::Create(i_pHeapMemory, l_memoryLeft, Fixed::Size_16, 100);
				l_memoryLeft -= Fixed_16_HeapSystem->GetByteSizeOfEverything();

				Fixed_32_HeapSystem = Fixed::KPFixedHeapManager::Create(Fixed_16_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_32, 200);
				l_memoryLeft -= Fixed_32_HeapSystem->GetByteSizeOfEverything();

				Fixed_128_HeapSystem = Fixed::KPFixedHeapManager::Create(Fixed_32_HeapSystem->GetPointerToEnd(), l_memoryLeft, Fixed::Size_128, 400);
				l_memoryLeft -= Fixed_128_HeapSystem->GetByteSizeOfEverything();

				// Create Dynamic Heap Manager
				Dynamic_HeapSystem = Dynamic::KPDynamicHeapManager::Create(Fixed_128_HeapSystem->GetPointerToEnd(), l_memoryLeft);

				return true;
			}

			void MemorySystem::Collect()
			{
				assert(Dynamic_HeapSystem);
				Dynamic_HeapSystem->Collect();
				// coalesce free blocks
				// you may or may not need to do this depending on how you've implemented your HeapManager
			}

			void MemorySystem::DestroyMemorySystem()
			{
				Fixed_16_HeapSystem->Destroy();
				Fixed_32_HeapSystem->Destroy();
				Fixed_128_HeapSystem->Destroy();
				Dynamic_HeapSystem->Destroy();
			}

		}
	}
}



