#ifndef MemoryCount_H
#define MemoryCount_H

#include <cstdlib>
#include <cstdio>

#define IMPLICIT_EXCEPTION_SPEC_MISMATCH 1
#include "IgnoreDiagnostics.h"

static std::size_t MEMORY_USED(0);

//=============================================================================
struct MemoryTrace {
  MemoryTrace()
    : pointer(0),
      size(0)
    {
    }
  void* pointer;
  std::size_t size;
};

#ifdef CUSTOM_MEMORY_MAP_CAPACITY
static const int MEMORY_MAP_CAPACITY = CUSTOM_MEMORY_MAP_CAPACITY;
#undef CUSTOM_MEMORY_MAP_CAPACITY
#else
static const int MEMORY_MAP_CAPACITY = 1024 * 1024;
#endif

static MemoryTrace MEMORY_MAP[MEMORY_MAP_CAPACITY];

//=============================================================================
void* operator new(std::size_t size)
{
  void* pointer = malloc(size);
  for (std::size_t i = 0; i < MEMORY_MAP_CAPACITY; ++i) {
    if (!MEMORY_MAP[i].pointer) {
      MEMORY_USED += size;
      MEMORY_MAP[i].pointer = pointer;
      MEMORY_MAP[i].size = size;
      break;
    }
  }
  return pointer;
}

//=============================================================================
void operator delete(void* pointer)
{
  for (std::size_t i = 0; i < MEMORY_MAP_CAPACITY; ++i) {
    if (MEMORY_MAP[i].pointer == pointer) {
      MEMORY_USED -= MEMORY_MAP[i].size;
      MEMORY_MAP[i].pointer = 0;
      MEMORY_MAP[i].size = 0;
      break;
    }
  }
  free(pointer);
}

//=============================================================================
void memory_dump()
{
  printf("Dump\nMEMORY_USED: %u\n", MEMORY_USED);
  for (std::size_t i = 0; i < MEMORY_MAP_CAPACITY; ++i) {
    if (MEMORY_MAP[i].pointer) {
      printf("%u: ptr=%p size=%u\n", i, MEMORY_MAP[i].pointer, MEMORY_MAP[i].size);
    }
  }
}

#endif
