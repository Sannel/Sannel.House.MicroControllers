#include "SannelCommon.h"

union bdouble {
	double d;
	char bytes[sizeof(double)];
};

void TypeHelper::AddToArray(uint8* arr, int data, uint startIndex)
{
	arr[startIndex] = (uint8)data;
	arr[startIndex + 1] = (uint8)(data >> 8);
	arr[startIndex + 2] = (uint8)(data >> 16);
	arr[startIndex + 3] = (uint8)(data >> 24);
}

void TypeHelper::AddToArray(uint8* arr, double data, uint startIndex) 
{
	bdouble q;
	q.d = data;
	int i = 0;
	for (i = 0; i < sizeof(double); i++) 
	{
		arr[startIndex + i] = q.bytes[i];
	}
}
