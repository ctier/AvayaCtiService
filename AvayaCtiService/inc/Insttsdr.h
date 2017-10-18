/*
 *
 * insttsdr.h
 *
 * 		Header file for adding a Telephony Services for NT PBX driver
 *		to the Telephony Services list of administered drivers
 *		during the install of the PBX driver. 
 *
 *	NOTE:
 *		Telephony Services must be installed before this routine can
 *		be called from a driver installation routine.
 *
 */

#if !defined(_INSTTSDRLIB_)
	#define INSTLIBAPI 	__declspec(dllimport)
#else
	#define INSTLIBAPI	__declspec(dllexport)
#endif

/**************************************************************************/
/* Prototypes                                                             */
/**************************************************************************/

INSTLIBAPI long installTelephonyServicesDriver(
	char 	*driverDllName,	// 8.3 name for driver dll
	int		flag);			// flag for autoloading

INSTLIBAPI long getTelephonyServicesDirectory(
	char 	*directoryName,	// Pointer to buffer for directory name
	LPDWORD	lpdwSize);		// Pointer to size of buffer provided

INSTLIBAPI long getTelephonyServicesIPAddress(
	char 	*tsIPAddress,	// Pointer to buffer for IP address
	LPDWORD	lpdwSize);		// Pointer to size of buffer provided

/**************************************************************************/
/* Defines for flag attribute for installTelephonyServicesDriver          */
/**************************************************************************/
#define		TSDR_DONT_AUTOLOAD 	FALSE	// Don't autoload driver when 
										// Telephony Server is started

#define		TSDR_AUTOLOAD		TRUE	// Attempt autoload of this driver 
										// when Telephony Server is started

/**************************************************************************/
/* Return Codes from insttsdr routines                                    */
/*                                                                        */
/*  A driver installation should not fail as a result of an error         */
/*  code from these routines.  For installTelephonyServicesDriver it      */ 
/*  should only notify the user that it was unable to add the driver to   */
/*  the list of administered drivers and the user should update the       */
/*  driver administration through the Telephony Services Administrator    */
/*  (TSA.EXE) or the Telephony Services Maintenance (TSM32.EXE) app.      */
/**************************************************************************/

#define		TSDR_SUCCESS			0	// The driver was successfully 
										// added to the list

#define		TSDR_DUPLICATE			-10	// The driver name is already 
										// in the list

#define		TSDR_TS_NOT_INSTALLED	-11	// Telephony Services is 
										// not installed

#define		TSDR_INTERNAL_ERROR		-12	// Unknown error

#define		TSDR_INVALID_PARAMETER	-13	// invalid parameter

#define		TSDR_BUFFER_TOO_SMALL	-14	// The size of the buffer is too 
										// small to accomodate 
										// the directory name - the minimum
										// size needed is returned in lpdwSize
