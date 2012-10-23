/*
 * compileConfig.h
 *
 *  Created on: Sep 14, 2012
 *      Author: gregorytkach
 */

#ifndef COMPILECONFIG_H_
#define COMPILECONFIG_H_

// --------------------------------------------
//
//! define a assert macro for debugging.
#if defined(DEBUG)
#if defined(_IRR_WINDOWS_API_) && defined(_MSC_VER) && !defined (_WIN32_WCE)
#if defined(WIN64) || defined(_WIN64) // using portable common solution for x64 configuration
#include <crtdbg.h>
#define IRR_ASSERT( _CONDITION_ ) if (!_CONDITION_) {_CrtDbgBreak();}
#else
#define IRR_ASSERT( _CONDITION_ ) if (!_CONDITION_) {_asm int 3}
#endif
#else
#include "assert.h"
#define IRR_ASSERT( _CONDITION_ ) assert( (_CONDITION_) );
#endif
#else
#define IRR_ASSERT( _CONDITION_ )
#endif

//! Provide deprecate attribute
//! Defines a deprecated macro which generates a warning at compile time
/** The usage is simple
 For typedef:		typedef _IRR_DEPRECATED_ int test1;
 For classes/structs:	class _IRR_DEPRECATED_ test2 { ... };
 For methods:		class test3 { _IRR_DEPRECATED_ virtual void foo() {} };
 For functions:		template<class T> _IRR_DEPRECATED_ void test4(void) {}
 **/
#if defined(IGNORE_DEPRECATED_WARNING)
#define _IRR_DEPRECATED_
#elif _MSC_VER >= 1310 //vs 2003 or higher
#define _IRR_DEPRECATED_ __declspec(deprecated)
#elif (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)) // all versions above 3.0 should support this feature
#define _IRR_DEPRECATED_  __attribute__ ((deprecated))
#else
#define _IRR_DEPRECATED_
#endif

//! creates four CC codes used in Irrlicht for simple ids
/** some compilers can create those by directly writing the
 code like 'code', but some generate warnings so we use this macro here */
#define MAKE_IRR_ID(c0, c1, c2, c3) \
		((u32)(u8)(c0) | ((u32)(u8)(c1) << 8) | \
		((u32)(u8)(c2) << 16) | ((u32)(u8)(c3) << 24 ))

// --------------------------------------------
//! MacOS X

//TODO:detect MacOS X
#if defined(__APPLE__) || defined(MACOSX)
#ifndef MACOSX	//legacy support
#define MACOSX
#endif

#define _IRRGAME_MACOSX_
#endif

//! io
#define LINEBREAK "\r"

//! threads
#define PRIORITY_LOW	-20
#define PRIORITY_NORMAL	0
#define PRIORITY_HIGH	20



// --------------------------------------------
//! Windows

//#define LINEBREAK "\r\n"

//! Defines a small statement to work around a microsoft compiler bug.
/** The microsoft compiler 7.0 - 7.1 has a bug:
 When you call unmanaged code that returns a bool type value of false from managed code,
 the return value may appear as true. See
 http://support.microsoft.com/default.aspx?kbid=823071 for details.
 Compiler version defines: VC6.0 : 1200, VC7.0 : 1300, VC7.1 : 1310, VC8.0 : 1400*/
#if defined(_IRR_WINDOWS_API_) && defined(_MSC_VER) && (_MSC_VER > 1299) && (_MSC_VER < 1400)
#define _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX __asm mov eax,100
#else
#define _IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
#endif // _IRR_MANAGED_MARSHALLING_BUGFIX
// memory debugging
#if defined(DEBUG) && defined(IRRLICHT_EXPORTS) && defined(_MSC_VER) && \
	(_MSC_VER > 1299) && !defined(_IRR_DONT_DO_MEMORY_DEBUGGING_HERE) && !defined(_WIN32_WCE)

#define CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#include <stdlib.h>
#include <crtdbg.h>
#define new DEBUG_CLIENTBLOCK
#endif

// disable truncated debug information warning in visual studio 6 by default
#if defined(_MSC_VER) && (_MSC_VER < 1300 )
#pragma warning( disable: 4786)
#endif // _MSC
//! ignore VC8 warning deprecated
/** The microsoft compiler */
#if defined(_IRR_WINDOWS_API_) && defined(_MSC_VER) && (_MSC_VER >= 1400)
//#pragma warning( disable: 4996)
//#define _CRT_SECURE_NO_DEPRECATE 1
//#define _CRT_NONSTDC_NO_DEPRECATE 1
#endif

#endif /* COMPILECONFIG_H_ */
