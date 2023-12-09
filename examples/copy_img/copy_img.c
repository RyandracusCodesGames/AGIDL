/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: copy_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){

	AGIDL_BMP* bmp = AGIDL_LoadBMP("sad_mug_box.bmp");
	AGIDL_BMP* cpybmp = AGIDL_BMPCpyImg(bmp);

	int x,y = 25;
	for(x = 0; x < AGIDL_BMPGetWidth(bmp); x++){
		COLOR clr = AGIDL_BMPGetClr(cpybmp,x,y);
		clr = AGIDL_GetColor(BROWN,AGIDL_BMPGetClrFmt(bmp));
		AGIDL_BMPSetClr(cpybmp,x,y,clr);
	}
	
	AGIDL_ExportBMP(cpybmp);
	AGIDL_FreeBMP(cpybmp);
	
	AGIDL_SetBMPFilename(bmp,"original.bmp");
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}