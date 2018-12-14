// To Swap between Dynamic and Mixed Heap Allocators. These have to be commented out and in according to what you want to use

#include <inttypes.h>

#include <stdio.h>
#include "../../../include/Core/HeapManager/KPFixedHeapManager.h"
#include "../../../include/Core/HeapManager/KPDynamicHeapManager.h"
#include "../../../include/Core/HeapManager/MemorySystem.h"


void * __cdecl malloc(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("malloc %zu\n", i_size);
	return KPEngine::Core::HeapManager::Dynamic_HeapSystem->_alloc(i_size, 4);
}

void __cdecl free(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("free 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	KPEngine::Core::HeapManager::Dynamic_HeapSystem->_free(i_ptr);
	return;
}

void * operator new(size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("new %zu\n", i_size);
	return KPEngine::Core::HeapManager::Dynamic_HeapSystem->_alloc(i_size, 4);
}

void operator delete(void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	KPEngine::Core::HeapManager::Dynamic_HeapSystem->_free(i_ptr);
	return;
}

void * operator new[](size_t i_size)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("new [] %zu\n", i_size);
	return KPEngine::Core::HeapManager::Dynamic_HeapSystem->_alloc(i_size, 4);;
}

void operator delete [](void * i_ptr)
{
	// replace with calls to your HeapManager or FixedSizeAllocators
	printf("delete [] 0x%" PRIXPTR "\n", reinterpret_cast<uintptr_t>(i_ptr));
	KPEngine::Core::HeapManager::Dynamic_HeapSystem->_free(i_ptr);
	return;
}