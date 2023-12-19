/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_img_palette.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_TIM* tim = AGIDL_LoadTIM("ufo.tim");
	AGIDL_BMP* bmp = AGIDL_ConvertTIM2BMP(tim);
	AGIDL_BMPSetICPMode(bmp,YES_ICP);
	AGIDL_BMPSetMaxDiff(bmp,4);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	AGIDL_FreeTIM(tim);
	
	AGIDL_BMP* droid = AGIDL_LoadBMP("droid.bmp");
	AGIDL_SetBMPFilename(droid,"droid_clr_palette.bmp");
	AGIDL_BMPSetICPMode(droid,YES_ICP);
	AGIDL_BMPSetMaxDiff(droid,15);
	AGIDL_ExportBMP(droid);
	AGIDL_FreeBMP(droid);
	
	return 0;
}