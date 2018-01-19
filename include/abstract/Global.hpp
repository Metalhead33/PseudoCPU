#pragma once
#include <exception>
#include <memory>
#include <iostream>
#include <cstdint>
#include <vector>

typedef std::vector<uint8_t> RawMemoryBuffer;
typedef std::shared_ptr<RawMemoryBuffer> SharedMemory;

// From util.h - Written by Daniël Sonck
#define DEFINE_PTR(a) typedef a *p##a; \
   typedef std::shared_ptr< a > s##a; \
   typedef std::weak_ptr< a > w##a;

#define DEFINE_PTR2(s,a) typedef s::a *p##a; \
   typedef std::shared_ptr< s::a > s##a; \
   typedef std::weak_ptr< s::a > w##a;

#define DEFINE_CLASS(klass) class klass; DEFINE_PTR(klass)
#define DEFINE_STRUCT(klass) struct klass; DEFINE_PTR(klass)

//End of former util.h

// Some useful defines
#define EXCEPTION(A,B) struct A : public std::exception \
{ \
  const char * what () const throw () \
  { \
	return B; \
  } \
};

#if defined(DEBUG) || defined(_DEBUG) || defined(DEBUG_BUILD)
#   define IF_DEBUG( ... )   __VA_ARGS__
#else
#   define IF_DEBUG( ... )
#endif /* DEBUG */
