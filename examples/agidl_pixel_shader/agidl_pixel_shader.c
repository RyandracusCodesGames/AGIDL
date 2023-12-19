/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_pixel_shader.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	AGIDL_CLR_FMT fmt = AGIDL_RGB_888;
	
	COLOR blue = AGIDL_GetColor(BLUE,fmt), red = AGIDL_GetColor(RED,fmt);
	COLOR purple = AGIDL_BlendColor(blue,red,0.3f,CC_BLEND_CLR_SRCINV,fmt);
	
	AGIDL_BMP* bmp = AGIDL_CreateBMP("blendclr.bmp",100,50,fmt);
	AGIDL_ClearBMP(bmp,purple);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	blue = AGIDL_RGB(1,1,255,fmt); red = AGIDL_RGB(255,1,1,fmt);
	purple = AGIDL_ColorCombine(blue,red,CC_SUB_AND_INTERP_CLR2,fmt);
	
	AGIDL_BMP* bmp2 = AGIDL_CreateBMP("n64_blendclr.bmp",100,50,fmt);
	AGIDL_ClearBMP(bmp2,purple);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	
	return 0;
}