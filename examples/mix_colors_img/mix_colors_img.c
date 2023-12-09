/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: mix_colors_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){

	COLOR16 clr = AGIDL_GetColor(BLUE,AGIDL_RGB_555), clr2 = AGIDL_GetColor(RED,AGIDL_RGB_555);
	COLOR16 mix = AGIDL_BlendColor(clr,clr2,0.35f,CC_BLEND_CLR_SRCINV,AGIDL_RGB_555);
	
	AGIDL_BMP* bmp = AGIDL_CreateBMP("mix.bmp",50,50,AGIDL_RGB_555);
	AGIDL_ClearBMP16(bmp,mix);
	AGIDL_ExportBMP(bmp);
	
	mix = AGIDL_ColorCombine(clr,clr2,CC_MUL_AND_SUB_CLR,AGIDL_RGB_555);
	AGIDL_ClearBMP16(bmp,mix);
	AGIDL_SetBMPFilename(bmp,"ultramix.bmp");
	AGIDL_ExportBMP(bmp);
	
	AGIDL_FreeBMP(bmp);

	return 0;
}