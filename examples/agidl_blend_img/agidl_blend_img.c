/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_blend_img.c
*   Date: 12/19/2023
*   Version: 0.2b
*   Updated: 12/19/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h> 

int main(){
	
	AGIDL_BMP* man = AGIDL_LoadBMP("man.bmp");
	AGIDL_BMP* gun = AGIDL_LoadBMP("shotgun.bmp");
	
	AGIDL_BlendChromaImg(man->pixels.pix32,gun->pixels.pix32, AGIDL_BMPGetWidth(man),AGIDL_BMPGetHeight(man),AGIDL_BMPGetWidth(gun),
	AGIDL_BMPGetHeight(gun), AGIDL_BMPGetClrFmt(man),AGIDL_BMPGetClrFmt(gun),80, 20, AGIDL_RGB(0,8,57,AGIDL_BMPGetClrFmt(gun)));
	
	AGIDL_SetBMPFilename(man,"man_with_shotgun.bmp");
	AGIDL_ExportBMP(man);
	AGIDL_FreeBMP(man);
	AGIDL_FreeBMP(gun);
	
	return 0;
}