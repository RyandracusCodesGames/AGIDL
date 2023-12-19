/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_mirror_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* bmp = AGIDL_LoadBMP("mirror.bmp");
	AGIDL_SetBMPFilename(bmp,"tree.bmp");
	AGIDL_MirrorBMP(bmp,MIRROR_LEFT_TO_RIGHT);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}