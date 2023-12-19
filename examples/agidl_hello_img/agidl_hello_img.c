/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_hello_img.c
*   Date: 12/18/2023
*   Version: 0.2b
*   Updated: 12/18/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){
	
	AGIDL_BMP* bmp = AGIDL_CreateBMP("hello_bmp.bmp",100,50,AGIDL_RGB_888);
	AGIDL_ClearBMP(bmp,AGIDL_GetColor(PURPLE,AGIDL_RGB_888));
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	AGIDL_TGA* tga = AGIDL_CreateTGA("hello_tga.tga",100,50,AGIDL_BGR_555);
	AGIDL_ClearTGA16(tga,AGIDL_RGB16(15,0,64,AGIDL_TGAGetClrFmt(tga)));
	AGIDL_ExportTGA(tga);
	AGIDL_FreeTGA(tga);
	
	return 0;
}