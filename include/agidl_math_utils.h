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
*   Updated: 10/25/2023
*   Author: Ryandracus Chapman
*
********************************************/

#include "agidl_types.h"

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

#endif