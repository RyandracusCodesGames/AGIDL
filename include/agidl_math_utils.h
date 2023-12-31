#ifndef AGIDL_MATH_UTILS_H
#define AGIDL_MATH_UTILS_H

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_math_utils.h
*   Date: 10/22/2023
*   Version: 0.1b
*   Updated: 12/18/2023
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_types.h"

#define AGIDL_PI 3.141592

int AGIDL_Min(int a, int b);
int AGIDL_Max(int a, int b);
int AGIDL_Abs(int a);
float AGIDL_Minf(float a, float b);
float AGIDL_Maxf(float a, float b);
float AGIDL_Absf(float a);
int AGIDL_Clamp(int minVal, int targetVal, int maxVal);
float AGIDL_Clampf(float minVal, float targetVal, float maxVal);
int AGIDL_Lerp(int a, int b, float interp);
int AGIDL_InvLerp(int a, int b, float interp);
float AGIDL_Sinf(float ang);
float AGIDL_Cosf(float ang);
float AGIDL_Tanf(float ang);
int AGIDL_Floor(int a);
float AGIDL_FModf(float a, float b);
float AGIDL_FixAng(float ang);
u32 AGIDL_Pow2(u32 num);
u32 AGIDL_Bin2Dec(char* bin);
u32 AGIDL_BitXor(u32 i, u32 j);
u32 AGIDL_BitInterleave(u32 a, u32 b);
char* AGIDL_Dec2Bin(u32 num);
u32 AGIDL_BitReverse(char* bin);

#endif