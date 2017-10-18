/* Copyright (C) 2001 Avaya Inc.  All rights reserved.*/
/***********************************************************/
/*
 *  tsplatfm.h    Platform-dependent definitions
 *
 */

#ifndef TSPLATFM_H
#define TSPLATFM_H

/* define the CONST_PARAM keyword for C++ compilers */
#if defined (__cplusplus)

 #define CONST_PARAM const

#else

 #define CONST_PARAM

#endif

/* figure out what platform we're compiling for */

#if defined ( __powerc ) || \
	defined ( powerc )
		
 #define TSLIB_MAC_PPC
 
#elif defined ( THINK_C ) || \
	defined ( __SC__ ) || \
	defined ( applec ) || \
	defined ( __MWERKS__ )

 #define TSLIB_MAC_68K
 
#elif defined ( __OS2__ )
	
 #define TSLIB_OS2
 
#elif defined ( __hpux )

 #define TSLIB_HPUX
 
#elif defined ( __USLC__ ) || \
	  defined ( unix )

 #define TSLIB_UNIXWARE

#elif defined (WIN32) || defined ( _WIN32 ) || \
	defined (__WIN32__) || defined ( __WINDOWS_386__ )
	
 #define TSLIB_WINDOWS_32
 
#elif defined ( WINDOWS ) || \
	defined ( _WINDOWS ) || \
	defined ( __WINDOWS__ ) || \
	defined ( _Windows )
	
 #define TSLIB_WINDOWS_16
 
#elif defined ( __WATCOMC__ )
	
 #define TSLIB_NETWARE
 
#else
 #error I do not recognize your compilation environment
#endif


#ifndef TRUE
#define TRUE (0 == 0)
#endif

#ifndef FALSE
#define FALSE (0 != 0)
#endif

typedef char Nulltype;


/*
 *	On some platforms, sizeof(int) depends upon
 *	the compiler and/or options used;
 *	the "_Int" data type is defined according
 *	to the size of "int" used in TSLIB
 */
 
#if defined ( TSLIB_WINDOWS_16 )

 #pragma pack(1)
 
 typedef unsigned short	ACSHandle_t;
 typedef char Boolean;
	
 #define _Int	short
 #define TSAPI	RetCode_t __far __pascal
 
 #ifndef FAR
  #define FAR __far
 #endif
	
#elif defined ( TSLIB_WINDOWS_32 )

 // Win32 Specific definitions for Windows/NT 3.5 
 #pragma pack(8)

 typedef unsigned long	ACSHandle_t;
 typedef unsigned char Boolean;  

 #define _Int int
 #define TSAPI  RetCode_t pascal	 

 #ifndef FAR
 #define FAR /* */
 #endif

 // typedef long LONG; 

#elif defined ( TSLIB_NETWARE )

 #pragma pack(1)
 
 typedef unsigned long	ACSHandle_t;
 typedef char Boolean;

 #define _Int	long
 #define TSAPI	RetCode_t
 #define FAR

#elif defined ( TSLIB_OS2 )

 #pragma pack(4)
 
 typedef unsigned long	ACSHandle_t;
 typedef char Boolean;

 #define _Int	long
 #define TSAPI	RetCode_t EXPENTRY
 #define FAR

#elif defined ( TSLIB_MAC_68K )

 /*
 	there is no universal pragma for all 68K
 	compilers, but 2-byte alignment is essential
 */
 
 typedef unsigned long	ACSHandle_t;
 #include <Types.h>		/* "Boolean" is already defined here */

 #define _Int	long
 #define TSAPI	pascal RetCode_t
 #define FAR

#elif defined ( TSLIB_MAC_PPC )

 #pragma options align=mac68k
 
 typedef unsigned long	ACSHandle_t;
 #include <Types.h>		/* "Boolean" is already defined here */

 #define _Int	long
 #define TSAPI	pascal RetCode_t
 #define FAR

#elif defined ( TSLIB_UNIXWARE )

 #pragma pack(4)
 
 typedef unsigned long	ACSHandle_t;
 typedef char Boolean;

 #define _Int	long
 #define TSAPI	RetCode_t
 #define FAR

#elif defined ( TSLIB_HPUX )

 #ifndef __cplusplus
 #pragma HP_ALIGN NATURAL
 #endif
 
 typedef unsigned long	ACSHandle_t;
 typedef char Boolean;

 #define _Int	long
 #define TSAPI	RetCode_t
 #define FAR

#endif


#endif

