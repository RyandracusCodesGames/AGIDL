/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_filter_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("quake_tex.bmp");
	AGIDL_SetBMPFilename(bmp,"bilin_filter.bmp");
	AGIDL_FilterBilerpBMP(bmp);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_BMP* bmp2 = AGIDL_LoadBMP("quake_tex.bmp");
	AGIDL_SetBMPFilename(bmp2,"trilin_filter.bmp");
	AGIDL_FilterTrilerpBMP(bmp2);
	AGIDL_ExportBMP(bmp2);
	AGIDL_FreeBMP(bmp2);
	
	return 0;
}