/*
 Name:		SannelCommon.h
 Created:	6/10/2017 7:35:18 PM
 Author:	holts
 Editor:	http://www.visualmicro.com
*/

#ifndef _SannelCommon_h
#define _SannelCommon_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class TypeHelper
{
public:
	static void AddToArray(uint8* arr, int data, uint startIndex = 0);
	static void AddToArray(uint8* arr, double data, uint startIndex = 0);
};

#endif

