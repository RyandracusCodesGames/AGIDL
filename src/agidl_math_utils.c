#include <stdlib.h>
#include <string.h>
#include "agidl_math_utils.h"
#include "agidl_math_trig_tables.h"

/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_math_utils.c
*   Date: 10/22/2023
*   Version: 0.1b
*   Updated: 12/18/2023
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

int AGIDL_Floor(int a){
	return a - (a % 1);
}

float AGIDL_FModf(float a, float b){
	int result = (int)AGIDL_Floor( a / b);
	return a - result * b;
}

float AGIDL_FixAng(float ang){
	ang = AGIDL_FModf(ang,360);
	if(ang < 0){
		ang += 360;
	}
	return ang;
}

float AGIDL_Sinf(float ang){
	return sin_lut[(int)AGIDL_FixAng(ang)];
}
float AGIDL_Cosf(float ang){
	return cos_lut[(int)AGIDL_FixAng(ang)];
}

float AGIDL_Tanf(float ang){
	return tan_lut[(int)AGIDL_FixAng(ang)];
}

u32 AGIDL_Pow2(u32 num){
	return 1 << num;
}

char* AGIDL_Dec2Bin(u32 num){
	u8 num_of_bits = 0;
	
	if(num <= 1){
		num_of_bits = 1;
	}
	else if(num <= 3){
		num_of_bits = 2;
	}
	else if(num <= 7){
		num_of_bits = 3;
	}
	else if(num <= 15){
		num_of_bits = 4;
	}
	else if(num <= 31){
		num_of_bits = 5;
	}
	else if(num <= 63){
		num_of_bits = 6;
	}
	else if(num <= 127){
		num_of_bits = 7;
	}
	else if(num <= 255){
		num_of_bits = 8;
	}
	else if(num <= 511){
		num_of_bits = 9;
	}
	else if(num <= 1023){
		num_of_bits = 10;
	}
	else if(num <= 2047){
		num_of_bits = 11;
	}
	else if(num <= 4095){
		num_of_bits = 12;
	}
	
	char* bin = (char*)malloc((sizeof(char)*num_of_bits)+1);
	
	int i;
	for(i = num_of_bits-1; i >= 0; i--){
		int k = num >> i;
		if(k & 1){
			bin[(num_of_bits-1)-i] = '1';
		}
		else{
			bin[(num_of_bits-1)-i] = '0';
		}
	}
	
	bin[num_of_bits] = '\0';
	
	return bin;
}

u32 AGIDL_Bin2Dec(char* bin){
	u32 accumulation = 0;
	int i;
	for(i = strlen(bin)-1; i >= 0; i--){
		u8 binmul = 0;
		if(bin[i] == '0'){
			binmul = 0;
		}
		if(bin[i] == '1'){
			binmul = 1;
		}
		accumulation += binmul * AGIDL_Pow2(strlen(bin)-(i+1));
	}
	return accumulation;
}

u32 AGIDL_BitReverse(char* bin){
	char* reverse = (char*)malloc(strlen(bin)+1);
	reverse[strlen(bin)] = '\0';
	
	int i;
	for(i = 0; i <= strlen(bin); i++){
		reverse[i] = bin[strlen(bin)-(i+1)];
	}
	
	u32 bitreverse = AGIDL_Bin2Dec(reverse);

	free(reverse);
	
	return bitreverse;
}

u32 AGIDL_BitXor(u32 i, u32 j){
	return i ^ j;
}

u32 AGIDL_BitInterleave(u32 a, u32 b){
	char* binA = AGIDL_Dec2Bin(a);
	char* binB = AGIDL_Dec2Bin(b);
	
	int lenA = strlen(binA);
	int lenB = strlen(binB);
	
	char* binC = (char*)malloc(lenA+lenB+1);
	
	int i;
	for(i = 0; i < lenA+lenB; i += 2){
		int index = i / 2;
		
		binC[i] = binA[index];
		binC[i+1] = binB[index];
	}
	
	binC[lenA+lenB] = '\0';
	
	u32 bitinterleave = AGIDL_Bin2Dec(binC);
	
	free(binA);
	free(binB);
	free(binC);
	
	return bitinterleave;
}