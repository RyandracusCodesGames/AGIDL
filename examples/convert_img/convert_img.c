/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: convert_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){

	AGIDL_TIM* tim = AGIDL_LoadTIM("sad_mug_rle.tim");
	AGIDL_BMP* bmp = AGIDL_ConvertTIM2BMP(tim);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	AGIDL_FreeTIM(tim);
	
	return 0;
}