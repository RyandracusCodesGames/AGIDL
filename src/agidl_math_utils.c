#include "agidl_math_utils.h"


/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_math_utils.c
*   Date: 10/22/2023
*   Version: 0.1b
*   Updated: 10/25/2023
*   Author: Ryandracus Chapman
*
********************************************/


int AGIDL_Min(int a, int b){
	if(a < b){
		return a;
	}
	else return b;
}

int AGIDL_Max(int a, int b){
	if(a > b){
		return a;
	}
	else return b;
}

int AGIDL_Abs(int a){
	if(a < 0){
		return -a;
	}
	else return a;
}

int AGIDL_Clamp(int minVal, int targetVal, int maxVal){
	return AGIDL_Max(AGIDL_Min(maxVal,targetVal),minVal);
}

int AGIDL_Lerp(int a, int b, float interp){
	return a + interp * (a - b);
}

float AGIDL_Minf(float a, float b){
	if(a < b){
		return a;
	}
	else return b;
}

float AGIDL_Maxf(float a, float b){
	if(a > b){
		return a;
	}
	else return b;
}

float AGIDL_Absf(float a){
	if(a < 0){
		return -a;
	}
	else return a;
}

float AGIDL_Clampf(float minVal, float targetVal, float maxVal){
	return AGIDL_Maxf(AGIDL_Minf(maxVal,targetVal),minVal);
}