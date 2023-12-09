/********************************************
*   Adaptive Graphics Image Display Library
*
*   Copyright (c) 2023 Ryandracus Chapman
*
*   Library: libagidl
*   File: grayscale_img.c
*   Date: 12/8/2023
*   Version: 0.1b
*   Updated: 12/8/2023
*   Author: Ryandracus Chapman
*
********************************************/
#include <stdio.h>
#include <agidl.h>

int main(){

	AGIDL_BMP* bmp = AGIDL_LoadBMP("trucker.bmp");
	AGIDL_SetBMPFilename(bmp,"grayscale_trucker.bmp");
	AGIDL_GrayscaleImgData(bmp->pixels.pix16,AGIDL_BMPGetWidth(bmp),AGIDL_BMPGetHeight(bmp),AGIDL_BMPGetClrFmt(bmp));
	AGIDL_ExportBMP(bmp);
	AGIDL_FreeBMP(bmp);
	
	return 0;
}