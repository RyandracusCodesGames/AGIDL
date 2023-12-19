/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_grayscale_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("droid.bmp");
	AGIDL_SetBMPFilename(bmp,"grayscale_droid.bmp");
	AGIDL_GrayscaleBMP(bmp);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}