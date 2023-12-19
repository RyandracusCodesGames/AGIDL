/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: agidl_bit_depth.c
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
	AGIDL_SetBMPFilename(bmp,"quake_tex_16.bmp");
	AGIDL_BMPConvert24BPPTO16BPP(bmp);
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}