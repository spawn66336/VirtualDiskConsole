#ifndef ZP_PREDEFINE
#define  ZP_PREDEFINE

#include "ZPStdDependency.h"

#	if defined( _DEBUG )
#		define ZP_DEBUG
#	endif

#	if defined( _USRDLL )
#			define ZP_NONCLIENT
#	endif

#  if defined( UNICODE )
#			define ZP_UNICODE
#  endif

#	if	defined( ZP_NONCLIENT )
#			define ZPEXPORT	__declspec( dllexport )
#	else	
#			define ZPEXPORT	__declspec( dllimport )
#	endif

#	if defined( ZP_DEBUG )
#			define ZP_ASSERT(x) assert(x)
#	else
#			define ZP_ASSERT(x)
#	endif

#define ZP_SAFE_NEW( x , t ) do{ if( NULL != (x) ){ delete (x); (x) = NULL; } (x) = new t; ZP_ASSERT(x); }while(0)
#define ZP_SAFE_DELETE( x ) do{ if( NULL != (x) ){ delete (x); (x) = NULL; } }while(0)
#define ZP_SAFE_NEW_BUFFER( x , t , size ) do{ if( NULL != (x) ){ delete[] (x); (x) = NULL; } (x) = new t[size]; ZP_ASSERT(x); }while(0)
#define ZP_SAFE_DELETE_BUFFER( x ) do{ if( NULL != (x) ){ delete[] (x); (x) = NULL; } }while(0)

#endif