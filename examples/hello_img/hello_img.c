/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: hello_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){

	AGIDL_BMP* bmp = AGIDL_CreateBMP("purple.bmp",100,50,AGIDL_RGB_888);
	AGIDL_ClearBMP(bmp,AGIDL_GetColor(PURPLE,AGIDL_RGB_888));
	AGIDL_BMPSetICPMode(bmp,1);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);

	return 0;
}